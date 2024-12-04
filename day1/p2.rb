list1 = []
list2 = []

File.foreach('input.txt') do |line|
  split = line.split
  list1.push(split[0])
  list2.push(split[1])
end

total = 0

list1.each do |val|
  count = 0
  list2.each do |l2|
    if val == l2
      count += 1
    end
  end
  total += val.to_i * count
end

puts total