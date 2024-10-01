BINARIES = wikiAnalyzer caesarAnalyzer

STD = c++17
CC = g++
LFLAGS = -ldl -lzed

DIRS = ../../ciphers/ ../../ext/ ../../src/ ../../parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(BINARIES)

wikiAnalyzer: wikiAnalyzer.o
	$(CC) -o $@ $^ $(OBJS) $(LFLAGS)

caesarAnalyzer: caesarAnalyzer.o
	$(CC) -o $@ $^ $(OBJS) $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARIES) *.o

.PHONY: clean all
