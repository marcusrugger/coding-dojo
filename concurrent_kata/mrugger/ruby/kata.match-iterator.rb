
class KataMatchIterator

  @sequence
  @current_position

  def initialize(sequence, start_position)
    @sequence = sequence
    @current_position = start_position
  end

  def each
    while (!is_done)
      yield self.next
    end
  end

  def current
    raise "iterator out of range" if is_done
    @sequence[@current_position].ord - '0'.ord
  end

  def next
    return nil if is_done
    rv = @sequence[@current_position].ord - '0'.ord
    @current_position -= 1
    return rv
  end

  def is_done
    @current_position < 0
  end

end
