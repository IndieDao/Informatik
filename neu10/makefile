CC = gcc -Wall
PRG = neu10
OBJ = neu10.o tools.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

neu10.o: neu10.c
	$(CC) -c $< #-fno-stack-protector

tools.o: tools.h
	$(CC) -c tools.c #-fno-stack-protector

all: clean $(PRG) run

clean:
	rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
