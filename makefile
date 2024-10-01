STD = c++17
CC = g++
LFLAGS = -ldl -lzed

# TODO: Install libzed on first make and include some sort of update command

BINARY = crypto

DIRS = ciphers/ ext/ src/ parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(BINARY): crypto.o $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARY) *.o

	cd ciphers && rm -f *.o
	cd src &&  rm -f *.o

	make clean -C tests
	make clean -C tools

count:
	@echo "Analyzing files not in ./ext or ./tests/bin"
	@echo "Total File Count"
	@find . -type f -not -path "*/.git/*" | wc -l
	@echo "Lines of Code (cpp, h, py)"
	@find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.py" \) ! -path "./ext/*" ! -path "./tests/bin" ! -name pugixml.cpp -exec wc -l {} +

ext/libzed/libzed.a: ext/libzed
	make static dynamic -C ext/libzed -j32

ext/libzed:
	git clone https://github.com/ZacharyWesterman/libzed.git ext/libzed

fetch: ext/libzed
	cd $< && git pull

install: ext/libzed/libzed.a
	make install -C ext/libzed

tests: $(BINARY)
	$(MAKE) -C tests/
	./tests/bin/run_tests $(FILTER)

tools: $(BINARY)
	$(MAKE) -C tools

.PHONY: clean count libzed tests tools fetch install
