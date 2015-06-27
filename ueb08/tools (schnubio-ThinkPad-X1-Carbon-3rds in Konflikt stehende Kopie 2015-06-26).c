#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"

//double Zahl1, Zahl2, Dez, Okt, Hex, Bin;
int GueltigeEingabe;
char Operator, Op, Dummy;

void clearBuffer() {
	do {
		scanf("%c", &Dummy);
	} while (Dummy != '\n');
}

void printFrame() {
	CLEAR;
	HOME;
	printf("|--------------------------------------------------------------|");
	printf("| Bitoperatoren-Rechner                                        |");
	printf("|                                                              |");
	printf("| Eingabe Zahl 1:                                              |");
	printf("| Operator:                                                    |");
	printf("| Eingabe Zahl 2:                                              |");
	printf("|                                                              |");
	printf("|--------------------------------------------------------------|");
	printf("|                                                              |");
	printf("|           |  dez.   | okt.    |  hex.    | Binaerdarstellung |");
	printf("| Zahl 1    |         |         |          |                   |");
	printf("| Operator  |         |         |          |                   |");
	printf("| Zahl 2    |         |         |          |                   |");
	printf("| ------------------------------------------------------------ |");
	printf("| Ergebnis  |         |         |          |                   |");
	printf("|                                                              |");
	printf("|--------------------------------------------------------------|");
}

short getNumber(int Zeile) {
	short Zahl1;
	POSITION(Zeile, 18); //Eingabezeile loeschen
	//printf("                                              ");
	//POSITION(Zeile, 18); //Eingabeposition
	do {
		// Rückgabe : gezählter eingeleser Wert
		GueltigeEingabe = scanf("%hi", &Zahl1);
		clearB
	} while (!GueltigeEingabe);
	return Zahl1;
}

void printInputNumber(int Zeile, short Zahl) {
	POSITION(Zeile, 0);
	CLEAR_LINE;
	if (Zeile == 4) {
		printf("| Eingabe Zahl 1:                                            |",
				Zahl);
	} else {
		printf("| Eingabe Zahl 2:                                            |",
				Zahl);
	}
	POSITION(Zeile, 18);
	printf("%d", &Zahl);
	//return 0;
}

char getOperator() {
	POSITION(5, 18); //Eingabezeile l�schen
	printf("                                              ");
	POSITION(5, 18); //Eingabeposition
	do {
		GueltigeEingabe = scanf("%c", &Op);
		do {
			scanf("%c", &Dummy);
		} while (Dummy != '\n');
	} while (!GueltigeEingabe);
	printInputOperator(Op);
	return Op;
}

void printInputOperator(char Operator) {
	POSITION(5, 0);
	CLEAR_LINE;
	printf("| Operator:                                                 |");
	POSITION(5, 18);
	printf("%c", &Operator);
}

short calcResult(short Z1, short Z2, char Op) {

}

void printResultNumber(int Zeile, short Zahl) {

}

void printBinary(int Zeile, short Zahl)

void printResultOperator(char Operator)

int askAgain()

void clearBuffer()

