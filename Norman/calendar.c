#include <stdio.h>
#include "calendar.h"


int countAppointments = 0;
TAppointment calendar[MAXAPPOINTMENTS];

void SwapAppointment(TAppointment *app1, TAppointment *app2) {
	TAppointment tmpd = *app1;

	*app1 = *app2;
	*app2 = tmpd;
}

int CmpAppDate(TAppointment *app1, TAppointment *app2, int asc) {
	if (app1->date.year > app2->date.year)
		return (asc) ? 1 : -1;
	else if (app1->date.year < app2->date.year)
		return (asc) ? -1 : 1;
	else { //year1 == year2
		if (app1->date.month > app2->date.month)
			return (asc) ? 1 : -1;
		else if (app1->date.month < app2->date.month)
			return (asc) ? -1 : 1;
		else { // month 1 == month2
			if (app1->date.day > app2->date.day)
				return (asc) ? 1 : -1;
			else if (app1->date.day < app2->date.day)
				return (asc) ? -1 : 1;
			else { // day1 == day2, cmp time
				if (app1->time.hour > app2->time.hour)
					return (asc) ? 1 : -1;
				else if (app1->time.minute < app2->time.minute)
					return (asc) ? -1 : 1;
				else
					return 0;
			}
		}
	}
}

int CmpAppDesc(TAppointment *app1, TAppointment *app2, int asc) {
	if (strcmp(app1->description, app2->description) < 0)
		return (asc) ? 1 : -1;
	else if (strcmp(app1->description, app2->description) > 0)
		return (asc) ? -1 : 1;
	else { //desc == desc
		return 0;
	}
}

int CmpAppLoc(TAppointment *app1, TAppointment *app2, int asc) {
	if (strcmp(app1->location, app2->location) < 0)
		return (asc) ? 1 : -1;
	else if (strcmp(app1->location, app2->location) > 0)
		return (asc) ? -1 : 1;
	else { //desc == desc
		return 0;
	}
}

int CmpAppDur(TAppointment *app1, TAppointment *app2, int asc) {
	if (app1->duration->hour > app2->duration->hour)
		return (asc) ? 1 : -1;
	else if (app1->duration->minute < app2->duration->minute)
		return (asc) ? -1 : 1;
	else
		return 0;
}

void createAppointment(TAppointment *app) {

	TAppointment* tmpapp = NULL;
	TTime dur;

	app->duration = (TTime*)malloc(sizeof(TTime));

	clearScreen();

	printf("Erfassung eines neuen Termins\n");
	printLine('=', 20);

	while (getDate("Datum (TT.MM.JJJJ): ", &app->date) != 1) {
		printf("Bitte geben Sie ein gueltiges Datum an.\n");
	}

	while (getTime("Uhrzeit (HH:MM(:SS)): ", &app->time, 0) != 1) {
		printf("Bitte geben Sie eine gueltige Uhrzeit an.\n");
	}

	while (getText("Beschreibung (max. 100 Zeichen): ", 100, &app->description, 1) != 1);

	while (getText("Ort (max. 15 Zeichen): ", 15, &app->location, 0) != 1);

	while (getTime("Dauer (HH:MM(:SS)): ", &dur, 1) != 1) {
		printf("Bitte geben Sie einen positiven Wert fuer die Dauer des Termins an. \n");
	}

	*app->duration = dur;

	app = (TAppointment*)malloc(sizeof(TAppointment));
	app = tmpapp;

	printf("\nTermin wurde gespeichert.");
};

void  editAppointment() {
	printf("editAppointment\n");
};

void  deleteAppointment() {
	printf("deleteAppointment\n");
};

void  searchAppointment() {


};

void  sortCalendar(TAppointment *app, int entrycount) {
	clearScreen();

	char *menutext = "Termine sortieren\n";
	printf(menutext);
	printLine('=', strlen(menutext));

	printf("1. Sortieren nach Datum und Uhrzeit\n");
	printf("2. Sortieren nach Beschreibung\n");
	printf("3. Sortieren nach Ort\n");
	printf("4. Sortieren nach Dauer\n");
	printf("5. Zurueck zum Hauptmenue\n\n");

	printf("Ihre Wahl: ");

	int wahl = 0;

	while (scanf("%i", &wahl) <= 0 || (wahl < 1 || wahl>5)) {
		clearBuffer();
		printf("Bitte geben Sie eine Zahl von 1 bis 5 ein.\n\n");
		printf("Ihre Wahl: ");
	}

	clearBuffer();

	int asc;

	char *sorttext = "\nBitte bestimmen Sie die Sortierreihenfolge\n\n";
	printf(sorttext);
	printLine('=', strlen(sorttext));

	printf("1. Aufsteigend\n");
	printf("2. Absteigend\n\n");
	printf("Ihre Wahl: ");
	while (scanf("%i", &asc) <= 0 || (asc < 1 || asc>2)) {
		clearBuffer();
		printf("Bitte geben Sie eine Zahl von 1 bis 2 ein.\n");
		printf("Ihre Wahl: ");
	}

	clearBuffer();

	if (asc == 1)
		asc = 1;
	else
		asc = 0;

	switch (wahl) {
	case 1:
		QuickSort(app, entrycount, CmpAppDate, SwapAppointment, asc);
		printf("Sortierung abgeschlossen.\n");
		break;
	case 2:
		QuickSort(app, entrycount, CmpAppDesc, SwapAppointment, asc);
		printf("Sortierung abgeschlossen.\n");
		break;
	case 3:
		QuickSort(app, entrycount, CmpAppLoc, SwapAppointment, asc);
		printf("Sortierung abgeschlossen.\n");
		break;
	case 4:
		QuickSort(app, entrycount, CmpAppDur, SwapAppointment, asc);
		printf("Sortierung abgeschlossen.\n");
		break;
	case 5:
		return;
	}
};

void listCalendar(TAppointment *app, int entrycount) {
	clearScreen();
	printf("\nListe der Termine\n");
	printLine('=', 16);

	int i;
	for (i = 0; i < entrycount; i++) {

		if (app->date.weekday != 0) {
			if (!sameDate(&app->date, &(app - 1)->date) || i == 0) {
				printLine('=', 80);
				printf("\n");
				printDOW(&app->date);
				printf(", ");
				printDate(&app->date);
				printf(":\n");
				printLine('-', 15);
			}

			printAppointment(app);
			printf("\n");
		}
		app++;
	}
}