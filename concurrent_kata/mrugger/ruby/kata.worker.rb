
class KataWorker

  def self.find_matches(iterator)
    iterator.iterate! { |match_iterator| match_count(match_iterator) }
  end

  def self.match_count(iterator)
    sum   = 0
    count = 0
    value = iterator.next

    iterator.each do |char|
      sum += char
      count += 1
      break if sum >= value
    end

    sum == value ? count : 0
  end

end
