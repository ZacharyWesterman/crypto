INCLUDEPATH = ../cpp_libs/libzed
STATICLIB = ../cpp_libs/libzed/libzed.a
STD = c++17
CC = g++

make: crypto.exe
crypto.exe: crypto.o tools/dictionary.o tools/helper.o ciphers/caesar.o $(STATICLIB)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -I$(INCLUDEPATH) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f *.exe *.o
	cd ciphers && rm -f *.exe *.o
	cd tools &&  rm -f *.exe *.o

remake: clean make

count:
	find . -type f \( -name \*.cpp -o -name \*.h \) ! -path "./libs/*" ! -name pugixml.cpp -exec wc -l {} +

libzed:
	cd ../cpp_libs/libzed && git pull && make -j32 static

.PHONY: clean count libzed
