#personal information
MATRIKEL=835333
NAME=Heiko radde
AUFGABE=Uebung4
CC = gcc -Wall
PRG = ueb04

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