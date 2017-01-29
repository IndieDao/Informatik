#include "calendar.h"
#include "tools.h"
#include "menu.h"
#include "datastructure.h"
#include "database.h"

int main() {

	char *Titel = "Terminverwaltung V 0.2";
	char *Menu[] =
	{
		"Neuen Termin anlegen",
		"Termin bearbeiten",
		"Termin loeschen",
		"Termin suchen",
		"Termine sortieren",
		"Termine auflisten",
		"Programm beenden"
	};

	int choice;

	// load calendar

	int appcnt = loadCalendar(calendar, MAXAPPOINTMENTS);

	do
	{
		choice = getMenu(Titel, Menu, 7);
		switch (choice)
		{
		case 1:
			createAppointment(calendar + appcnt);
			appcnt++;
			waitForEnter();
			break;
		case 2:
			editAppointment();
			waitForEnter();
			break;
		case 3:
			deleteAppointment();
			waitForEnter();
			break;
		case 4:
			searchAppointment();
			waitForEnter();
			break;
		case 5:
			sortCalendar(calendar, appcnt);
			waitForEnter();
			break;
		case 6:
			listCalendar(calendar, MAXAPPOINTMENTS);
			waitForEnter();
			break;
		case 7:
			break;
		}
	} while (choice != 7);

	// save changes
	if (saveCalendar(calendar, appcnt))
		printf("Kalender erfolgreich gespeichert.\n");
	else
		printf("Beim Speichern des Kalenders trat ein Fehler auf.\n");

	// clean up
	int i = 0;
	for (i = 0; i < appcnt; i++) {
		free(calendar[i].description);
		free(calendar[i].location);
		free(calendar[i].duration);
	}

	printf("Datenbank entladen.\n"); 

	waitForEnter();
	printf("Programm wurde beendet!\n");
	return 0;
}