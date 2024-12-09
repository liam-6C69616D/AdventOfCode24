grid = []

File.foreach('input.txt') do |line|
  line.gsub!(/\n/, '')
  grid.push(line)
end

a_positions = []

(1...grid.length).each do |row_num|
  (1...grid[row_num].length).each do |col_num|
    if grid[row_num][col_num] == 'A'
      a_positions.push([row_num, col_num])
    end
  end
end

def check_cross(grid, a_pos)
  begin
    upper_left = grid[a_pos[0] - 1][a_pos[1] - 1]
    lower_right = grid[a_pos[0] + 1][a_pos[1] + 1]
    lower_left = grid[a_pos[0] + 1][a_pos[1] - 1]
    upper_right = grid[a_pos[0] - 1][a_pos[1] + 1]

    diag1 = upper_left + lower_right
    diag2 = lower_left + upper_right
  rescue # Catches errors pertaining to indices being out of bounds
    return false
  end

  if (diag1 == 'MS' || diag1 == 'SM') && (diag2 == 'MS' || diag2 == 'SM')
    return true
  else
    return false
  end

end

count = 0
for pos in a_positions
  if check_cross(grid, pos)
    count += 1
  end
end

puts count
