
class KataWorker

  def self.find_all_matches(iterator)
    iterator.each { |sequence_iterator| find_matches(sequence_iterator) }
  end

  def self.find_matches(iterator)
    iterator.each do |match_iterator|
      count = match_count(match_iterator)
      iterator.push_match(count) if count > 0
    end
  end

  def self.match_count(iterator)
    sum = 0
    count = 0

    value = iterator.current
    iterator.next

    while (!iterator.is_done && sum < value) do
      sum += iterator.current
      count += 1
      iterator.next
    end

    sum == value ? count : 0
  end

end
