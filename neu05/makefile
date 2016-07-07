CC = gcc -Wall
PRG = neu05
OBJ = neu05.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

$(OBJ): $(PRG).c
	$(CC) -c $<

all: clean $(PRG) run

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
