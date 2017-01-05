#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include <string.h>
#include "escapesequenzen.h"
/*************************************************************************
*   Alle Kalenderfunktionen des Hauptmenüs werden hier als Funktion
*   programmiert. Die Benutzerführung, sowie einzelne Unterprogramme.
*************************************************************************/

#define ORT 15            /*max Laenge Ortseingabe   */
#define TERMIN 100

int countAppointments = 0;

TAppointment calendar[MAX_APPOINTEMENTS];

int compareDate(TAppointment *Appointment1, TAppointment *Appointment2)
{
    if(    Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year
        && Appointment1->DateOfAppointment.Month == Appointment2->DateOfAppointment.Month
        && Appointment1->DateOfAppointment.Day == Appointment2->DateOfAppointment.Day)
        return 0;
    else
        return 1;
}

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void createAppointment()
{
    TTime Duration;

    char *Titel = "\nErfassung eines neuen Termins\n";
    TAppointment *Appointment;
    Appointment = calloc(1, sizeof(TAppointment));

    printf("%s", Titel);
    printLine('=', (strlen(Titel)-2));                  //Umbruch muss abgezogen werden
    getDate("Datum        :", &Appointment->DateOfAppointment);
    getTime("Uhrzeit      :", &Appointment->TimeOfAppointment);
    getText("Beschreibung :", &Appointment->Beschreibung, TERMIN, 1);
    getText("Ort          :", &Appointment->Location, ORT, 1);
    getTime("Dauer        :", &Duration);
    //getTime("Dauer        :",(*Appointment).Duration);
    calendar[countAppointments].Duration = calloc (1, sizeof(TTime)); // weil Dauer ein Zeiger ist
    calendar[countAppointments] = *Appointment;         //schreibt Termin in Hauptkalender
    calendar[countAppointments].Duration = &Duration;
    countAppointments++;
    printf("Termin wurde gespeichert!");
    free(Appointment);
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


void listAppointment(TAppointment *Appointment, int WithDate)
{
    int j;

    if (WithDate)
    {
        printf("\n\n");
        FORECOLOR_BLUE;
        printLine('=', 81);
        FORECOLOR_WHITE;
        printDate( Appointment);
        printLine('~', 28);
    }
    printTime( Appointment);
    printf("%15s     | ", Appointment->Location);

    int len_Beschreibung = (unsigned) strlen(Appointment->Beschreibung);

    if(len_Beschreibung <= 48)
        printf(" %s\n", Appointment->Beschreibung);

    else if( len_Beschreibung > 48)
    {
        for(j = 0; j < 44; j++)
            printf("%c", (Appointment->Beschreibung)[j]);

        printf("...\n");
    }

}

void listCalendar()
{
    int i;
    int WithDate = 1;

    char *Titel = "Liste der Termine";
    printf("\n%s\n", Titel);
    printLine('=', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
    printf("\n");
    if(countAppointments > 0)
    {
        //Ausgabe für Termin mit gleichem Datum
        for(i = 0 ; i < countAppointments; i++)
        {
            listAppointment(calendar + i, WithDate);
            if (i < countAppointments -1)
                WithDate = (compareDate(calendar + i, calendar + i + 1) != 0);

            if(i!= 0 && (i %15) == 0)
                waitForEnter();
        }
    }
    else
    {
        printf("\nkeine Termine gespeichert.\n");
    }
    waitForEnter();
}

void freeCalendar(TAppointment *calendar)
{
int i;
    for(i = 0 ; i <countAppointments; i++)
    {
    free(&calendar[i]);
    }
}

void freeAppointment();
