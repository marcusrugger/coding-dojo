#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

#include <string>


/* Test helpers */

void should_eq(bool test_result, bool should_be, std::string description);
void should_eq(int test_result, int should_be, std::string description);
void should_eq(char *test_result, char *should_be, std::string description);


/* Testers */

void test_reverse_string(void);
void test_worker(int thread_count, int replicant_count, int block_size);


#endif  // __TEST_MAIN_H__
