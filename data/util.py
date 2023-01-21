import json
from pathlib import Path


tags = {}


def load_json(filename):
    with open(filename) as f:
        return json.load(f)


def load_tag(tag_type, tag_name):
    return load_json('generated/data/minecraft/tags/' + tag_type + '/' + tag_name + '.json')


def get_tag(tag_type, tag_name):
    if tag_type not in tags:
        tags[tag_type] = {}

    if tag_name not in tags[tag_type]:
        tags[tag_type][tag_name] = load_tag(tag_type, tag_name)

    return tags[tag_type][tag_name]


def load_tags(tag_type):
    for path in Path('generated/data/minecraft/tags/' + tag_type).glob('**/*.json'):
        filename = str(path.relative_to('generated/data/minecraft/tags/' + tag_type)).replace('\\', '/')
        if filename.endswith('.json'):
            tag_name = filename[:-5]
            get_tag(tag_type, tag_name)


def append_tag_ids(tag_type, registry, tag, dst):
    for v in tag['values']:
        if v.startswith('#'):
            append_tag_ids(tag_type, registry, get_tag(tag_type, v.replace('#minecraft:', '')), dst)
        else:
            dst.append(registry[v]['protocol_id'])


def sanitize(name):
    return name.replace('/', '_')


def chunks(lst, n):
    for i in range(0, len(lst), n):
        yield lst[i:i+n]
