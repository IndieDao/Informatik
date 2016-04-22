CC = gcc -Wall
PRG = neu03
OBJ = neu03.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^

neu03.o: neu03.c
	$(CC) -c $<

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
