#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"

double Zahl1, Zahl2, Dez, Okt, Hex, Bin;
int GueltigeEingabe;
char Operator, Op, Dummy;
short Z;

void printFrame()
{
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


short getNumber(int Zeile)
{
   POSITION(Zeile, 18); //Eingabezeile löschen
   printf("                                              ");
   POSITION(Zeile, 18); //Eingabeposition
   do
   {
      GueltigeEingabe = scanf("%lf", &Zahl1);
      do
      {
         scanf("%c", &Dummy);
      } while (Dummy != '\n');
   }while (!GueltigeEingabe);
   return Z1;
}

void printInputNumber(int Zeile, short Zahl)
{
   POSITION(Zeile, 0);
   CLEAR_LINE;
   if (Zeile == 4)
   {
   printf("| Eingabe Zahl 1:                                            |");
   }
   else
   {
   printf("| Eingabe Zahl 2:                                            |");
   }
   POSITION(Zeile, 18);
   printf("%d", Zahl);
   //return 0;
}

char getOperator()
{
   POSITION(5, 18); //Eingabezeile löschen
   printf("                                              ");
   POSITION(5, 18); //Eingabeposition
   do
   {
      GueltigeEingabe = scanf("%c", &Op);
      do
      {
         scanf("%c", &Dummy);
      } while (Dummy != '\n');
   }while (!GueltigeEingabe);
   printInputOperator(Op);
   return Op;
}

void printInputOperator(char Operator)
{
   POSITION(5, 0);
   CLEAR_LINE;
   printf("| Operator:                                                 |");
   POSITION(5, 18);
   printf("%c", Operator);
}

short calcResult(short Z1, short Z2, char Op)
{
    switch(op)
    {
        case '&': Z = Z1&Z2;
        break;
        case '|': Z = Z1|Z2;
        break;
        case '^': Z = Z1^Z2;
        break;
        case '<<': Z = Z1<<Z2;
        break;
        case '>>': Z = Z1>>Z2;
        break;
    }
return Z
}

void printResultNumber(int Zeile, short Zahl)
{
   POSITION(12, 12);
   printf("Zahlen rechtsbündig ausgeben: %5d, %o, %x\n",Z1, Z1, Z1);
   POSITION(12, 12);
}

void printBinary(int Zeile, short Zahl);

void printResultOperator(char Operator);

int askAgain();

void clearBuffer();

short bin_output(int val)
{
    int i;
    char str[33];
    for (i = 31; i >= 0; i--)
	str[31-i] = '0' + ((val >> i) & 0x1);
    str[32] = 0;
    puts(str);
    return;
}
