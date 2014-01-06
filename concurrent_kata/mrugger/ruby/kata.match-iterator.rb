
class KataMatchIterator

  @sequence
  @current_position

  def initialize(sequence, start_position)
    @sequence = sequence
    @current_position = start_position
  end

  def current
    raise "iterator out of range" if is_done
    @sequence[@current_position].ord - '0'.ord
  end

  def next
    raise "iterator out of range" if is_done
    @current_position -= 1
  end

  def is_done
    @current_position < 0
  end

end
