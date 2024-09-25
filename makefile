STD = c++17
CC = g++
LFLAGS = -ldl -lzed

# TODO: Install libzed on first make and include some sort of update command

BINARY = crypto

DIRS = ciphers/ ext/ libs/ parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(BINARY): crypto.o $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f $(BINARY) *.o
	cd ciphers && rm -f *.o
	cd ext &&  rm -f *.o
	cd libs &&  rm -f *.o
	cd parser &&  rm -f *.o
	
	cd tests && make clean

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) ! -path "./ext/*" ! -path "./tests/*" ! -name pugixml.cpp -exec wc -l {} +

libzed:
	cd ../../libs/libzed && make clean && git pull && make -j32 && sudo make install

tests: $(BINARY)
	$(MAKE) -C tests/
	./tests/bin/run_tests $(TAG)

.PHONY: clean count libzed
