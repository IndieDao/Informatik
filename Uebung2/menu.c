#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "calendar.h"

void getMenu(char *MenuTitel, char Menupkt, int AnzahlMenupunkte)
{
    int k = 0;
    int l = 0;
    printf(MenuTitel);
    printLine(50);
    for ( k = 0; k < AnzahlMenupunkte; k++)
    {
        while (*(Menupkt[k]+l) != '\0')
        {
            printf( "%c", Menupkt[k][l++] );
        }
        printf("\n");
    }
}
