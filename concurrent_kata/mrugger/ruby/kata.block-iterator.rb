require "./kata.sequence-iterator"

class KataBlockIterator

  @sequence
  @block_size
  @queue

  @current_position
  @end_of_sequence

  def initialize(sequence, block_size, queue)
    @sequence = sequence
    @block_size = block_size
    @queue = queue
    @current_position = 0
    @end_of_sequence = sequence.length - 1
  end

  def next
    return nil if is_done

    puts "current_position: #{@current_position}"

    start_position  = [next_start_position, @end_of_sequence].min
    end_position    = next_end_position
    inner_loop_end  = next_inner_loop_end
    match_stack     = []

    @queue << match_stack
    increment_current_position_to_next_block

    return KataSequenceIterator.new(@sequence, start_position, end_position, inner_loop_end, match_stack)
  end

  private

  def is_done
    @current_position > @end_of_sequence
  end

  def next_start_position
    @current_position + @block_size - 1
  end

  def next_end_position
    @current_position
  end

  def next_inner_loop_end
    (@current_position > 8) ? @current_position - 8 : 0
  end

  def increment_current_position_to_next_block
    @current_position += @block_size
  end

end
