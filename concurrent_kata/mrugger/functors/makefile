
CC=g++
CFLAGS=-c -O3 -DNODEBUG -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =


TEST_ITERATOR = test.iterator

TEST_ITERATOR_SOURCES =	$(TEST_ITERATOR).cpp						\
												$(TEST_ITERATOR).iterators.cpp	\
												$(TEST_ITERATOR).sequencer.cpp	\
												$(TEST_ITERATOR).thread.cpp			\
												$(SOURCE_FILES)

TEST_ITERATOR_OBJECTS = $(TEST_ITERATOR_SOURCES:.cpp=.o)


all:	$(TEST_ITERATOR)


clean:
	rm *.o
	rm $(TEST_ITERATOR)


$(TEST_ITERATOR):	$(TEST_ITERATOR_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_ITERATOR_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
