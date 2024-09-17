INCLUDEPATH = ../cpp_libs/libzed
STATICLIB = ../cpp_libs/libzed/libzed.a
STD = c++17
CC = g++

BINARY = crypto.exe

DIRS = ciphers/ ext/ libs/ parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(BINARY): crypto.o $(OBJS) $(STATICLIB)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -I$(INCLUDEPATH) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f *.exe *.o
	cd ciphers && rm -f *.exe *.o
	cd ext &&  rm -f *.exe *.o
	cd libs &&  rm -f *.exe *.o
	cd parser &&  rm -f *.exe *.o

remake: clean make

count:
	find . -type f \( -name \*.cpp -o -name \*.h \) ! -path "./libs/*" ! -name pugixml.cpp -exec wc -l {} +

libzed:
	cd ../cpp_libs/libzed && git pull && make -j32 static

tests: $(BINARY)
	$(MAKE) -C tests/
	./tests/bin/run_tests.exe

.PHONY: clean count remake libzed
