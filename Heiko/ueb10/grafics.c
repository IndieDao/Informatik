#include <stdio.h>
#include "ini.h"


void printHeader()
{
  printf("========================\n");
  printf("||   Zeichenzaehler   ||\n");
  printf("||                    ||\n");
  printf("========================\n");
  printf("\n");
  printf("Geben Sie bitte den Text ein (mind. 1Zeichen / max. %i Zeichen),\n", MAXZEICHEN);
  printf("dessen Zeichen gezäehlt werden sollen:\n");
}


void printResults(int *countOfAscii)
{
  int i=1,j=1,Z=1;

  printf("\n");
  printf("Anzahl der Zeichen:\n");
  printf("-----------------------------------------------------------------\n");
 
  for (i = 1; i <= 256; i++)
  {
    if (countOfAscii[i] != 0)
    {
      if (i < 32)
        Z = 32;
      else
        Z = i;
      switch (j)
      {
      case 1:  printf("| %c (%#04x): %3i |", Z, i, countOfAscii[i]);
	       j++;
	       break;
      case 4:  printf(" %c (%#04x): %3i |\n", Z, i, countOfAscii[i]);
	       j = 1;
	       break;
      default: printf(" %c (%#04x): %3i |", Z, i, countOfAscii[i]);
	       j++;
      }
    }
  }
  if (j != 1)
  {
    do
    {
      printf("               |");
      j++;
    } while (j <= 4);
    printf("\n");
  }
  printf("-----------------------------------------------------------------\n");

}
