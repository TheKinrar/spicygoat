def item_to_class(item, blocks):
    if 'minecraft:' + item in blocks:
        return 'BlockItem', ['Blocks::' + item]

    return 'Item', []
