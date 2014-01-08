
class KataUnboundedCharIterator

  @sequence
  @current_position
  @end_position

  def initialize(sequence, start=-1, stop=0)
    @sequence = sequence
    @current_position = start
    @end_position = stop
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

  @idx
  @sequencer
  @match_map

  @match_iterator

  @current_position
  @end_position
  @match_end

  def initialize(idx, sequencer, match_map, start_position, end_position, match_end)
    @idx = idx
    @sequencer = sequencer
    @match_map = match_map
    @end_position = end_position
    @current_position = start_position
    @match_end = match_end
    @match_iterator = KataUnboundedCharIterator.new(sequencer)
  end

  def iterate!
    self.each do |match_it|
      push_match(yield match_it)
    end
  end

  def each
    yield get_next while !is_done
  end

  def get_next
    return nil if is_done
    @match_iterator.reset(@current_position, @match_end)
    @current_position -= 1
    return @match_iterator
  end

  def push_match(count)
    @match_map << { position: @current_position + 1, count: count } if count > 0
  end


  private

  def is_done
    @current_position < @end_position
  end

end


class KataUnboundedSequencer

  @sequence
  @sequence_length
  @current_position

  def initialize(sequence, total_sequence_size)
    @sequence = sequence
    @sequence_length = sequence.length
    @current_position = total_sequence_size
  end

  def at(idx)
    @sequence[idx % @sequence_length].ord - '0'.ord
  end

end
