BINARIES = wikiAnalyzer fishAnalyzer

STD = c++17
CC = g++
LFLAGS = -ldl -lzed

DIRS = ../../ciphers/ ../../ext/ ../../src/ ../../parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(BINARIES)

%: %.o $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARIES) *.o

.PHONY: clean all
