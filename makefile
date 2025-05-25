FLAGS=-O3 -Wall -Wextra -Werror
EXEC=Main
CC=clang++

ALL: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) -c $(EXEC).cpp
	$(CC) $(FLAGS) $(EXEC).o  -o $(EXEC).exe

clean:
	rm -rf $(EXEC) *.o
