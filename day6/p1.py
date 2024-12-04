import time
import os

grid = []
moves = {
    '^': (-1, 0),
    '>': (0, 1),
    'v': (1, 0),
    '<': (0, -1)
}

turns = {
    '^': '>',
    '>': 'v',
    'v': '<',
    '<': '^'
}

current_pos = (-1, -1)
current_dir = ''

seen = []

def read_file(path : str) -> None:
    with open(path, 'r') as file:
        for line in file.readlines():
            line = line.replace('\n', '')
            grid.append(list(line))


def print_grid():
    os.system('cls')
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if [i,j] in seen:
                print('X', end='')
            else:
                print(grid[i][j], end='')
        print()

def get_pos_and_dir() -> tuple[int, int, str]:
    row = -1
    col = -1
    direction = ''
    for i in range(len(grid)):
        if any([char in grid[i] for char in "^<>v"]):
            row = i
    
    for j in range(len(grid[row])):
        if any([char in grid[row][j] for char in "^<>v"]):
            col = j

    direction = grid[row][col]

    return row, col, direction


def move() -> bool:
    global current_pos, current_dir
    add_tuple = moves[current_dir]
    current_pos = tuple(a + b for a, b in zip(current_pos, add_tuple))
    
    for val in current_pos:
        if val < 0 or val > len(grid[0]) - 1:
            return False

    if grid[current_pos[0]][current_pos[1]] == "#":
        current_pos = tuple(a - b for a, b in zip(current_pos, add_tuple))
        current_dir = turns[current_dir]


    return True

if __name__ == '__main__':
    read_file('./input.txt')
    pos_and_dir = get_pos_and_dir()
    current_pos, current_dir = pos_and_dir[:2], pos_and_dir[2]
    seen.append(list(current_pos))
    
    while move():
        if list(current_pos) not in seen:
            seen.append(list(current_pos))
    
    print(len(seen))
    