#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "thread.h"
#include "sequencer.h"


accumulator match_count(accumulator acc, const int count, const char_iterator &char_it, const char val)
{
  const char new_val = val - char_it();

  if (new_val > 0 && char_it.is_more())
    return match_count(acc, count+1, char_it.next(), new_val);
  else if (new_val == 0)
    acc.push_back(match_pair(char_it.to_i(), count+1));

  return acc;
}


accumulator for_each(accumulator acc, const sequence_iterator &s_it, const std::function<accumulator(accumulator &, const char_iterator &)> fn)
{
  accumulator rv = fn(acc, s_it());
  if (s_it.is_more()) 
    return for_each(rv, s_it.next(), fn);
  else
    return rv;
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
    accumulator seq_acc = for_each(acc, seq_it, [](accumulator acc, const char_iterator &char_it) -> accumulator {
      if (char_it.is_more())
        return match_count(acc, 1, char_it.next(), char_it());
      else
        return acc;
    });
    acc.insert(acc.end(), seq_acc.begin(), seq_acc.end());
  }
}


static void print_match(const match_pair p, const sequencer &seq)
{
  const sequencer block = seq.clone_block(p.first, p.second);
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
