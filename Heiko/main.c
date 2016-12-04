#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "calendar.h"
#include "menu.h"

#define BUF 255

int main()
{
    int Anz = 7;
//    int Ende = 1;

    char Menu[50] = "TerminVerwaltung V 0.2";
    char *Menupunkte[] = {"Neuen Termin anlegen", "Termin bearbeiten", "Termin loeschen", "Termin suchen", "Termine sortieren", "Termine auflisten", "Programm beenden"};


   //TDate Date;
   //TTime Time;
   //char Input[20];

   do
   {
      clearScreen();
       int Wahl = getMenu( Menu , Menupunkte , Anz);

        printf("ToDo:");

        switch(Wahl)
        {
            case 1: createAppointment(); break;
            case 2: editAppointment();   break;
            case 3: deleteAppointment(); break;
            case 4: searchAppointment(); break;
            case 5: sortCalendar();      break;
            case 6: listCalendar();      break;
//            case 7: printf("Das Programm wird beendet");
//                   Ende = 0;             break;
            default: printf("Falsche Wahl\n\n");
        }
   } while (askAgain("Moechten Sie noch einmal (j//n) ? "));
   return 0;
}
