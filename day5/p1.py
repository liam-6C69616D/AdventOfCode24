import math

def readFileSplit(path : str) -> tuple[list, list]:
    rules = []
    updates = []
    reading_rules = True
    with open(path, 'r') as file:
        for line in file.readlines():
            if line == '\n':
                reading_rules = False
                continue
            
            line = line.replace('\n', '')
            if reading_rules:
                split_rule = line.split('|')
                rules.append([split_rule[0], split_rule[1]])
            else:
                updates.append(line.split(','))
    
    return rules, updates

def updateValid(update : list, rules : list) -> bool:
    valid = True

    for page in update:
        for rule in rules:
            if page == rule[0] and rule[1] in update:
                if update.index(rule[0]) > update.index(rule[1]):
                    valid = False

    return valid

def middleValue(update : list) -> int:
    middle = math.floor(len(update) / 2)

    return int(update[middle])


if __name__ == '__main__':
    rules, updates = readFileSplit('./input.txt')
    valid = []

    for update in updates:
        if updateValid(update, rules):
            valid.append(update)
    
    sum = 0
    for entry in valid:
        sum += middleValue(entry)

    print(sum)