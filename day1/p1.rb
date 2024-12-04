list1 = []
list2 = []

File.foreach('input.txt') do |line|
    split = line.split
    list1.push(split[0])
    list2.push(split[1])
end

list1.sort!
list2.sort!

pairs = list1.zip(list2)

tally = 0
pairs.each { |pair| tally += (pair[0].to_i - pair[1].to_i).abs }

puts tally