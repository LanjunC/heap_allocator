gcc-test:
	gcc -O3 list.c heap.c main.c -o heap_test
	./heap_test

clean:
	rm heap_test