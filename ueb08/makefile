CC = gcc -Wall
PRG = ueb08
OBJ = ueb08.o tools.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

ueb08.o: ueb08.c
	$(CC) -c $<

tools.o: tools.c tools.h
	$(CC) -c tools.c tools.h

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
