#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "test.main.h"


static std::string bool_to_string(bool flag)
{ return flag ? "true" : "false"; }


void should_eq(bool test_result, bool should_be, std::string description)
{
  if (test_result != should_be)
  {
    std::ostringstream ss;
    ss << description << ": was (" << bool_to_string(test_result) << "), should be (" << bool_to_string(should_be) << ")";
    throw std::runtime_error(ss.str());
  }
  else
  {
    std::cout << "success: " << description << ", result: " << test_result << "\n";
  }
}


void should_eq(int test_result, int should_be, std::string description)
{
  if (test_result != should_be)
  {
    std::ostringstream ss;
    ss << description << ": was (" << test_result << "), should be (" << should_be << ")";
    throw std::runtime_error(ss.str());
  }
  else
  {
    std::cout << "success: " << description << ", result: " << test_result << "\n";
  }
}


static void parse_argument(argument_map *map, char *arg)
{
  assert(map != NULL);
  assert(arg != NULL);

  char *key   = strtok(arg, "=");
  char *value = strtok(NULL, "");

  if (key && value)
    (*map)[key] = value;
}


static void parse_command_line(argument_map *map, int argc, char **argv)
{
  assert(map != NULL);
  assert(argv != NULL);

  for (int a = 1; a < argc; a++)
    parse_argument(map, argv[a]);
}


static std::unique_ptr<argument_map> create_argument_map_with_default_values(void)
{
  std::unique_ptr<argument_map> map(new argument_map());

  map->insert(argument_pair(ARGKEY_THREAD_COUNT, "1"));
  map->insert(argument_pair(ARGKEY_REPLICANT_COUNT, "1"));
  map->insert(argument_pair(ARGKEY_BLOCK_SIZE, "0"));

  return map;
}


int main(int argc, char **argv)
{
  std::unique_ptr<argument_map> map(create_argument_map_with_default_values());
  parse_command_line(map.get(), argc, argv);
  
  test_worker(map.get());
  test_with_stream(map.get());
}