#include <stdio.h>
#include "escapesequenzen.h"
#include "tools.h"

//int i = 0 ;

int Strlen(char *str)
{
int len = 0;

while(*(str++) != '\0')
    {
        len++;
    }
    return len;
}

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
