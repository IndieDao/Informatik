CC = gcc -Wall
Prg = neu00
Obj = neu00.o

$(Prg): $(Obj)
	$(CC) -o $@ $^

neu00.o: neu00.c
	$(CC) -c $<

run:
	./$(Prg)

all: clean $(Prg) run

clean:
	rm $(Prg) $(Obj) -f

