

class MatchIterator
{
  def sequence
  def position

  MatchIterator(seq, pos) {
    sequence = seq
    position = pos
  }

  def next() {
    if (is_done()) return '\0'
    return ((int) sequence[position--]) - 48
  }

  def is_done() { return position < 0 }
}


class SequenceIterator
{
  def sequence
  def position

  SequenceIterator(seq) {
    sequence = seq
    position = sequence.size() - 1
  }

  def each(Closure yield) {
    def it = next()
    while (it != null) {
      def count = yield(it)
      println "SequenceIterator: " + count
      it = next()
    }
  }

  def next() {
    if (is_done()) return null
    return new MatchIterator(sequence, position--)
  }

  def is_done() { return position < 0 }
}


match_count = { iterator ->
  def sum   = 0
  def count = 0
  def value = iterator.next()

  def c = iterator.next()
  while (c != '\0' && sum < value) {
    sum += c
    count++
    c = iterator.next()
  }

  return sum == value ? count : 0;
}

def find_solutions(iterator) { iterator.each(match_count) }

str = new String("123123123123123123123")
sit = new SequenceIterator(str)
find_solutions(sit)
