targets = []
parts = []

File.foreach('input.txt') do |line|
  lineSplit = line.split(':')
  targets.push(lineSplit[0].to_i) 
  numbers = lineSplit[1].split.map { |elem| elem.to_i }
  parts.push(numbers)
end

def permute(numbers, target)
  found = false
  operations = ['+', '*', '||'].repeated_permutation(numbers.length - 1).to_a
  operations.each do |op|
    if evaluate(numbers, op) == target
      found = true
      break
    end
  end

  return found
end

def evaluate(numbers, operations)
  total = numbers[0]
  for i in 0...operations.length
    if operations[i] == '+'
      total += numbers[i+1]
    elsif operations[i] == '*'
      total *= numbers[i+1]
    else
      total = (total.to_s + numbers[i+1].to_s).to_i
    end
  end

  return total
end

sum = 0

for i in 0...targets.length
  if permute(parts[i], targets[i])
    sum += targets[i]
  end
end

puts sum