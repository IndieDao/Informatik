#include <stdio.h>
#include <stddef.h>
#include "tools.h"
#include "escapesequenzen.h"

void printFrame()
{
    // grafische Oberflaeche
    CLEAR;
    HOME;
    printf("|--------------------------------------------------------------|\n");
    FORECOLOR_RED;
    BACKCOLOR_WHITE;
    INVERSE;
    printf("  Bitoperatoren-Rechner      |&<>~^                             \n");
    ATTRIBUTE_OFF;
    printf("|                                                              |\n");
    printf("| Eingabe Zahl 1:                                              |\n");
    printf("| Operator:                                                    |\n");
    printf("| Eingabe Zahl 2:                                              |\n");
    printf("|                                                              |\n");
    printf("|--------------------------------------------------------------|\n");
    printf("|                                                              |\n");
    printf("|           |  dez.   | okt.    |  hex.    | Binaerdarstellung |\n");
    printf("| Zahl 1    |         |         |          |                   |\n");
    printf("| Operator  |         |         |          |                   |\n");
    printf("| Zahl 2    |         |         |          |                   |\n");
    printf("| ------------------------------------------------------------ |\n");
    printf("| Ergebnis  |         |         |          |                   |\n");
    printf("|                                                              |\n");
    printf("|--------------------------------------------------------------|\n");
}

// Tastaturpuffer loeschen
void clearBuffer()
{
    char Dummy;
    do
    {
        scanf("%c", &Dummy);
    } while (Dummy != '\n');
}

// Zahl einlesen
short getNumber(int Zeile)
{
    short Zahl;
    int GueltigeEingabe;
    POSITION(Zeile, 18); //Eingabeposition
    do
    {
        GueltigeEingabe = scanf("%hi", &Zahl);
        clearBuffer();
        if (!GueltigeEingabe)
        {
            POSITION(Zeile, 25);
            printf("erneute Eingabe!                       |");
            POSITION(Zeile, 18);
        }
    } while (!GueltigeEingabe);
    printInputNumber(Zeile, Zahl);

    return Zahl;
}

// Buendige Ausgabe eingegebener Zahlen
void printInputNumber(int Zeile, short Zahl)
{
    POSITION(Zeile, 18);
    printf("%7i                                       |", Zahl);
}

// Bitoperator einlesen
char getOperator()
{
    int GueltigeEingabe;
    char Op;
    POSITION(5, 20); //Eingabezeile loeschen
    printf("                                            | ");
    POSITION(5, 20); //Eingabeposition
    do
    {
        GueltigeEingabe = scanf("%[|<>&~^]", &Op);
        clearBuffer();
        if (!GueltigeEingabe)
        {
            POSITION(5, 25);
            printf("erneute Eingabe!                       |");
            POSITION(5, 20);
        }
    } while (!GueltigeEingabe);
    printInputOperator(Op);

    return Op;
}

// Ausgabe Bitshift Operator bei Eingabe
void printInputOperator(char Op)
{
    POSITION(5, 20);
    if (Op == '<' || Op == '>')
        printf("%c%c                                     ", Op, Op);
    else
        printf("%c                                      ", Op);
}

// Berechnungen
short calcResult(short Z1, short Z2, char Op)
{
    switch (Op)
    {
    case '&':
        return (Z1 & Z2);
    case '|':
        return (Z1 | Z2);
    case '<':
        return (Z1 << Z2);
    case '>':
        return (Z1 >> Z2);
    case '^':
        return (Z1 ^ Z2);
    case '~':
        return (~Z1);
    }

    return 0;
}

//Ausgabe Ergebnisse in Dezimal, Oktal und Hexadezimal
void printResultNumber(int Zeile, short Zahl)
{
    POSITION(Zeile, 13);
    printf("%9i %#9ho %#9hX                 |", Zahl, Zahl, Zahl);
    printBinary(Zeile, Zahl);
    printf("\n");
}

//Ausgabe Ergebnisse in Binaerzahlen
void printBinary(int Zeile, short Zahl)
{
    int i;
    POSITION(Zeile, 47);
    for (i = 15 ; i >= 0; i--)
    {
        printf("%i", (Zahl >> i) &1);
    }
}

//grafische Ausgabe Bitoperatoren in Ergebnis
void printResultOperator(char Op)
{
if (Op == '<' || Op == '>')
printf("| Operator  |    %c%c   |     %c%c   |    %c%c   |         %c%c   \n", Op, Op, Op, Op, Op, Op, Op, Op);
else
printf("| Operator  |    %c    |    %c    |    %c     |          %c        \n",
         Op, Op, Op, Op);
}

int askAgain()
{
    char W = 'j';
    do
    {
        POSITION(18, 0);
        printf("Moechten Sie noch einmal (j/n) "); // Eingabeaufforderung
        scanf("%c", &W);
        if (W != '\n')
            clearBuffer();
        if (W != 'j' && W != 'J' && W != 'n' && W != 'N')
            printf("\n j | n reicht!");
        else if (W == 'j' || W == 'J')
        {
            return 1;
        }
    } while (W != 'j' && W != 'J' && W != 'n' && W != 'N');
    return 0;
}
