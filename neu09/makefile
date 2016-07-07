CC = gcc -Wall
PRG = neu09
OBJ = neu09.o tools.o matrix.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

neu09.o: neu09.c
	$(CC) -c $<

tools.o: tools.h
	$(CC) -c tools.c

matrix.o: tools.h matrix.h
	$(CC) -c matrix.c

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
