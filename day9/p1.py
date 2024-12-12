import time

def readFile():
    with open('src/input.txt', 'r') as file:
        return file.read()

def parse(contents):
    block_index = 0
    file = True
    new_output = []
    for char in contents:
        if file:
            for i in range(int(char)):
                new_output.append(block_index)
            file = False
            block_index += 1
        else:
            for i in range(int(char)):
                new_output.append('.')
            file = True
                
    return new_output

def move_from_end(parsed_contents):
    write_pos = 0
    for i in range(len(parsed_contents)-1, -1, -1):
        if (parsed_contents[i] != '.'):
            while parsed_contents[write_pos] != '.':
                write_pos += 1
            if write_pos < i:
                parsed_contents[write_pos] = parsed_contents[i]
                parsed_contents[i] = '.'
    
    return parsed_contents

def checksum(line):
    checksum = 0
    for i in range(len(line)):
        if line[i] != '.':
            checksum += i * int(line[i])
    
    return checksum
    

if __name__ == '__main__':
    file_contents = readFile()
    parsed = parse(file_contents)
    moved = move_from_end(parsed)
    print(checksum(moved))
