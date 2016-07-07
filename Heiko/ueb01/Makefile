#personal information
MATRIKEL=835333
NAME=Heiko Radde
AUFGABE=Uebung1
CC = gcc -Wall
PRG = ueb01

$(PRG): main.o
	$(CC) -o $(PRG) main.o
	@echo $(AUFGABE) von $(NAME), $(MATRIKEL)

main.o: main.c
	$(CC) -c main.c

all: clean $(PRG) run

clean:
	rm main.o $(PRG) -f

run:
	./$(PRG)
