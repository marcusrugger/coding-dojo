require "./kata.match-iterator"

class KataBlockIterator

  @sequencer
  @is_done

  @current_iterator

  def initialize(sequencer)
    @sequencer = sequencer
    @current_iterator = sequencer.next
  end

  def each
    it = self.next
    while (!it.nil?)
      yield it
      it = self.next
    end
  end

  def next
    return nil if @is_done
    rv = @current_iterator.next
    if rv.nil?
      @current_iterator = @sequencer.next
      return nil if is_done
      rv = @current_iterator.next
    end
    return rv
  end

  def push_match(count)
    @current_iterator.push_match(count)
  end


  private

  def is_done
    @current_iterator.nil?
  end

end
