BINARIES = wikiAnalyzer caesarAnalyzer randomAnalyzer

STD = c++17
CC = g++
LFLAGS = -ldl -lzed

DIRS =  ../../src/ ../../src/ciphers/  ../../src/helpers/ ../../libs/ ../../src/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(BINARIES)

wikiAnalyzer: wikiAnalyzer.o
	$(CC) -o $@ $^ $(OBJS) $(LFLAGS)

caesarAnalyzer: caesarAnalyzer.o
	$(CC) -o $@ $^ $(OBJS) $(LFLAGS)

randomAnalyzer: randomAnalyzer.o
	$(CC) -o $@ $^ $(OBJS) $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARIES) *.o

.PHONY: clean all
