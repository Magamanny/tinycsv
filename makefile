build: examples/basic.c src/tinycsv.c
	gcc -o basic examples/basic.c src/tinycsv.c -I./include
	gcc -o demo_write examples/demo_write.c src/tinycsv.c -I./include
	./basic