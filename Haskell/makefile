CC = ghc
CFLAGS =-O3 -Wall -Wextra -Werror
ASSEMBLY =-S
TARGETASSEMBLY = Huffman.s
TARGET = Huffman.exe
SRC = Huffman.hs

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(ASSEMBLY) $(SRC) -o $(TARGETASSEMBLY)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)
