#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"

void clearBuffer()
{
   char Dummy;
   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}

int askAgain(int Row, int Col)
{
   char W = 'j';
  do
   {
      POSITION(Row, Col);
      printf("Moechten Sie noch einmal (j/n) "); // Eingabeaufforderung
      clearBuffer();
      scanf("%c", &W);
      if (W != 'j' && W != 'J' && W != 'n' && W != 'N')
         printf("\n j | n reicht!");
      else if (W == 'j' || W == 'J')
      {
         return 1;
      }
   }while (W != 'j' && W != 'J' && W != 'n' && W != 'N');
   return 0;
}
