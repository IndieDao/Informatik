#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
/*************************************************************************
*   Alle Kalenderfunktionen des Hauptmenüs werden hier als Funktion
*   programmiert. Die Benutzerführung, sowie einzelne Unterprogramme.
*************************************************************************/

#define ORT 15            /*max Laenge Ortseingabe   */
#define TERMIN 100

int countAppointments = 0;
TAppointment calendar[MAX_APPOINTEMENTS];
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Konstrukt und speichert den Termin
//  nach "calendar".
//  --------------------------------------------------------------------------------
void createAppointment()
{
    char *Titel = "\nErfassung eines neuen Termins\n";
    TAppointment *Appointment;
    Appointment = calloc(1, sizeof(TAppointment));

    printf("%s", Titel);
    printLine('=', (Strlen(Titel)-2));                  //Umbruch muss abgezogen werden
    getDate("Datum        :", &Appointment->DateOfAppointment);
    getTime("Uhrzeit      :", &Appointment->TimeOfAppointment);
    getText("Beschreibung :", &Appointment->Beschreibung, TERMIN, 0);
    getText("Ort          :", &Appointment->Location, ORT, 0);
    getTime("Dauer        :",(*Appointment).Duration);
    calendar[countAppointments] = *Appointment;         //funktioniert nicht...
    printf("Termin wurde gespeichert!");
    countAppointments++;
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
    if(countAppointments > 0)
    {
        char *Titel = "\nListe der Termine\n";
        printf("%s", Titel);
        printLine('=', (Strlen(Titel)-2)); //Umbruch muss abgezogen werden
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
/*int x; MAX_APPOINTEMENTS;

    for(x = 0 ; x < MAX_APPOINTEMENTS; x++)
    {
    free(calendar[x]);
    p = NULL
    }
    */
}
void freeAppointment();
