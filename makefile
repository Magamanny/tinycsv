build: examples/basic.c src/tinycsv.c
	gcc -o basic examples/basic.c src/tinycsv.c -I./include
	./basic