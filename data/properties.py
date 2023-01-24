countable = {
    'age': {2: 'age_1', 3: 'age_2', 4: 'age_3', 5: 'age_4', 6: 'age_5', 8: 'age_7', 16: 'age_15', 26: 'age_25'},
    'distance': {7: 'distance_1_7', 8: 'distance_0_7'},
    'facing': {4: 'horizontal_facing', 5: 'hopper_facing', 6: 'facing'},
    'level': {3: 'level_3', 8: 'level_1_8', 9: 'level_8', 16: 'level_15'},
}

overrides = {
    'axis': {'nether_portal': 'horizontal_axis'},
    'east': {'_wall': 'east_wall_shape', 'redstone_wire': 'east_wire_connection'},
    'face': {('_button', 'grindstone', 'lever'): 'wall_mount_location'},
    'facing': {'_bed': 'horizontal_facing', 'hopper': 'hopper_facing'},
    'half': {('_door', 'large_fern', 'lilac', 'peony', 'rose_bush',
              'small_dripleaf', 'sunflower', 'tall_grass', 'tall_seagrass'): 'double_block_half',
             ('_stairs', '_trapdoor'): 'block_half'},
    'hinge': {'_door': 'door_hinge'},
    'orientation': {'jigsaw': 'jigsaw_orientation'},
    'leaves': {'bamboo': 'bamboo_leaves'},
    'mode': {'comparator': 'comparator_mode', 'structure_block': 'structure_block_mode'},
    'north': {'_wall': 'north_wall_shape', 'redstone_wire': 'north_wire_connection'},
    'part': {'_bed': 'bed_part'},
    'shape': {'_rail': 'straight_rail_shape', '_stairs': 'stair_shape', 'rail': 'rail_shape'},
    'short': {'piston_head': 'short_head'},
    'south': {'_wall': 'south_wall_shape', 'redstone_wire': 'south_wire_connection'},
    'type': {('chest', 'trapped_chest'): 'chest_type',
             ('moving_piston', 'piston_head'): 'piston_type', '_slab': 'slab_type'},
    'west': {'_wall': 'west_wall_shape', 'redstone_wire': 'west_wire_connection'},
}

reorder = {
    ('chest', 'trapped_chest'): {0: 1},
    'moving_piston': {0: 1},
    'piston_head': {0: 2},
}


def reorder_array(array, recipe):
    for a, b in recipe.items():
        array.insert(b, array.pop(a))


def reorder_properties(block, props):
    for pattern, result in reorder.items():
        if type(pattern) is tuple:
            if any(test_pattern(p, block) for p in pattern):
                reorder_array(props, result)
        elif test_pattern(pattern, block):
            reorder_array(props, result)


def test_pattern(pattern, block):
    return (pattern.startswith('_') and block.endswith(pattern)) or block == pattern


def translate_property(block, p):
    (prop, values) = p
    val_len = len(values)

    if prop in countable:
        return countable[prop][val_len]

    if prop in overrides:
        for pattern, result in overrides[prop].items():
            if type(pattern) is tuple:
                if any(test_pattern(p, block) for p in pattern):
                    return result
            elif test_pattern(pattern, block):
                return result

    return prop
