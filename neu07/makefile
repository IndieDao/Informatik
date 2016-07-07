CC = gcc -Wall
PRG = neu07
OBJ = neu07.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

$(OBJ): $(PRG).c
	$(CC) -c $<

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
