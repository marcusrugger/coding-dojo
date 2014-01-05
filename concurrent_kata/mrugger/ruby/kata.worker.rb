
class KataWorker

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

  def self.find_matches(iterator)
    match_iterator = iterator.next
    while (!match_iterator.nil?) do
      count = match_count(match_iterator)
      iterator.push_match(count) if count > 0
      match_iterator = iterator.next
    end
  end

  def self.find_all_matches(iterator)
    sequence_iterator = iterator.next
    while (!sequence_iterator.nil?) do
      find_matches(sequence_iterator)
      sequence_iterator = iterator.next
    end
  end

end
