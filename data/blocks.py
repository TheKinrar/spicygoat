overrides = {
    '_stairs': 'BlockStairs',
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
