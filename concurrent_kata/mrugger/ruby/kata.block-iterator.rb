require "./kata.match-iterator"

class KataBlockIterator

  @sequencer
  @is_done

  @current_iterator

  def initialize(sequencer)
    @sequencer = sequencer
  end

  def each
    @sequencer.each do |block_it|
      @current_iterator = block_it
      block_it.each { |it| yield it }
    end
  end

  def push_match(count)
    @current_iterator.push_match(count)
  end

end
