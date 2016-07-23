#include <stdio.h>
#include "escapesequenzen.h"
#include "tools.h"

int i = 0 ;

//Zeichenpuffer loeschen
void clearBuffer()
{
   char Dummy;
   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}


//Programm wiederholen
int askAgain(int Row, int Col)
{
char W;
while (!scanf("%[jJnN]", &W))
    {
        POSITION(Row, Col);
        CLEAR_LINE;
        printf("Moechten Sie noch einmal (j/n) ");
        clearBuffer();
    }
    if (W == 'j' || W =='J')
    {
        return 1;
    }
return 0;
}
