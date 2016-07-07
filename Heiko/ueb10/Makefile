#personal information
MATRIKEL=835333
NAME=Heiko Radde
AUFGABE=Uebung10
CC = gcc -Wall
PRG = ueb10


$(PRG): main.o grafics.o tools.o escapesequenzen.h
	$(CC) -o $(PRG) main.o grafics.o tools.o -lm #-fno-stack-protector
	@echo $(AUFGABE) von $(NAME), $(MATRIKEL)

main.o: main.c 
	$(CC) -c main.c #-fno-stack-protector

grafics.o: grafics.c grafics.h
	$(CC) -c grafics.c #-fno-stack-protector

tools.o: tools.c tools.h
	$(CC) -c tools.c #-fno-stack-protector

all: clean $(PRG) run

clean:
	rm main.o grafics.o tools.o $(PRG) -f

run:
	./$(PRG)


#-fno-stack-protector um pufferoverflow detection & protection zu deaktivieren
