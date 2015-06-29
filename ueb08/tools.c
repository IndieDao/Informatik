#include <stdio.h>
#include <stddef.h>
#include "tools.h"
#include "escapesequenzen.h"

void printFrame()
{
   CLEAR;
   HOME;
   printf("|--------------------------------------------------------------|\n");
   printf("| Bitoperatoren-Rechner                                        |\n");
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
      if (!GueltigeEingabe)
      {
         POSITION(Zeile, 17);
         printf("           erneute Eingabe!                    |");
         POSITION(Zeile, 17);
      }
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

char getOperator()
{
   int GueltigeEingabe;
   char Op;
   POSITION(5, 17); //Eingabezeile loeschen
   printf("                                               ");
   POSITION(5, 17); //Eingabeposition
   do
   {
      GueltigeEingabe = scanf("%[|<>&~^]", &Op);
      clearBuffer();
      if (!GueltigeEingabe)
      {
         POSITION(5, 17);
         printf("           erneute Eingabe!                    |");
         POSITION(5, 17);
      }
   } while (!GueltigeEingabe);
   printInputOperator(Op);
   return Op;
}

void printInputOperator(char Op)
{
   POSITION(5, 17);
   if (Op == '<' || Op == '>')
      printf("%c%c                                     ", Op, Op);
   else
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
   return 0;
}

void printResultNumber(int Zeile, short Zahl)
{
   POSITION(Zeile, 13);
   printf("%9i %#9o %#9X                 |", Zahl, Zahl, Zahl);
   printBinary(Zeile, Zahl);
   printf("\n");
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
      LEFT(2);
   }
}

void printResultOperator(char Op)
{
   printf(
         "| Operator  |    %c    |    %c    |    %c     |        %c          \n",
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

