CC = gcc -Wall
PRG = neu08
OBJ = neu08.o tools.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

neu08.o: neu08.c
	$(CC) -c $<

tools.o: tools.c tools.h
	$(CC) -c tools.c tools.h

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
