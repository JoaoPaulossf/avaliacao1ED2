CC = gcc

CFLAGS = -O0 -std=c11 \
-Wall -Wextra -Werror \
-Wno-sign-compare \
-Wno-unused-parameter \
-Wno-unused-variable \
-Wshadow \
-fsanitize=address,undefined,leak

LDFLAGS = -lm -fsanitize=address,undefined,leak

SRC = main.c heap.c Huffman.c
OUT = compilador

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)