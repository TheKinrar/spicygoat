from code_generation.cpp_generator import *
from code_generation.code_generator import *
import glob
import os
import os.path
import subprocess
import urllib.request

from properties import translate_property
from util import *


if not os.path.exists('server.jar'):
    print('Downloading server jar')
    urllib.request.urlretrieve(
        'https://piston-data.mojang.com/v1/objects/c9df48efed58511cdd0213c56b9013a7b5c9ac1f/server.jar', 'server.jar')

if not os.path.exists('generated'):
    print('Generating server data')
    subprocess.call(['java', '-DbundlerMainClass=net.minecraft.data.Main', '-jar', 'server.jar', '--reports', '--server'])


blocks = load_json('generated/reports/blocks.json')
blocks = sorted(blocks.items(), key=lambda item: min(map(lambda state: state['id'], item[1]['states'])))
registries = load_json('generated/reports/registries.json')
load_tags('blocks')
load_tags('entity_types')
load_tags('fluids')
load_tags('game_events')
load_tags('items')


# Clean output directory
for f in glob.glob('out/*'):
    os.remove(f)


hpp = CppFile('out/blocks.h')
hpp('#pragma once')
hpp('#include "../../src/block/Block.h"')

with hpp.block('namespace Blocks'):
    lines = []
    for block_name, block in blocks:
        block['short_name'] = block_name.replace('minecraft:', '')

        CppVariable(name=block['short_name'], type='extern const Block').render_to_string(hpp)
        line = 'const Block ' + block['short_name'] + ' = Block({"' + block['short_name'] + '"}, {' + ', '.join(map(lambda p: 'Properties::' + translate_property(block['short_name'], p), block.get('properties', {}).items())) + '}'

        for state in block['states']:
            if 'default' in state and state['default'] and 'properties' in state:
                line += ', {' + ', '.join(map(lambda v: '"' + v + '"', state['properties'].values())) + '}'

        line += ');'

        lines.append(line)

    lines_chunked = list(chunks(lines, 100))
    for n, file_lines in enumerate(lines_chunked):
        cppn = CppFile('out/blocks.' + str(n) + '.cpp')
        cppn('#include "blocks.h"')
        cppn('#include "../../src/block/property/properties.h"')
        with cppn.block('namespace Blocks'):
            for line in file_lines:
                cppn(line)
        cppn.close()

hpp.close()


cpp = CppFile('out/tags.h')
cpp('#pragma once')
cpp('#include <functional>')
cpp('#include <vector>')
cpp('#include "../../src/tags/Tag.h"')

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
hpp = CppFile('out/registries.h')
hpp('#pragma once')
hpp('#include "../../src/block/BlockRegistry.h"')
hpp('#include "../../src/item/ItemRegistry.h"')
cpp = CppFile('out/registries.cpp')
cpp('#include "registries.h"')

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
