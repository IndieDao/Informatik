//
//  Menu.c
//  a1
//
//  Created by BD on 23.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#include <stdio.h>
#include "Menu.h"
#include "escapesequenzen.h"
#include "tools.h"
#include "calendar.h" 
#include "datastructure.h" 
#include "string.h"

/*************************************************
                                                 *
                                                 *
 Parameter: MenuTitel, die MenuPunkte und die    *
 Anz der MenuPunkte                              *
                                                 *
 Ergebnis: return eine Zahl, die die ausgewählte *
 Menupunkte entspricht                           *
 *************************************************/

int getMenu(char * MenuTitel, char ** MenuPunkte, int Anz) // Anz steht hier für die Anzahl der Menüpunkte
{
    int j;
    int Wahl,
        Eingabe;
    
    do
    {
        printf("\n%s", MenuTitel); // Bildschirmausgabe des Titels >>> einfachne Schreibweise
       
        /*while(*MenuTitel) >>>> man kann auch wie folgt schreiben
        {
            for(int i = 0; *MenuTitel != '\0'; i++)
            {
                printf("%c", *MenuTitel);
                MenuTitel++;
            }
            
        }*/
       
        printf("\n");
        //printLine('=', (unsigned)strlen(MenuTitel) ); // anstatt unsigned kann man auh int schreiben -> Typumwandlung, weil size_t strlen(string) ist die Funktion prototyp, von daher soll size_t in int oder unsigned umgewandelt werden
        
        
        for(j = 0; j < Anz; j++) //Bildschirmausgabe der MenüPunkte
        {
            printf("%i. %s \n", (j + 1), *(MenuPunkte + j) ); //kurze Schreibweise
            
           /* printf("%i. ", (j + 1) ); >>>> komplizierte Schreibweise
            for(int i = 0; *(MenuPunkte[j] + i) != '\0'; i++)
                 printf("%c", *(MenuPunkte[j] + i));
            printf("\n"); */
        
        }
    
        printf("\n");
        printf("Ihre Wahl: ");
        Eingabe = scanf("%i", &Wahl);
        clearBuffer();
        
        //if( ( (Wahl < 1) && (Wahl > Anz) ) || (!Eingabe) ) // die eingegeben Zahl soll zwischen 1 und Anz sein und der Benutzer muss etwas eingeben
            //printf("Falsche Eingabe\n");
           
    }while ( ( (Wahl < 1) && (Wahl > Anz) ) || (!Eingabe) );
    

return Wahl;
}
