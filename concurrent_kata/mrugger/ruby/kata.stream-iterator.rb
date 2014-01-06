require 'thread'
require "./kata.sequence-iterator"

class KataStreamIterator

  @sequence
  @block_size
  @queue

  @mutex

  def initialize(sequence, block_size, queue)
    @sequence = sequence
    @block_size = block_size
    @queue = queue
    @mutex = Mutex.new
  end

  def each
    it = self.next
    while !it.nil?
      yield it
      it = self.next
    end
  end

  def next
    next_block      = String.new
    end_position    = 0
    match_stack     = []

    @mutex.synchronize do
      return nil if @sequence.eof?

      end_position = @queue.size > 0 ? 8 : 0

      @sequence.rewind(8)
      bytes_read = @sequence.readbytes(@block_size, next_block)
      @queue << match_stack
    end

    return KataSequenceIterator.new(next_block, end_position, match_stack)
  end

end
