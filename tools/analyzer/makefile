BIN = wikiAnalyzer

STD = c++17
CC = g++
LFLAGS = -ldl -lzed

DIRS = ../../ciphers/ ../../ext/ ../../src/ ../../parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(BIN): $(BIN).o $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARY) *.o

.PHONY: clean
