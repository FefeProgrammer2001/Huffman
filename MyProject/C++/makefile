CC=clang++
CFLAGS=-Wall -Werror -Wextra -std=c++23 -O3 -g
SRC=*.cpp
BIN=Huffman

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clear:
	rm -rf Huffman

.PHONY: all clear