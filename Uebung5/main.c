#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "calendar.h"
#include "menu.h"
#include "database.h"

/*************************************************************************
*   Bei Veränderungen der Menüauswahl verändert man hier die Einträge
*   Die einzelnen Module des Programms werden hier aufgerufen.
*************************************************************************/

#define BUF 255     /*Puffert ...*/

int main()
{
    int Anz = 7;
    int Ende = 1;
    int Wahl;
    loadCalendar();

    char *Menu = "Termin-Verwaltung V 0.2";
    char *Menupunkte[] =   {"Neuen Termin anlegen",
                            "Termin bearbeiten",
                            "Termin loeschen",
                            "Termin suchen",
                            "Termine sortieren",
                            "Termine auflisten",
                            "Programm beenden"};
   do
   {
       clearScreen();
       Wahl = getMenu( Menu , Menupunkte , Anz);
                                                                    //   Verzweigung in die einzelnen Programmmodule
        switch(Wahl)
        {
            case 1: createAppointment(); break;
            case 2: editAppointment();   break;
            case 3: deleteAppointment(); break;
            case 4: searchAppointment(); break;
            case 5: sortCalendar();      break;
            case 6: listCalendar();      break;
            case 7: printf("Das Programm wird beendet");
                    Ende = 0;            break;
        }
   } while (Ende);                                                  // Ende des Hauptprogramms
   saveCalendar();
   freeCalendar();
   return 0;
}
