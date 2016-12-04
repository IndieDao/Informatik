#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include <string.h>
/*************************************************************************
*   Alle Kalenderfunktionen des Hauptmenüs werden hier als Funktion
*   programmiert. Die Benutzerführung, sowie einzelne Unterprogramme.
*************************************************************************/

#define ORT 15            /*max Laenge Ortseingabe   */
#define TERMIN 100

int countAppointments = 0;

TAppointment calendar[MAX_APPOINTEMENTS];
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void createAppointment()
{
    char *Titel = "\nErfassung eines neuen Termins\n";
    TAppointment *Appointment;
    Appointment = calloc(1, sizeof(TAppointment));

    printf("%s", Titel);
    printLine('=', (strlen(Titel)-2));                  //Umbruch muss abgezogen werden
    getDate("Datum        :", &Appointment->DateOfAppointment);
    getTime("Uhrzeit      :", &Appointment->TimeOfAppointment);
    getText("Beschreibung :", &Appointment->Beschreibung, TERMIN, 1);
    getText("Ort          :", &Appointment->Location, ORT, 1);
    getTime("Dauer        :",(*Appointment).Duration);
    calendar[countAppointments] = *Appointment;         //schreibt Termin in Hauptkalender
    countAppointments++;
    printf("Termin wurde gespeichert!");
    free(Appointment);
    Appointment = NULL;
    waitForEnter();
}

void editAppointment()
{
    printf("Termin bearbeiten");

    waitForEnter();
}


void deleteAppointment()
{
    printf("Termin loeschen\n");

    waitForEnter();
}

void searchAppointment()
{
    printf("Termin suchen\n");

    waitForEnter();
}

void sortCalendar()
{
    printf("Termine sortieren\n");

    waitForEnter();
}

void listCalendar()
{
    //k = 1;
    if(countAppointments > 0)
    {
        char *Titel = "\nListe der Termine\n";
        printf("%s", Titel);
        printLine('=', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
        printDate(calendar);
    }
    else
    {
        printf("\nkeine Termine gespeichert.\n");
    }
    waitForEnter();
}

void freeCalendar()
{
/*
int x;
    for(x = 0 ; x <= MAX_APPOINTEMENTS; x++)
    {
    calendar[x] = NULL;
    }
*/
}
void freeAppointment();
