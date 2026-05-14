all: main.c heap.c Huffman.c heap.h Huffman.h
	gcc main.c heap.c Huffman.c -o compilador
run: all
	./compilador
clean:
	rm -f compilador