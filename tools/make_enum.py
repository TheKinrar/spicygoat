enum_name = input("Enum name: ")

values = []
while True:
    value = input("Value (. for end): ")
    if value == '.':
        break

    values.append(value)


with open(enum_name + '.h', 'w') as f:
    indent = 0

    def write(line):
        for i in range(0, indent):
            f.write(' ')
        f.write(line)
        f.write('\n')

    write('#pragma once\n')
    write('#include "../../util/Enum.h"\n')
    write('class ' + enum_name + ' : public Enum {')
    indent = 4
    write('explicit ' + enum_name + '(const std::string& name) : Enum(name) {}\n')
    indent = 3
    write('public:')
    indent = 4
    write('static const ' + enum_name + ' ' + ', '.join(values) + ';\n')
    write('static const std::vector<' + enum_name + '> values;')
    indent = 0
    write('};\n')

    for value in values:
        write('inline const ' + enum_name + ' ' + enum_name + '::' + value + ' = ' + enum_name + '("' + value + '");')

    write('\ninline const std::vector<' + enum_name + '> ' + enum_name + '::values = {' + ', '.join(values) + '};')
