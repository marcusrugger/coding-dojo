require "colorize"
require "./kata.char-iterator"
require "./kata.sequence-iterator"
require "./kata.block-iterator"
require "./kata.worker"

#                         6         5         4         3         2         1  
#                9876543210987654321098765432109876543210987654321098765432109876543210
#                          1         2         3         4         5         6 
#                0123456789012345678901234567890123456789012345678901234567890123456789
kata_sequence = "8745648184845171326578518184151512461752149647129746915414816354846454"
#                               1326        415   246
#                                                   617


def should_eq(test_result, expected_value, description)
  if test_result == expected_value
    puts "success: #{description}, result: #{test_result}"
  else
    puts "FAIL: result: #{test_result}, should be: #{expected_value}, #{description}".red
  end
end


def check_pair(pair, expected_position, expected_count, description)
  should_eq(pair[:position], expected_position, description)
  should_eq(pair[:count], expected_count, description)
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


# Test KataWorker.find_matches

match_map = []
test_sequence = "911511912"
iterator = KataSequenceIterator.new(test_sequence, test_sequence.length - 1, 0, 0, match_map)
KataWorker.find_matches(iterator)
should_eq(match_map.count, 3, "match_map count")

match_map = []
iterator = KataSequenceIterator.new(kata_sequence, kata_sequence.length - 1, 0, 0, match_map)
KataWorker.find_matches(iterator)
should_eq(match_map.count, 4, "match_map count")
check_pair(match_map.pop, 18, 3, "kata_sequence, match 1")
check_pair(match_map.pop, 29, 2, "kata_sequence, match 2")
check_pair(match_map.pop, 35, 2, "kata_sequence, match 3")
check_pair(match_map.pop, 37, 2, "kata_sequence, match 4")


# Test KataWorker.find_all_matches

queue = []
iterator = KataBlockIterator.new(kata_sequence, 15, queue)
KataWorker.find_all_matches(iterator)
should_eq(queue.count, 5, "queue size")
should_eq(queue.shift.count, 0, "kata_sequence, stack 1")

match_map = queue.shift
should_eq(match_map.count, 2, "kata_sequence, stack 2")
check_pair(match_map.pop, 18, 3, "kata_sequence, stack 2, match 1")
check_pair(match_map.pop, 29, 2, "kata_sequence, stack 2, match 2")

match_map = queue.shift
should_eq(match_map.count, 2, "kata_sequence, stack 3")
check_pair(match_map.pop, 35, 2, "kata_sequence, stack 3, match 1")
check_pair(match_map.pop, 37, 2, "kata_sequence, stack 3, match 2")

should_eq(queue.shift.count, 0, "kata_sequence, stack 4")
should_eq(queue.shift.count, 0, "kata_sequence, stack 5")
