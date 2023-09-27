.PHONY: all test clean
all: basic_read.exe basic_write.exe
	./basic_read.exe
	./basic_write.exe
basic_read.exe: basic_read.o tinycsv.o
	gcc -o basic_read.exe basic_read.o tinycsv.o -I./include
	
basic_write.exe: basic_write.o tinycsv.o
	gcc -o basic_write.exe basic_write.o tinycsv.o -I./include
	./basic_write.exe

basic_read.o: examples/basic_read.c
	gcc -c examples/basic_read.c -I./include

basic_write.o: examples/basic_write.c
	gcc -c examples/basic_write.c -I./include

tinycsv.o: src/tinycsv.c
	gcc -c src/tinycsv.c -I./include

test:
	ceedling test:all

clean:
	rm -f *.exe *.o