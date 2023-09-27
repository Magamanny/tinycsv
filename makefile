build: examples/basic.c src/tinycsv.c
	gcc -o basic.exe examples/basic.c src/tinycsv.c -I./include
	gcc -o demo_write.exe examples/demo_write.c src/tinycsv.c -I./include
	./basic.exe
	./demo_write.exe