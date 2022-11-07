gcc-test-clean:
	gcc -O3 list.c heap.c main.c -o heap_test
	./heap_test
	rm heap_test
gdb-test-clean:
	gcc -g list.c heap.c main.c -o heap_test
	gdb ./heap_test
	rm heap_test
clean:
	rm heap_test