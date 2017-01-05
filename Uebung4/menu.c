#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"
#include <string.h>

/*************************************************************************
*   Exklusives Modul für die Zeichnung der aktiven Programmpunkte
*   und der darauf folgenden Nutzerauswahl
*************************************************************************/

int getMenu(char *MenuTitel, char **MenuPunkte, int Anz)    // Anz steht hier für die Anzahl der Menüpunkte
{
    int j;
    int Wahl = 0;
    int Eingabe = 0;

    printf("%s\n", MenuTitel);                              // Bildschirmausgabe des Titels
    printLine('=', strlen(MenuTitel));

    for(j = 0; j < Anz; j++)                                // Bildschirmausgabe der Menuepunkte
    {
        printf("%i. %s \n", (j + 1), *(MenuPunkte + j) );
    }

    while ((Wahl > Anz) || !Eingabe)                        // solange die Nutzereingabe nicht stimmt...
    {
        printf("\n");
        CLEAR_LINE;
        printf("Ihre Wahl: ");
        Eingabe = scanf("%i", &Wahl);
        clearBuffer();
        if( (Wahl > Anz) || !Eingabe )                      // der eingegebe Wert muss zwischen 1 und Anz sein
        {
            UP(2);
            FORECOLOR_RED;
            printf("   falsche Eingabe!");
            FORECOLOR_WHITE;
        }
    }
    return Wahl;                                            // Funktionswahl fürs Hauptmenue
}
