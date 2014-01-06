require "./kata.match-iterator"

class KataBlockIterator

  @sequencer
  @is_done

  def initialize(sequencer)
    @sequencer = sequencer
  end

  def iterate!
    self.each { |match_it| yield match_it }
  end

  def each
    @sequencer.each do |sequence_it|
      sequence_it.iterate! { |it| yield it }
    end
  end

end
