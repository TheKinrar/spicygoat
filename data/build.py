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


registries = load_json('generated/reports/registries.json')
load_tags('blocks')
load_tags('entity_types')
load_tags('fluids')
load_tags('game_events')
load_tags('items')


cpp = CppFile('include/tags.h')
cpp('#include <functional>')
cpp('#include <vector>')
cpp('#include "../../src/tags/Tag.h"')

with cpp.block('namespace Tags'):
    for tag_type in tags:
        with cpp.block('namespace ' + tag_type):
            for tag_name, tag in tags[tag_type].items():
                ids = []
                append_tag_ids(tag_type, registries['minecraft:' + tag_type[:-1]]['entries'], tag, ids)

                CppVariable(name=sanitize(tag_name), type='Tag', initialization_value='Tag("minecraft:' + tag_name + '", {' + ', '.join(map(lambda e: str(e), ids)) + '})')\
                    .render_to_string(cpp)

            CppVariable(name='All', type='std::vector<std::reference_wrapper<Tag>>', initialization_value='{' + ', '.join(map(lambda e: sanitize(e), tags[tag_type])) + '}') \
                .render_to_string(cpp)

cpp.close()


print('Done.')
