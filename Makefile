gcc-test:
	gcc -O3 list.c heap.c main.c -o heap_test -I /usr/include/c++/8
	./heap_test

clean:
	rm heap_test