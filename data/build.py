from code_generation.cpp_generator import *
from code_generation.code_generator import *
import glob
import os
import os.path
import subprocess
import urllib.request

from blocks import block_to_class, block_to_traits
from items import item_to_class
from properties import reorder_properties, translate_property
from util import *


if not os.path.exists('server.jar'):
    print('Downloading server jar')
    urllib.request.urlretrieve(
        'https://piston-data.mojang.com/v1/objects/8f3112a1049751cc472ec13e397eade5336ca7ae/server.jar', 'server.jar')

if not os.path.exists('generated'):
    print('Generating server data')
    subprocess.call(['java', '-DbundlerMainClass=net.minecraft.data.Main', '-jar', 'server.jar', '--reports', '--server'])

if not os.path.exists('out/include'):
    os.makedirs('out/include')

if not os.path.exists('out/src'):
    os.makedirs('out/src')


blocks = load_json('generated/reports/blocks.json')
block_names = blocks.keys()
for block in blocks.values():
    block['min_id'] = min(map(lambda state: state['id'], block['states']))
blocks = sorted(blocks.items(), key=lambda item: item[1]['min_id'])
registries = load_json('generated/reports/registries.json')
load_tags('blocks')
load_tags('entity_types')
load_tags('fluids')
load_tags('game_events')
load_tags('items')


# Clean output directory
for f in glob.glob('out/**.*'):
    os.remove(f)


hpp = CppFile('out/include/blocks.h')
hpp('#pragma once')
hpp('#include <vector>')
hpp('#include <spicygoat/block/types.h>')
cpp = CppFile('out/src/blocks.cpp')
cpp('#include <spicygoat/data/blocks.h>')

with hpp.block('namespace Blocks'), cpp.block('namespace Blocks'):
    lines = []
    for block_name, block in blocks:
        short_name = block['short_name'] = block_name.replace('minecraft:', '')
        block_class = block_to_class(short_name)
        block_traits = ', {' + ', '.join(map(lambda t: 'Traits::' + t, block_to_traits(short_name))) + '}' if block_class == 'Block' else ''
        properties = list(block.get('properties', {}).items())
        reorder_properties(short_name, properties)
        block_props = ', {' + ', '.join(map(lambda p: 'Properties::' + translate_property(short_name, p), properties)) + '}' if block_class == 'Block' else ''

        CppVariable(name=short_name, type='extern const ' + block_class).render_to_string(hpp)
        line = 'const ' + block_class + ' ' + short_name + ' = ' + block_class + '({"' + short_name + '"}' + block_traits + block_props

        for state in block['states']:
            if 'default' in state and state['default'] and 'properties' in state and state['id'] != block['min_id']:
                state_properties = list(state['properties'].values())
                reorder_properties(short_name, state_properties)
                line += ', {' + ', '.join(map(lambda v: '"' + v + '"', state_properties)) + '}'

        line += ');'

        lines.append(line)

    CppVariable(name='All', type='extern const std::vector<std::reference_wrapper<const Block>>').render_to_string(hpp)
    cpp('const std::vector<std::reference_wrapper<const Block>> All = {' + ', '.join(map(lambda e: e[1]['short_name'], blocks)) + '};')

    lines_chunked = list(chunks(lines, 100))
    for n, file_lines in enumerate(lines_chunked):
        cppn = CppFile('out/src/blocks.' + str(n) + '.cpp')
        cppn('#include <spicygoat/data/blocks.h>')
        cppn('#include <spicygoat/block/properties/properties.h>')
        with cppn.block('namespace Blocks'):
            for line in file_lines:
                cppn(line)
        cppn.close()

hpp.close()
cpp.close()


hpp = CppFile('out/include/items.h')
hpp('#pragma once')
hpp('#include <vector>')
hpp('#include <spicygoat/item/types.h>')
cpp = CppFile('out/src/items.cpp')
cpp('#include <spicygoat/data/items.h>')

with hpp.block('namespace Items'), cpp.block('namespace Items'):
    lines = []
    items = registries['minecraft:item']['entries'].items()
    for item_name, item in items:
        short_name = item['short_name'] = item_name.replace('minecraft:', '')
        item_class, ctr_args = item_to_class(short_name, block_names)

        CppVariable(name=short_name, type='extern const ' + item_class).render_to_string(hpp)
        line = 'const ' + item_class + ' ' + short_name + ' = ' + item_class + '("' + item_name + '"' \
               + (', ' + ', '.join(ctr_args) if ctr_args else '') + ');'

        lines.append(line)

    CppVariable(name='All', type='extern const std::vector<std::reference_wrapper<const Item>>').render_to_string(hpp)
    cpp('const std::vector<std::reference_wrapper<const Item>> All = {' + ', '.join(map(lambda e: e[1]['short_name'], items)) + '};')

    lines_chunked = list(chunks(lines, 100))
    for n, file_lines in enumerate(lines_chunked):
        cppn = CppFile('out/src/items.' + str(n) + '.cpp')
        cppn('#include <spicygoat/data/blocks.h>')
        cppn('#include <spicygoat/data/items.h>')
        with cppn.block('namespace Items'):
            for line in file_lines:
                cppn(line)
        cppn.close()

hpp.close()
cpp.close()


cpp = CppFile('out/include/tags.h')
cpp('#pragma once')
cpp('#include <functional>')
cpp('#include <vector>')
cpp('#include <spicygoat/tags/Tag.h>')

with cpp.block('namespace Tags'):
    for tag_type in tags:
        with cpp.block('namespace ' + tag_type):
            for tag_name, tag in tags[tag_type].items():
                ids = []
                append_tag_ids(tag_type, registries['minecraft:' + tag_type[:-1]]['entries'], tag, ids)

                CppVariable(name=sanitize(tag_name), type='inline Tag', initialization_value='Tag("minecraft:' + tag_name + '", {' + ', '.join(map(lambda e: str(e), ids)) + '})')\
                    .render_to_string(cpp)

            CppVariable(name='All', type='inline std::vector<std::reference_wrapper<Tag>>', initialization_value='{' + ', '.join(map(lambda e: sanitize(e), tags[tag_type])) + '}') \
                .render_to_string(cpp)

cpp.close()


registry_classes = {'block': 'BlockRegistry', 'item': 'ItemRegistry'}
registry_names = ['block', 'entity_type', 'item']
hpp = CppFile('out/include/registries.h')
hpp('#pragma once')
hpp('#include <spicygoat/block/BlockRegistry.h>')
hpp('#include <spicygoat/item/ItemRegistry.h>')
cpp = CppFile('out/src/registries.cpp')
cpp('#include <spicygoat/data/registries.h>')

with hpp.block('namespace Registries'), cpp.block('namespace Registries'):
    def impl(self, cpp):
        for registry_name in registry_names:
            registry = registries['minecraft:' + registry_name]
            if 'default' in registry:
                cpp(registry_name + '.defaultKey = "' + registry['default'] + '";')

            for entry_name, entry in registry['entries'].items():
                cpp(registry_name + '.addMapping("' + entry_name + '", ' + str(entry['protocol_id']) + ');')

    fun = CppFunction(name='load', ret_type='void', implementation_handle=impl)
    for registry_name in registry_names:
        fun.add_argument(registry_classes.get(registry_name, 'Registry') + '& ' + registry_name)
    fun.declaration().render_to_string(hpp)
    fun.definition().render_to_string(cpp)

hpp.close()
cpp.close()


print('Done.')
