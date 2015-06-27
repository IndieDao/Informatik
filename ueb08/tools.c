#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"

/*Kommentar für Sophie*/
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

void clearBuffer()
{
   char Dummy;
   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}

short getNumber(int Zeile)
{
   short Zahl;
   int GueltigeEingabe;
   POSITION(Zeile, 18); //Eingabeposition
   do
   {
      GueltigeEingabe = scanf("%hi", &Zahl);
      clearBuffer();
   } while (!GueltigeEingabe);
//	POSITION(Zeile, 18); //Eingabeposition
//	printf("%7i                                       |", );
   printInputNumber(Zeile, Zahl);
   return Zahl;
}

void printInputNumber(int Zeile, short Zahl)
{
   POSITION(Zeile, 18);
   printf("%7i                                       |", Zahl);
}

char getOperator(int Zeile)
{
   POSITION(5, 18); //Eingabezeile l�schen
   printf("                                              ");
   POSITION(5, 18); //Eingabeposition
   do
   {
      GueltigeEingabe = scanf("%1c[|^<>&~]", &Op);
      clearBuffer();
   } while (!GueltigeEingabe);
   printInputOperator (Op);
   return Op;
}

void printInputOperator(int Zeile, char Op)
{
   POSITION(Zeile, 18);
   if (Op == '<')
   {
      Op = '<<';
   }
   else if (Op == '>')
   {
      Op = '>>';
   }
   printf("%c                                      ", Op);
}

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
}

void printResultNumber(int Zeile, short Zahl)
{

   printBinary();
}

void printBinary(int Zeile, short Zahl)
{
   int i;
   int Rest;
   POSITION(Zeile, 62);
   for (i = 0; i < 16; i++)
   {
      Rest = Zahl % 2;
      Zahl = Zahl / 2;
      printf("%i", Rest);
      RIGHT(2);
   }
}

void printResultOperator(char Operator)
{
   printf(
         "| Operator  |    %c    |    %c    |      %c    |         %c         |",
         Op, Op, Op, Op);
}

int askAgain()
{

}
