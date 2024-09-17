INCLUDEPATH = ../../cpp_libs/libzed
STATICLIB = ../../cpp_libs/libzed/libzed.a

CC = g++
LN = g++
CFLAGS = --std=c++17 -fprofile-arcs -ftest-coverage
LFLAGS = -lgcov

SRCS = $(wildcard $(addsuffix *.cpp, src/))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

bin/run_tests.exe: $(OBJS) $(STATICLIB)
	$(LN) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -I $(INCLUDEPATH) -o $@ -c $< $(CFLAGS)

clean:
	rm -f bin/* src/*.o src/*.gcda src/*.gcno *.gcov

.PHONY: all clean
