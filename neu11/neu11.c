#include <stdio.h>
#include"text.h"
#include"tools.h"
#include"escapesequenzen.h"

int main()
{
    int const MaxLaenge = 201;
    char EingabeSatz[MaxLaenge];
    int Breite;
    
    do
    {
        CLEAR;
        HOME;
        printf("Textanzeige mit variabler Breite\n\n");
        getText("geben Sie bitte den Text ein (min.1  Zeichen; max. 200 Zeichen):\n", EingabeSatz);
        printf("\n");
        getWidth("In welcher maximalen Breite soll der Text ausgegeben werden (%i-%i): ", 10, 79, &Breite);
        printText(EingabeSatz, Breite);
    } while(askAgain(23, 1));
    return 0;
}
