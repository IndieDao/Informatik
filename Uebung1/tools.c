#include <stdio.h>
#include "escapesequenzen.h"
#include "tools.h"
#include <string.h>

//int i = 0 ;

//Programm wiederholen
int askAgain(char *Frage)
{
char W;
printf("%s", Frage);
while (!scanf("%[jJnN]", &W))
    {
        UP_LINE;
        CLEAR_LINE;
        clearBuffer();
    }
    if (W == 'j' || W =='J')
    {
        clearBuffer();
        return 1;
    }
return 0;
}

//Zeichenpuffer loeschen
void clearBuffer()
{
   char Dummy;
   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}


void clearScreen()
{
CLEAR;
POSITION(1, 1);
}
