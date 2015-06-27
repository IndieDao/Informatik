CC = gcc -Wall
PRG = ueb08
OBJ = ueb08.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ -lm

ueb08.o: ueb08.c
	$(CC) -c $<

tools.o: tools.c tools.h
   gcc-c tools.c

all: clean $(PRG) run
	

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
