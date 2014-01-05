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


# Test concurrency

queue = []
iterator = KataBlockIterator.new(kata_sequence, 2, queue)

a = Thread.new { KataWorker.find_all_matches(iterator) }
b = Thread.new { KataWorker.find_all_matches(iterator) }

a.join
b.join

should_eq(queue.count, 35, "concurrency queue size")
queue.inject { |sum,x| sum + x }

total_matches = 0
queue.each { |map| total_matches += map.count }
should_eq(total_matches, 4, "concurrency matches")
