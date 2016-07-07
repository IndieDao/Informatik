#personal information
MATRIKEL=835333
NAME=Heiko Radde
AUFGABE=Uebung5
CC = gcc -Wall
PRG = ueb05

ueb01: main.o
	$(CC) -o $(PRG) main.o -lm
	@echo $(AUFGABE) von $(NAME), $(MATRIKEL)

main.o: main.c
	$(CC) -c main.c

all: clean $(PRG) run

clean:
	rm main.o $(PRG) -f

run:
	./$(PRG)