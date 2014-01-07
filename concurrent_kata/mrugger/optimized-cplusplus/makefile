
CC=g++
CFLAGS=-c -O3 -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses


TEST_MAIN = test.main

TEST_MAIN_SOURCES =	$(TEST_MAIN).cpp					\
										test.worker.cpp

TEST_MAIN_OBJECTS = $(TEST_MAIN_SOURCES:.cpp=.o)


all:	$(TEST_MAIN)


clean:
	rm *.o
	rm $(TEST_MAIN)


$(TEST_MAIN):	$(TEST_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
