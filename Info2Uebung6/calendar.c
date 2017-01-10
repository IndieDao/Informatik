#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
#include "sort.h"
#include <string.h>
#include "escapesequenzen.h"
/*************************************************************************
*   Alle Kalenderfunktionen des Hauptmenüs werden hier als Funktion
*   programmiert. Die Benutzerführung, sowie einzelne Unterprogramme.
*************************************************************************/

#define ORTEINGABE 15            /*max Laenge Ortseingabe   */
#define TERMIN 100
#define DATUM 0
#define DAUER 1
#define BESCHREIBUNG 2
#define ORT 3

int countAppointments = 0;

TTime Duration[MAX_APPOINTEMENTS];

TAppointment calendar[MAX_APPOINTEMENTS];


void swapAppointment(TAppointment Appointment1, TAppointment Appointment2)
{
    TAppointment temp;
    // setze Vergleichselement (Schranke zwischen beide Teile)
    temp = Appointment2;
    Appointment2 = Appointment1;
    Appointment1 = temp;
}

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
int compareDuration(TAppointment Appointment1, TAppointment Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour) ? 0 : 1;
    if(Appointment1.Duration->Hour == Appointment2.Duration->Hour)
    {
        if ( Appointment1.Duration->Minute == Appointment2.Duration->Minute )
        {
            if ( Appointment1.Duration->Second == Appointment2.Duration->Second )
            {
                Vergleich = 0;
            }
            else if ( Appointment1.Duration->Second > Appointment2.Duration->Second )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1.Duration->Minute > Appointment2.Duration->Minute)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1.Duration->Hour > Appointment2.Duration->Hour)
    {
        Vergleich = 1;
    }
    return Vergleich;
}

int compareDate(TAppointment Appointment1, TAppointment Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year) ? 0 : 1;
    if(Appointment1.DateOfAppointment.Year == Appointment2.DateOfAppointment.Year)
    {
        if ( Appointment1.DateOfAppointment.Month == Appointment2.DateOfAppointment.Month )
        {
            if ( Appointment1.DateOfAppointment.Day == Appointment2.DateOfAppointment.Day )
            {
                Vergleich = 0;
            }
            else if ( Appointment1.DateOfAppointment.Day > Appointment2.DateOfAppointment.Day )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1.DateOfAppointment.Month > Appointment2.DateOfAppointment.Month)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1.DateOfAppointment.Year > Appointment2.DateOfAppointment.Year)
    {
        Vergleich = 1;
    }
    return Vergleich;
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
int compareDescription(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Beschreibung), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Beschreibung), sizeof(char));

    App1 = Appointment1.Beschreibung;
    App2 = Appointment2.Beschreibung;
    for( i = 0 ; i <= strlen(Appointment1.Beschreibung) ; i++)
    {
        if(*(App1+i) > 96)
            *(App1+i)-= 32;
    }

    for( i = 0 ; i <= strlen(Appointment2.Beschreibung); i++)
    {
        if(*(App2+i) > 96)
            *(App2+i)-= 32;
    }
    i=0;
    do
    {
        if (*(App1+i) > *(App2+i) )
            return -1;

        else if (*(App1+i) < *(App2+i) )
            return 1;

    }while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    return Vergleich;
 }
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
int compareLocation(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Location), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Location), sizeof(char));

    App1 = Appointment1.Location;
    App2 = Appointment2.Location;

    for( i = 0 ; i <= strlen(Appointment1.Location) ; i++)
    {
        if(*(App1+i) > 96)
            *(App1+i)-= 32;
    }
    for( i = 0 ; i <= strlen(Appointment2.Location); i++)
    {
        if(*(App2+i) > 96)
            *(App2+i)-= 32;
    }
    i=0;
    do
    {
        if (*(App1+i) > *(App2+i) )
            return -1;

        else if (*(App1+i) < *(App2+i) )
            return 1;

    }while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    return Vergleich;
 }
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
int compareTime(TAppointment Appointment1, TAppointment Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour) ? 0 : 1;
    if(Appointment1.TimeOfAppointment.Hour == Appointment2.TimeOfAppointment.Hour)
    {
        if ( Appointment1.TimeOfAppointment.Minute == Appointment2.TimeOfAppointment.Minute )
        {
            if ( Appointment1.TimeOfAppointment.Second == Appointment2.TimeOfAppointment.Second )
            {
                Vergleich = 0;
            }
            else if ( Appointment1.TimeOfAppointment.Second > Appointment2.TimeOfAppointment.Second )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1.TimeOfAppointment.Minute > Appointment2.TimeOfAppointment.Minute)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1.TimeOfAppointment.Hour > Appointment2.TimeOfAppointment.Hour)
    {
        Vergleich = 1;
    }
    return Vergleich;
}

int compareEquality(TAppointment *Appointment1, TAppointment *Appointment2)
{
    if(    Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year
        && Appointment1->DateOfAppointment.Month == Appointment2->DateOfAppointment.Month
        && Appointment1->DateOfAppointment.Day == Appointment2->DateOfAppointment.Day)
        return 0;
    else if(    Appointment1->DateOfAppointment.Year >= Appointment2->DateOfAppointment.Year
        || Appointment1->DateOfAppointment.Month >= Appointment2->DateOfAppointment.Month
        || Appointment1->DateOfAppointment.Day >= Appointment2->DateOfAppointment.Day)
        return 1;
    else
        return -1;
}

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void createAppointment()
{
    //TTime Duration;

    char *Titel = "\nErfassung eines neuen Termins\n";
    TAppointment *Appointment;
    Appointment = calloc(1, sizeof(TAppointment));

    printf("%s", Titel);
    printLine('=', (strlen(Titel)-2));                  //Umbruch muss abgezogen werden
    getDate("Datum        :", &Appointment->DateOfAppointment);
    getTime("Uhrzeit      :", &Appointment->TimeOfAppointment);
    getText("Beschreibung :", &Appointment->Beschreibung, TERMIN, 1);
    getText("Ort          :", &Appointment->Location, ORTEINGABE, 1);
    //getTime("Dauer        :", &Duration);
    Appointment->Duration = calloc (1, sizeof(TTime));
    getTime("Dauer        :", Appointment->Duration);
    //getTime("Dauer        :",(*Appointment).Duration);
    calendar[countAppointments].Duration = calloc (1, sizeof(TTime)); // weil Dauer ein Zeiger ist
    calendar[countAppointments] = *Appointment;         //schreibt Termin in Hauptkalender
    //calendar[countAppointments].Duration = &Duration;
    countAppointments++;
    printf("Termin wurde gespeichert!");
    free(Appointment);
    waitForEnter();
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void editAppointment()
{
    int i;
    printf("Termin bearbeiten");
    for(i=0; i<=countAppointments; i++)
    {
    printf("%02i:%02i\n", calendar[i].Duration->Hour, calendar[i].Duration->Minute);
    printf("%s\n", calendar[i].Beschreibung);
    }

    waitForEnter();
}

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
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
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void sortCalendar()
{
int Anz = 5;
int Ende = 1;
int Wahl;
char *Menu = "Termine sortieren";
char *Menupunkte[] =   {"Sortieren nach Datum und Uhrzeit",
                        "Sortieren nach Beschreibung",
                        "Sortieren nach Ort",
                        "Sortieren nach Dauer",
                        "Zurueck zum Hauptmenue"};
   do
   {
       //clearScreen();
       printf("\n");
       FORECOLOR_YELLOW;
       Wahl = getMenu( Menu , Menupunkte , Anz);
                        /** FEHLER   Verzweigung in die einzelnen Programmmodule   */
        switch(Wahl)
        {
            case 1:
                    printf("%i", compareDate(calendar[0],calendar[1]));
                    quicksort(&(calendar), countAppointments, DATUM );
                    Ende = 0;
                    break;

            case 2: printf("%i", compareDescription(calendar[3],calendar[2]));
                    //quicksort(calendar, countAppointments, DAUER );
                    Ende = 0;
                    break;

            case 3: printf("%i", compareLocation(calendar[2],calendar[3]));
                    //quicksort(&calendar, countAppointments, BESCHREIBUNG );
                    Ende = 0;
                    break;

            case 4: printf("  %i", compareDuration(calendar[0],calendar[1]));
                    //quicksort(&calendar, countAppointments, ORT );
                    Ende = 0;
                    break;
            case 5: Ende = 0;
                    break;
        }
        FORECOLOR_WHITE;
   } while (Ende);
    //waitForEnter();
}

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void listAppointment(TAppointment *Appointment, int WithDate)
{
    int j;

    if (WithDate)
    {
        printf("\n\n");
        FORECOLOR_BLUE;
        printLine('=', 85);
        FORECOLOR_WHITE;
        printDate( Appointment);
        printLine('~', 36);
    }
    printTime( Appointment);
    printf(" %-14s     | ", Appointment->Location);

    int len_Beschreibung = (unsigned) strlen(Appointment->Beschreibung);

    if(len_Beschreibung <= 48)
        printf(" %-s\n", Appointment->Beschreibung);

    else if( len_Beschreibung > 48)
    {
        printf(" ");
        for(j = 0; j < 43; j++)
            printf("%c", (Appointment->Beschreibung)[j]);

        printf("...\n");
    }
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
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
                WithDate = (compareEquality(calendar + i, calendar + i + 1) != 0);

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
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void freeCalendar()
{
int i;
    for(i = 0 ; i <countAppointments; i++)
    {
        calendar[i].Beschreibung = '\0';
        calendar[i].DateOfAppointment.Day = '\0';
        calendar[i].DateOfAppointment.Month = '\0';
        calendar[i].DateOfAppointment.Year = '\0';
        calendar[i].Location = '\0';
        calendar[i].TimeOfAppointment.Hour = '\0';
        calendar[i].TimeOfAppointment.Minute = '\0';
        calendar[i].TimeOfAppointment.Second = '\0';
    }
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void freeAppointment();
