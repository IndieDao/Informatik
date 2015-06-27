CC = gcc -Wall
PRG = ueb01
OBJ = ueb01.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ 

ueb01.o: ueb01.c
	$(CC) -c $<

all: clean $(PRG) run
	

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
