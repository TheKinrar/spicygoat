from code_generation.cpp_generator import *
from code_generation.code_generator import *
import os.path
import subprocess
import urllib.request

from util import *


if not os.path.exists('server.jar'):
    print('Downloading server jar')
    urllib.request.urlretrieve(
        'https://piston-data.mojang.com/v1/objects/c9df48efed58511cdd0213c56b9013a7b5c9ac1f/server.jar', 'server.jar')

if not os.path.exists('generated'):
    print('Generating server data')
    subprocess.call(['java', '-DbundlerMainClass=net.minecraft.data.Main', '-jar', 'server.jar', '--reports', '--server'])


blocks = load_json('generated/reports/blocks.json')
registries = load_json('generated/reports/registries.json')
load_tags('blocks')
load_tags('entity_types')
load_tags('fluids')
load_tags('game_events')
load_tags('items')


hpp = CppFile('out/blocks.h')
hpp('#pragma once')
hpp('#include "../../src/world/chunks/ChunkPalette.h"')
cpp = CppFile('out/blocks.cpp')
cpp('#include "blocks.h"')

with hpp.block('namespace Blocks'), cpp.block('namespace Blocks'):
    lines = []
    for block_name, block in blocks.items():
        for state in block['states']:
            props = []

            if 'properties' in state:
                for k, v in state['properties'].items():
                    props.append('{"' + k + '", "' + v + '"}')

            lines.append('palette.addBlockState(BlockState("' + block_name + '", {' + ', '.join(props) + '}), ' + str(state['id']) + ');')

    lines_chunked = list(chunks(lines, 1000))
    for n, file_lines in enumerate(lines_chunked):
        def impl(self, cpp):
            for line in file_lines:
                cpp(line)

        cppn = CppFile('out/blocks.' + str(n) + '.cpp')
        cppn('#include "blocks.h"')
        with cppn.block('namespace Blocks'):
            fun = CppFunction(name='load_' + str(n), ret_type='void', implementation_handle=impl)
            fun.add_argument('ChunkPalette& palette')
            fun.declaration().render_to_string(hpp)
            fun.definition().render_to_string(cppn)
        cppn.close()

    def impl(self, cpp):
        for n in range(0, len(lines_chunked)):
            cpp('load_' + str(n) + '(palette);')

    fun = CppFunction(name='load', ret_type='void', implementation_handle=impl)
    fun.add_argument('ChunkPalette& palette')
    fun.declaration().render_to_string(hpp)
    fun.definition().render_to_string(cpp)


hpp.close()
cpp.close()


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


registry_classes = {'item': 'ItemRegistry'}
registry_names = ['entity_type', 'item']
hpp = CppFile('out/registries.h')
hpp('#pragma once')
hpp('#include "../../src/item/ItemRegistry.h"')
cpp = CppFile('out/registries.cpp')
cpp('#include "registries.h"')

with hpp.block('namespace Registries'), cpp.block('namespace Registries'):
    for registry_name in registry_names:
        var_type = None
        var_init = None
        if registry_name in registry_classes:
            var_type = registry_classes[registry_name]
            var_init = var_type + '()'
        else:
            var_type = 'Registry'
            var_init = 'Registry("minecraft:' + registry_name + '")'

        CppVariable(name=registry_name, type='inline ' + var_type, initialization_value=var_init)\
            .render_to_string(hpp)

    def impl(self, cpp):
        for registry_name in registry_names:
            registry = registries['minecraft:' + registry_name]
            if 'default' in registry:
                cpp(registry_name + '.defaultKey = "' + registry['default'] + '";')

            for entry_name, entry in registry['entries'].items():
                cpp(registry_name + '.addMapping("' + entry_name + '", ' + str(entry['protocol_id']) + ');')

    fun = CppFunction(name='load', ret_type='void', implementation_handle=impl)
    fun.declaration().render_to_string(hpp)
    fun.definition().render_to_string(cpp)

hpp.close()
cpp.close()


print('Done.')
