build: examples/basic_read.c src/tinycsv.c
	gcc -o basic_read.exe examples/basic_read.c src/tinycsv.c -I./include
	gcc -o basic_write.exe examples/basic_write.c src/tinycsv.c -I./include
	./basic_read.exe
	./basic_write.exe