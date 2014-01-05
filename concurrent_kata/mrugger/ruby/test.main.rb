require "./kata.char-iterator"
require "./kata.sequence-iterator"
require "./kata.worker"

#                         6         5         4         3         2         1  
#                9876543210987654321098765432109876543210987654321098765432109876543210
#                          1         2         3         4         5         6 
#                0123456789012345678901234567890123456789012345678901234567890123456789
kata_sequence = "8745648184845171326578518184151512461752149647129746915414816354846454"
#                               1326        415   246
#                                                   617


def should_eq(test_result, should_be_value, description)
  if test_result == should_be_value
    puts "success: #{description}, result: #{test_result}"
  else
    raise "fail: result: #{test_result}, should be: #{should_be_value}, #{description}"
  end
end


# Test KataWorker.match_count

test_sequence = "17119"
iterator = KataCharIterator.new(test_sequence, test_sequence.length - 1, 0)
should_eq(KataWorker.match_count(iterator), 3, "match_count: #{test_sequence}")

test_sequence = "15119"
iterator = KataCharIterator.new(test_sequence, test_sequence.length - 1, 0)
should_eq(KataWorker.match_count(iterator), 0, "match_count: #{test_sequence}")

test_sequence = "115119"
iterator = KataCharIterator.new(test_sequence, test_sequence.length - 1, 0)
should_eq(KataWorker.match_count(iterator), 5, "match_count: #{test_sequence}")


# Test KataBlockIterator

match_map = []
test_sequence = "911511912"
iterator = KataSequenceIterator.new(test_sequence, test_sequence.length - 1, 0, 0, match_map)
KataWorker.find_matches(iterator)
should_eq(match_map.count, 3, "match_map count")

match_map = []
iterator = KataSequenceIterator.new(kata_sequence, kata_sequence.length - 1, 0, 0, match_map)
KataWorker.find_matches(iterator)
should_eq(match_map.count, 4, "match_map count")
