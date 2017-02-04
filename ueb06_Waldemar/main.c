#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "menu.h"
#include "calendar.h"
#include "database.h"
#include "datastructure.h"

int main()
{
	const char *mainMenuTitle = "Terminverwaltung V 1337";

	const char *mainMenu[] = {
                                "1. Neuen Termin anlegen",
                                "2. Termin bearbeiten",
                                "3. Termin loeschen",
                                "4. Termin Suchen",
                                //"5. Termin Sortieren",
                                "5. Termin auflisten",
                                "6. Programm beenden"
                            };

	int Input = 0,
        endprog = 0,
        skipenter = 0;

    if( loadCalendar() == 0 )
        perror("Calender konnte nicht geladen werden");

	do
	{
		Input = getMenu(mainMenuTitle, mainMenu, 6);

		switch( Input )
		{
            case 1: createAppointment();		break;
            case 2: editAppointment();		    break;
            case 3: deleteAppointment();		break;
            case 4: searchAppointment();    	break;
            //case 5: sortCalendar();		        break;
            case 5: listCalendar();
                    skipenter = 1;              break;
            case 6: endprog = 1;
                    skipenter = 1 ;              break;
		}

		if ( !endprog && skipenter )
        {
            printf("\n");
            waitForEnter();
            skipenter = 0;
        }

		else
			printf("\nProgramm wird beendet\n");

	} while ( !endprog );

	saveCalendar();

	freeCalender();

	return 0;
}
