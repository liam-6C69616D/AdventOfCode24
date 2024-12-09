class Wordsearch

  attr_reader :count
  def initialize(lines)
    @grid = lines
    @grid = @grid.map(&:chomp) # Notation is shorthand for @grid.map {|element| element.chomp} or @grid.map do |element| element.chomp end
    @count = 0
  end

  def check_horizontal
    @grid.each do |line|
      @count += line.scan(/XMAS/).length
      @count += line.scan(/SAMX/).length
    end
  end

  def check_vertical
    rows = @grid.length
    columns = @grid.first.length

    (0...columns).each do |col|
      vertical = (0...rows).map { |row| @grid[row][col] }.join
      @count += vertical.scan(/XMAS/).length
      @count += vertical.scan(/SAMX/).length
    end

  end

  def check_diag
    rows = @grid.length
    columns = @grid.first.length

    diagonals = []

    # Diagonals starting from the top row
    (0...columns).each do |c|
      diag = ""
      row, col = 0, c
      while row < rows && col < columns
        diag += @grid[row][col]
        row += 1
        col += 1
      end

      diagonals.append(diag)
    end

    # Diagonals starting from the left column
    (1...rows).each do |r|
      diag = ""
      row, col = r, 0
      while row < rows && col < columns
        diag += @grid[row][col]
        row += 1
        col += 1
      end

      diagonals.append(diag)
    end

    # Diagonals starting top row (right to left)
    (columns - 1).downto(0) do |c|
      diag = ""
      row, col = 0, c
      while row < rows && col >=0
        diag += @grid[row][col]
        row += 1
        col -= 1
      end

      diagonals.append(diag)
    end

    # Diagonals starting right column (right to left)
    (1...rows).each do |r|
      diag = ""
      row, col = r, columns - 1
      while row < rows && col >= 0
        diag += @grid[row][col]
        row += 1
        col -= 1
      end

      diagonals.append(diag)
    end

    diagonals.each do |line|
      @count += line.scan(/XMAS/).length
      @count += line.scan(/SAMX/).length
    end

  end

end