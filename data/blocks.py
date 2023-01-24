overrides = {
    '_bed': 'BlockBed',
    '_door': 'BlockDoor',
    '_fence_gate': 'BlockFenceGate',
    '_stairs': 'BlockStairs',
    '_trapdoor': 'BlockTrapdoor',
    'chest': 'BlockChest',
    'ender_chest': 'BlockEnderChest',
    'furnace': 'BlockFurnace',
    'repeater': 'BlockRepeater',
}

traits = {
    '_button': ['wallMountable'],
    'attached_melon_stem': ['orientable'],
    'attached_pumpkin_stem': ['orientable'],
    'carved_pumpkin': ['orientable'],
    'jack_o_lantern': ['orientableOpposite'],
    'ladder': ['wallMountable'],
    'soul_wall_torch': ['wallMountable'],
    'tripwire_hook': ['wallMountable'],
    'wall_torch': ['wallMountable'],
}


def test_pattern(pattern, block):
    return (pattern.startswith('_') and block.endswith(pattern)) or block == pattern


def block_to_class(block):
    for pattern, result in overrides.items():
        if type(pattern) is tuple:
            if any(test_pattern(p, block) for p in pattern):
                return result
        elif test_pattern(pattern, block):
            return result

    return 'Block'


def block_to_traits(block):
    for pattern, result in traits.items():
        if type(pattern) is tuple:
            if any(test_pattern(p, block) for p in pattern):
                return result
        elif test_pattern(pattern, block):
            return result

    return []
