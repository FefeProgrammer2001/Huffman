FLAGS=-O3 -Wall -Wextra -Werror
EXEC=Main
CC=clang++

ALL: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o  -o $(EXEC).exe

clean:
	rm -rf $(EXEC) *.o
