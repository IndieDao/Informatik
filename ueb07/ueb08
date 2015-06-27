CC = gcc -Wall
PRG = ueb07
OBJ = ueb07.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

ueb07.o: ueb07.c
	$(CC) -c $<

all: clean $(PRG) run
	

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
