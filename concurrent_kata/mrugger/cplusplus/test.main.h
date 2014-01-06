#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

#include <string>
#include <map>


typedef std::pair<std::string, std::string> argument_pair;
typedef std::map<std::string, std::string> argument_map;

const std::string ARGKEY_THREAD_COUNT("thread_count");
const std::string ARGKEY_REPLICANT_COUNT("replicant_count");
const std::string ARGKEY_BLOCK_SIZE("block_size");


/* Test helpers */

void should_eq(bool test_result, bool should_be, std::string description);
void should_eq(int test_result, int should_be, std::string description);


/* Testers */

void test_worker(argument_map *map);
void test_concurrency(argument_map *map);
void test_with_stream(argument_map *map);


#endif  // __TEST_MAIN_H__
