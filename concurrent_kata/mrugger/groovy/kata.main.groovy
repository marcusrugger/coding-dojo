

//                         6         5         4         3         2         1  
//                9876543210987654321098765432109876543210987654321098765432109876543210
//                          1         2         3         4         5         6 
//                0123456789012345678901234567890123456789012345678901234567890123456789
kata_sequence =  "8745648184845171326578518184151512461752149647129746915414816354846454"
//                               1326        415   246
//                                                   617


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
    return sequence.at(position--)
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
      //if (count > 0) print "${(position+1)}, "
      it = next()
    }
  }

  def next() {
    if (is_done()) return null
    return new MatchIterator(sequence, position--)
  }

  def is_done() { return position < 0 }
}


class StringSequencer
{
  def sequence_string

  StringSequencer(string) {
    sequence_string = string
  }

  def size() {
    return sequence_string.size()
  }

  def at(idx) {
    return ((int) sequence_string[idx]) - 48
  }
}


class UnboundedStringSequencer
{
  def sequence_string
  def total_sequence_size

  UnboundedStringSequencer(string, total_size) {
    sequence_string = string
    total_sequence_size = total_size
  }

  def size() {
    return total_sequence_size
  }

  def at(idx) {
    def sidx = idx % sequence_string.size()
    return ((int) sequence_string[sidx]) - 48
  }
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

//str = new String(kata_sequence)
str = new UnboundedStringSequencer(kata_sequence, 1000000)

thread_pool = []
for (a = 0; a < 4; a++) {
  sit = new SequenceIterator(str)
  t = Thread.start { sit.each(match_count) }
  thread_pool.push(t)
}

thread_pool.each { t -> t.join() }


a = [ 1, 2, 3 ]
println a
a += 4
println a
println a.tail()
println a.tail()
b = a.pop()
println b
println a
println a.size()
