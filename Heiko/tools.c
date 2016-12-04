#include <stdio.h>
#include "escapesequenzen.h"
#include "tools.h"

    char *pTag;
    char *pMonth;
    char *pJahr;

    char *pStd;
    char *pMin;
    char *pSec;

void printLine(char Zeichen, int Anzahl)
{
int j = 0;
for ( j = 0; j<Anzahl; j++ )
    {
        printf("%c", Zeichen);
    }
    printf("\n");
}

void waitForEnter()
{
    char Dummy;

    printf("\nBitte druecken Sie die Eingabetaste ...\n");

    do
        scanf("%c", &Dummy);
    while(Dummy !='\n');
}

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
