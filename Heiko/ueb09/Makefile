#personal information
MATRIKEL=835333
NAME=Heiko Radde
AUFGABE=Uebung9
CC = gcc -Wall
PRG = ueb09

ueb09: ueb09.o matrix.o tools.o escapesequenzen.h
	$(CC) -o $(PRG) ueb09.o matrix.o tools.o -lm
	@echo $(AUFGABE) von $(NAME), $(MATRIKEL)

ueb09.o: ueb09.c 
	$(CC) -c ueb09.c

matrix.o: matrix.h tools.h
	$(CC) -c matrix.c

tools.o: tools.h
	$(CC) -c tools.c

all: clean $(PRG) run

clean:
	rm ueb09.o $(PRG) matrix.o tools.o -f

run:
	./$(PRG)
