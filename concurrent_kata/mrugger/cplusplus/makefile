
CC=g++
CFLAGS=-c -O2 -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =	kata.worker.cpp										\
								kata.char-decrement-iterator.cpp	\
								kata.sequence-iterator.cpp				\
								kata.stream-iterator.cpp


TEST_MAIN = test.main

TEST_MAIN_SOURCES =	$(TEST_MAIN).cpp					\
										$(SOURCE_FILES)						\
										test.worker.cpp						\
										test.with-stream.cpp			\
										test.block-iterator.cpp		\
										test.stream.cpp

TEST_MAIN_OBJECTS = $(TEST_MAIN_SOURCES:.cpp=.o)


all:	$(TEST_MAIN)


clean:
	rm *.o
	rm $(TEST_MAIN)


$(TEST_MAIN):	$(TEST_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
