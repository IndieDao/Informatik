CC = gcc -Wall
PRG = neu04
OBJ = neu04.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

neu04.o: neu04.c
	$(CC) -c $<

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
