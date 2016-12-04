//  main.c
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#include <stdio.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "calendar.h"
#include "escapesequenzen.h"
#include "Menu.h"
#include <string.h>



int main()
{
    char * Dateipfad = "/Users/bricedorseylongdje/Documents/2.semester/Info2/a1/a1/Termine.txt";
    int Anz = 9;
    int Ende = 1;
    char Menu[50] = "TerminVerwaltung V 0.2";
    char * MenuPunkte[] = {"Neuen Termin anlegen",
                           "Termin bearbeiten",
                           "Termin suchen",
                           "Termine loeschen",
                           "Termine sortieren",
                           "Termine auflisten",
                           "Termine speichern",
                           "Termine Laden",
                           "Programm beenden"};
    
    do
    {
        
        int Wahl = getMenu( Menu , MenuPunkte , Anz);
        
        //printf("ToDo:");
        
        switch(Wahl)
        {
            case 1: createAppointment();            break;
            case 2: editAppointment();              break;
            case 3: deleteAppointment();            break;
            case 4: searchAppointment();            break;
            case 5: sortCalendar();                 break;
            case 6: listCalendar();                 break;
            case 9:Ende = 0;                        break;
                
                //default: printf("Falsche Wahl\n\n");
        }
        
        
    }while(Ende);
    
    printf("Das Programm wird beendet");
    
    printf("\n");
    waitForEnter();
    
    return 0;
} 
 

/*
 int main()
 {
     TDate Date;
     TTime Time;
     char Input[20];
 
 do
 {
     clearScreen();
     printf("Geben Sie bitte ein gueltiges Datum ein: ");
     *Input = '\0';
     scanf("%19[^\n]", Input);
     clearBuffer();
     if (*Input)
         if (getDateFromString(Input, &Date))
             printf("Das Datum %02i.%02i.%04i ist gueltig!\n", Date.Day, Date.Month, Date.Year);
         else
             printf("Das eingegebene Datum %s ist ungueltig!\n", Input);
         else
             printf("Sie haben nichts eingegeben!\n");
 
     printf("Geben Sie bitte eine gueltige Uhrzeit ein: "); *Input = '\0';
     scanf("%19[^\n]", Input);
     clearBuffer();
     if (*Input)
         if (getTimeFromString(Input, &Time))
             printf("Die Uhrzeit %02i:%02i:%02i ist gueltig!\n", Time.Hour, Time.Minute, Time.Second);
         else
             printf("Die eingegebene Uhrzeit ist ungueltig!\n");
         else
             printf("Sie haben nichts eingegeben!\n");
 
    } while (askAgain("Moechten Sie noch einmal (j/n) ? "));
 
     return 0;
}

*/
