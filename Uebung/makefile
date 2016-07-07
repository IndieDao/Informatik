CC = gcc -Wall
PRG = prog1
OBJ = prog1.o 

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

prog1.o: prog1.c
	$(CC) -c $< #-fno-stack-protector

#tools.o: tools.h
#	$(CC) -c tools.c #-fno-stack-protector

all: clean $(PRG) run

clean:
	rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
