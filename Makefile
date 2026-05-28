CC = gcc

CFLAGS = -O0 -g -std=c11 \
-Wall -Wextra -Werror \
-Wno-sign-compare \
-Wno-unused-parameter \
-Wno-unused-variable \
-Wshadow

LDFLAGS = -lm

SRC = main.c heap.c Huffman.c
OUT = compilador

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT)

clean:
	rm -f $(OUT)