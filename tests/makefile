CC = g++
LN = g++
CFLAGS = --std=c++17 -fprofile-arcs -ftest-coverage
LFLAGS = -lgcov -ldl -lzed

SRCS = $(wildcard $(addsuffix *.cpp, src/))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

PARENT_DIRS =  ../src/ ../src/ciphers/ ../ext/
PARENT_SRCS = $(wildcard $(addsuffix *.cpp, $(PARENT_DIRS)))
PARENT_OBJS = $(patsubst %.cpp,%.o,$(PARENT_SRCS))

bin/run_tests: $(OBJS) $(PARENT_OBJS)
	$(LN) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f bin/* src/*.o src/*.gcda src/*.gcno *.gcov

.PHONY: all clean
