CC = gcc -Wall
PRG = neu11
OBJ = neu11.o tools.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

neu11.o: neu11.c
	$(CC) -c $< #-fno-stack-protector

tools.o: tools.h
	$(CC) -c tools.c #-fno-stack-protector

all: clean $(PRG) run

clean:
	rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
