require "colorize"
require "./kata.match-iterator"
require "./kata.block-iterator"
require "./kata.stream-iterator"
require "./kata.worker"
require "./test.stream"

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

puts "Begin test..."

REPLICATION_COUNT = 10000
THREAD_COUNT = 2
BLOCK_SIZE = (kata_sequence.length * REPLICATION_COUNT) / THREAD_COUNT + 8

puts "Thread count:      #{THREAD_COUNT}"
puts "Replication count: #{REPLICATION_COUNT}"
puts "Block size:        #{BLOCK_SIZE}"

queue = []
stream = TestStream.new(kata_sequence, REPLICATION_COUNT)
stream_iterator = KataStreamIterator.new(stream, BLOCK_SIZE, queue)

thread_pool = []
for a in 1..THREAD_COUNT
  thread_pool << Thread.new do
    block_iterator = KataBlockIterator.new(stream_iterator)
    KataWorker.find_matches(block_iterator)
  end
end

thread_pool.each { |thread| thread.join }

total_matches = 0
queue.each { |map| total_matches += map.count }
should_eq(total_matches, 4 * REPLICATION_COUNT, "concurrency matches")
