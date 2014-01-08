
class UnboundedMatchIterator
{
  def sequence
  def int position
  def int end_position

  UnboundedMatchIterator(seq) {
    sequence = seq
    position = -1
    end_position = 0
  }

  def reset(int start, int stop) {
    position = start
    end_position = stop
  }

  def next() {
    if (is_done()) return '\0'
    return sequence.at(position--)
  }

  def is_done() { return position < end_position }
}


class UnboundedSequenceIterator
{
  def sequence
  def match_map
  def int position
  def int stop_position
  def int match_stop_position
  def UnboundedMatchIterator match_iterator

  UnboundedSequenceIterator(seq, map, start, stop, match_stop) {
    sequence = seq
    match_map = map
    position = start
    stop_position = stop
    match_stop_position = match_stop
    match_iterator = new UnboundedMatchIterator(seq)
  }

  def each(Closure yield) {
    def it = next()
    while (it != null) {
      def count = yield(it)
      push_match_count(count)
      it = next()
    }
  }

  def next() {
    if (is_done()) return null
    match_iterator.reset(position--, match_stop_position)
    return match_iterator
  }

  def is_done() { return position < stop_position }

  def push_match_count(int count)
  {
    if (count) match_map.push(position+1)
  }
}


class UnboundedStringSequencer
{
  def sequence_string
  def int total_sequence_size

  UnboundedStringSequencer(string, total_size) {
    sequence_string = string
    total_sequence_size = total_size
  }

  def at(idx) {
    def sidx = idx % sequence_string.size()
    return ((int) sequence_string[sidx]) - 48
  }
}



//                         6         5         4         3         2         1  
//                9876543210987654321098765432109876543210987654321098765432109876543210
//                          1         2         3         4         5         6 
//                0123456789012345678901234567890123456789012345678901234567890123456789
kata_sequence =  "8745648184845171326578518184151512461752149647129746915414816354846454"
//                               1326        415   246
//                                                   617



determine_match_count = { iterator ->
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



THREAD_COUNT = 4
SEQUENCE_LENGTH = 10000000

//str = new String(kata_sequence)
str = new UnboundedStringSequencer(kata_sequence, SEQUENCE_LENGTH)

iterator_pool = []
thread_pool = []
for (a = 0; a < THREAD_COUNT; a++) {
  ArrayList<Integer> map = new ArrayList<Integer>()
  def sit = new UnboundedSequenceIterator(str, map, SEQUENCE_LENGTH-1, 0, 0)
  iterator_pool.push(sit)
  t = Thread.start { sit.each(determine_match_count) }
  thread_pool.push(t)
}

thread_pool.each { t -> t.join() }

iterator_pool.each { it -> println "stack size: ${it.match_map.size()}" }
