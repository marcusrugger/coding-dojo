#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

#include <string>


/* Test helpers */

void should_eq(int test_result, int should_be, std::string description);


/* Testers */

void test_worker(void);


#endif  // __TEST_MAIN_H__
