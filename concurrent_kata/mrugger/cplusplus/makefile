
CC=g++
CFLAGS=-c -O3 -std=c++11
LDFLAGS=-lncurses

SOURCE_FILES =	kata.worker.cpp


TEST_WORKER = test.worker

TEST_WORKER_SOURCES =	$(TEST_WORKER).cpp	\
											$(SOURCE_FILES)

TEST_WORKER_OBJECTS = $(TEST_WORKER_SOURCES:.cpp=.o)


all:	$(TEST_WORKER)


clean:
	rm *.o
	rm $(TEST_WORKER)


$(TEST_WORKER):	$(TEST_WORKER_OBJECTS)
	$(CC) $(TEST_WORKER_OBJECTS) $(LDFLAGS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
