INCLUDEPATH = ../cpp_libs/libzed
STATICLIB = ../cpp_libs/libzed/libzed.a
STD = c++17
CC = g++

make: crypto.exe
crypto.exe: crypto.o tools/dictionary.o ciphers/caesar.o $(STATICLIB)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -I$(INCLUDEPATH) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f *.exe *.o
	cd ciphers && rm -f *.exe *.o
	cd tools &&  rm -f *.exe *.o

remake: clean make

.PHONY: clean
