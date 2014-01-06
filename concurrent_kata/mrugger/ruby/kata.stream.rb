
class KataStream

  @sequence
  @replication_count

  @total_sequence_length
  @current_position

  def initialize(sequence, replication_count)
    @sequence = sequence
    @replication_count = replication_count
    @total_sequence_length = sequence.length * replication_count
    @current_position = 0
  end

  def readbytes(count, block)
    copy_count = copy_next_block(count, block)
    count -= copy_count
    total_copy_count = copy_count

    while (count > 0 && !eof?)
      copy_count = copy_next_block(count, block)
      count -= copy_count
      total_copy_count += copy_count
    end
    
    total_copy_count
  end

  def rewind(count)
    @current_position = (@current_position > count) ? @current_position - count : 0
  end

  def eof?
    @current_position >= @total_sequence_length
  end


  private

  def copy_next_block(count, block)
    readcount = [count, @total_sequence_length - @current_position].min

    begin_index = @current_position % @sequence.length
    copysize = [readcount, @sequence.length - begin_index].min
    end_index = begin_index + copysize - 1

    block << @sequence[begin_index..end_index]
    @current_position += copysize
    return copysize
  end

end
