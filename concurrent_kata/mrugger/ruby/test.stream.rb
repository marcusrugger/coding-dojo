
class TestStream

  @sequence

  @total_sequence_length
  @current_position

  def initialize(sequence, replication_count)
    @sequence = sequence
    @total_sequence_length = sequence.length * replication_count
    @current_position = 0
  end

  def readbytes(count, block)
    copy_count = 0
    copy_count += copy_next_block(count - copy_count, block) while (copy_count < count && !eof?)
  end

  def rewind(count)
    @current_position = (@current_position > count) ? @current_position - count : 0
  end

  def eof?
    @current_position >= @total_sequence_length
  end


  private

  def copy_next_block(count, block)
    begin_index = @current_position % @sequence.length

    # Which ever is smaller
    copysize = [count,                                        # the requested number of characters
                @total_sequence_length - @current_position,   # what's left of the total replicated sequence
                @sequence.length - begin_index].min           # what's left in the sequence

    end_index = begin_index + copysize - 1

    block << @sequence[begin_index..end_index]
    @current_position += copysize
    return copysize
  end

end
