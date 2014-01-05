
CC=g++
CFLAGS=-c -O3 -std=c++11
LDFLAGS=-lncurses

SOURCE_FILES =	kata.reverse-string.cpp						\
								kata.worker.cpp										\
								kata.char-decrement-iterator.cpp	\
								kata.kata-iterator.cpp						\
								kata.block-iterator.cpp


TEST_MAIN = test.main

TEST_MAIN_SOURCES =	$(TEST_MAIN).cpp					\
										$(SOURCE_FILES)						\
										test.worker.cpp

TEST_MAIN_OBJECTS = $(TEST_MAIN_SOURCES:.cpp=.o)


all:	$(TEST_MAIN)


clean:
	rm *.o
	rm $(TEST_MAIN)


$(TEST_MAIN):	$(TEST_MAIN_OBJECTS)
	$(CC) $(TEST_MAIN_OBJECTS) $(LDFLAGS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
