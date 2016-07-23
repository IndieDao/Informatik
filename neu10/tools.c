#include <stdio.h>
#include "escapesequenzen.h"
#include "limit.h"
#include "tools.h"

int i = 0 ;

//Eingabemaske
void printInputMask()
{
    CLEAR;
    HOME;
    BLINK;
    printf("=====================\n");
    printf("||                 ||\n");
    printf("||  ");
    ATTRIBUTE_OFF;
    printf("Zeichenzaehler");
    BLINK;
    printf(" ||\n");
    printf("||                 ||\n");
    printf("=====================\n\n");
    ATTRIBUTE_OFF;
    printf("Geben Sie bitte den Text ein (mind. 1 Zeichen / max. 150 Zeichen),\ndessen Zeichen gezaehlt werden sollen:\n\n");
}

int Strlen(char *str)
{
    int len = 0;

    while (*str++ != '\0')
        {
            len++;
        }
    return len;
}

//Text einlesen
void getText(unsigned char *text)
{
    *text = 0;
    do
    {
        POSITION(10, 1);
        scanf("%150[^\n]", text);
        clearBuffer();
    }while (Strlen(text) == 0);
}

//Zeichen zaehlen
int countInAscii(unsigned char *text, unsigned int *anzahl)
{
    int Stringlaenge = Strlen(text);
    
    for( i=0 ; i < ASCIIMAX ; i++)
    {
        *(anzahl + i) = 0;
    }

    i = 0;
    while (*(text + i) )
    {
        if ( ((*(text + i) >= 'A') && (*(text + i) <= 'Z')) || *(text + i) == 'Ä' || *(text + i) == 'Ö' || *(text + i) == 'Ü' )
        {
            *(anzahl+(*(text + i)) + 32) += 1;
        }else{
            *(anzahl+(*(text + i))) += 1;
        }
        i++;
    }
    return Stringlaenge;
}

//Ausgabemaske mit Ergebnissen
void printCounted(unsigned int *counted, int stringlaenge)
{

    int Zeichen ;
    int j = 0;
    printf("\nAnzahl der Zeichen: %i\n", stringlaenge);
    printf("-----------------------------------------------------------------\n");
    for (i = 0; i < ASCIIMAX ; i++)
    {
       if (*(counted+i) != '\0')
        {
            j++;
            if (i < 32)
            {
                Zeichen = 32;
            }else{
                Zeichen = i;
            }
            printf("| %c (%#04x): %3i ", Zeichen, i,*(counted+i));
            if (j%4 == 0)
               printf("|\n");
        }
    }
    if(!(j%4))
    printf("-----------------------------------------------------------------\n");
    else
    {
        while( j++%4)
        {
            printf("|               ");
        }      
        printf("|\n-----------------------------------------------------------------\n");
    }
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


//Programm wiederholen
int askAgain()
{
char W;
printf("Moechten Sie noch einmal (j/n) "); // Eingabeaufforderung
while (!scanf("%[jJnN]", &W))
    {
        UP_LINE;
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
