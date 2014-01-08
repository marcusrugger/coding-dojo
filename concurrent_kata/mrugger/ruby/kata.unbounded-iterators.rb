
class KataUnboundedCharIterator

  @sequence
  @current_position
  @end_position

  def initialize(sequence)
    @sequence = sequence
    @current_position = -1
    @end_position = 0
  end

  def reset(start, stop)
    @current_position = start
    @end_position = stop
  end

  def each
    yield self.next while !is_done
  end

  def next
    return nil if is_done
    rv = @sequence.at(@current_position)
    @current_position -= 1
    return rv
  end

  def is_done
    @current_position < @end_position
  end

end


class KataUnboundedSequenceIterator

  attr_accessor :match_map

  @sequence
  @match_map

  @match_iterator

  @current_position
  @end_position
  @match_end

  def initialize(sequence, match_map, start_position, end_position, match_end)
    @sequence = sequence
    @match_map = match_map
    @end_position = end_position
    @current_position = start_position
    @match_end = match_end
    @match_iterator = KataUnboundedCharIterator.new(@sequence)
  end

  def iterate!
    self.each do |match_it|
      match_count = yield match_it
      self.push_match(match_count) if match_count > 0
    end
  end

  def each
    yield self.next while !is_done
  end

  def next
    return nil if is_done
    @match_iterator.reset(@current_position, @match_end)
    @current_position -= 1
    return @match_iterator
  end

  def push_match(count)
    @match_map << { position: @current_position + 1, count: count }
  end


  private

  def is_done
    @current_position < @end_position
  end

end


class KataUnboundedSequencer

  @sequence
  @current_position

  def initialize(sequence, total_sequence_size)
    @sequence = sequence
    @current_position = total_sequence_size
  end

  def at(idx)
    @sequence[idx % @sequence.length].ord - '0'.ord
  end

end
