CC = gcc -Wall
PRG = ueb03
OBJ = ueb03.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^ 

ueb03.o: ueb03.c
	$(CC) -c $<

all: clean $(PRG) run
	

clean:
	-rm $(PRG) $(OBJ) -f

run:
	./$(PRG)
