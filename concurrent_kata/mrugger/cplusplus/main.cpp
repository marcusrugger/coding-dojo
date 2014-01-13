#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "thread.h"
#include "sequencer.h"


int match_count(const int count, const char_iterator &char_it, const char val)
{
  const char new_val = val - char_it();

  if (new_val > 0 && char_it.is_more())
    return match_count(count+1, char_it.next(), new_val);
  else if (new_val == 0)
    return count+1;
  else
    return 0;
}


accumulator for_each(const accumulator acc, const sequence_iterator &s_it, const std::function<int(const char_iterator &)> fn)
{
  int cnt = fn(s_it());
  if (cnt)
  {
    accumulator new_acc = acc;
    new_acc.push_back(match_pair(s_it.to_i(), cnt));

    if (s_it.is_more()) 
      return for_each(new_acc, s_it.next(), fn);
    else
      return new_acc;
  }
  else
  {
    if (s_it.is_more()) 
      return for_each(acc, s_it.next(), fn);
    else
      return acc;
  }
}


accumulator adsffor_each(const accumulator acc, const sequence_iterator &s_it, const std::function<int(const char_iterator &)> fn)
{
  accumulator new_acc = acc;

  int cnt = fn(s_it());
  if (cnt) new_acc.push_back(match_pair(s_it.to_i(), cnt));

  if (s_it.is_more()) 
    return for_each(new_acc, s_it.next(), fn);
  else
    return new_acc;
}


void split_sequence(accumulator &acc, const sequencer &seq, const int count)
{
  if (seq.length() > 512)
  {
    sequencer seq_front = seq.clone_front_half();
    mythread t(split_sequence, acc, seq_front, count+1);

    accumulator back_acc;
    sequencer seq_back = seq.clone_back_half();
    split_sequence(back_acc, seq_back, count+1);

    t.join();
    acc.insert(acc.end(), back_acc.begin(), back_acc.end());
  }
  else
  {
    sequence_iterator seq_it = seq.get_sequence_iterator();
    accumulator seq_acc = for_each(acc, seq_it, [](const char_iterator &char_it) -> int {
      if (char_it.is_more())
        return match_count(1, char_it.next(), char_it());
      else
        return 0;
    });
    acc.insert(acc.end(), seq_acc.begin(), seq_acc.end());
  }
}


static void print_match(const match_pair p, const sequencer &seq)
{
  const sequencer block = seq.clone_block(p.first-p.second+1, p.second);
  printf("Position: %3d, characters: %d, %s\n", p.first, p.second, block.to_s().c_str());
}


static void print_list(const accumulator &list, const sequencer &seq)
{
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Application done: " << ctime(&tt);
  std::cout << "list size: " << list.size() << std::endl;

  std::for_each(list.begin(), std::next(list.begin(), 10), [seq](match_pair p) {
    const sequencer block = seq.clone_block(p.first, p.second);
    printf("Position: %3d, characters: %d, %s\n", p.first, p.second, block.to_s().c_str());
  });
}


int main(int argc, char **argv)
{
  mythread::set_max_tree_depth();
  const int replications = 1000000;

  std::string str("8745648184845171326578518184151512461752149647129746915414816354846454");
  sequencer seq(str, replications);
  accumulator acc;
  acc.reserve(4 * replications);
  std::cout << "vector capacity: " << acc.capacity() << std::endl;
  split_sequence(acc, seq, 0);

  print_list(acc, seq);
}
