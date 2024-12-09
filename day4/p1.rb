require_relative 'wordsearch'

lines = []

File.foreach('input.txt') do |line|
  lines.push(line)
end

search = Wordsearch.new(lines)
search.check_horizontal
search.check_vertical
search.check_diag

puts search.count