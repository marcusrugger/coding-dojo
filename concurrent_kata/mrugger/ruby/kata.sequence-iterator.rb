require "./kata.match-iterator"

class KataSequenceIterator

  @sequence
  @end_position
  @match_map

  @current_position

  def initialize(sequence, end_position, match_map)
    @sequence = sequence
    @end_position = end_position
    @current_position = sequence.length - 1
    @match_map = match_map
  end

  def each
    while (!is_done)
      yield self.next
    end
  end

  def next
    return nil if is_done
    iterator = KataMatchIterator.new(@sequence, @current_position)
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
