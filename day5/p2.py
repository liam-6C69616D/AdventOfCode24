import p1

def re_order(update : list) -> list:
    for page in update:
        for rule in rules:
            if page == rule[0] and rule[1] in update:
                rule_first_value_position = update.index(rule[0])
                rule_second_value_position = update.index(rule[1])

                if rule_first_value_position > rule_second_value_position:
                    move_value = update.pop(rule_first_value_position)
                    update.insert(rule_second_value_position, move_value)
    
    return update


if __name__ == '__main__':
    rules, updates = p1.readFileSplit('./input.txt')
    invalid = []

    for update in updates:
        if not p1.updateValid(update, rules):
            invalid.append(update)
    
    sum = 0
    for entry in invalid:
        new_order = re_order(entry)
        sum += p1.middleValue(new_order)

    print(sum)