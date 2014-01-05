require "./kata.char-iterator"

class KataSequenceIterator

  @sequence
  @start_position
  @end_position
  @inner_loop_end
  @match_map

  @current_position

  def initialize(sequence, start_position, end_position, inner_loop_end, match_map)
    @sequence = sequence
    @start_position = start_position
    @end_position = end_position
    @inner_loop_end = inner_loop_end
    @current_position = @start_position
    @match_map = match_map
  end

  def each
    match_iterator = self.next
    while (!match_iterator.nil?)
      yield match_iterator
      match_iterator = self.next
    end
  end

  def next
    return nil if is_done
    iterator = KataCharIterator.new(@sequence, @current_position, @inner_loop_end)
    @current_position -= 1
    return iterator
  end

  def push_match(count)
    @match_map << { position: @current_position + 1, count: count }
  end


  private

  def is_done
    @current_position < @end_position
  end

end
