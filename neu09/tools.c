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
char W;
while(!scanf("%[jJnN]", &W))
{
      POSITION(Row, Col);
      CLEAR_LINE;
      printf("Moechten Sie noch einmal (j/n) "); // Eingabeaufforderung
      clearBuffer();
}
    if (W == 'j' || W == 'J')
    {
        return 1;
    }
    return 0;
}
