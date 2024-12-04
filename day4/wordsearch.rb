class Wordsearch

  attr_reader :count
  def initialize(lines)
    @grid = lines
    @count = 0
  end

  def check_horizontal
    @grid.each do |line|
      @count += line.scan(/XMAS||SAMX/).length
    end
  end

  def check_vertical
    vertical_grid = []
    for i in 0..@grid[0].length
      for j in 0..@grid.length
        puts @grid[j]
      end
    end
  end

end