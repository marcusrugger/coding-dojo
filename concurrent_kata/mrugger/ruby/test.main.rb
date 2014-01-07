require 'colorize'
require './kata.unbounded-iterators'
require './kata.worker'

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


# Test KataWorker.find_matches

puts "Starting test..."

THREAD_COUNT = 4
SEQUENCE_LENGTH = 1000000

thread_pool = []
iterator_pool = []

sequencer = KataUnboundedSequencer.new(kata_sequence, SEQUENCE_LENGTH)

for a in 1..THREAD_COUNT
  match_map = []
  iterator = KataUnboundedSequenceIterator.new(sequencer, match_map, SEQUENCE_LENGTH-1, 0, 0)
  iterator_pool << iterator
  thread_pool << Thread.new { iterator.iterate! { |it| KataWorker.match_count(it) } }
end

thread_pool.each { |t| t.join }

iterator_pool.each { |it| puts "stack size: #{iterator.match_map.size}"}

puts "All done."
