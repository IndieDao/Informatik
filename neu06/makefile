CC = gcc -Wall
PRG = neu06
OBJ = neu06.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

$(OBJ): $(PRG).c
	$(CC) -c $<

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
