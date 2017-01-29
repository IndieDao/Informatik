#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "calendar.h"
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
#define TERMIN 100              /*max Menge Termine   */

extern int countAppointments = 0;

extern TAppointment calendar[MAX_APPOINTEMENTS];

//  --------------------------------------------------------------------------------
/** \brief tauscht die Stellen zweier Appointments
 *
 * \param Appointment1 TAppointment*
 * \param Appointment2 TAppointment*
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void swapAppointment( TAppointment *Appointment1, TAppointment *Appointment2 )
{
    TAppointment temp;

    temp = *Appointment1;
    *Appointment1 = *Appointment2;
    *Appointment2 = temp;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Zeit von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt (T1 > T2 = -1) , ( T1 = T2 = 0 ), ( T1 < T2 = 1 ) aus.
 *
 */
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
    printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int           gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDuration(TAppointment Appointment1, TAppointment Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour) ? 0 : 1;
    if(!Appointment1.Duration)
    {
        return -1;
    }

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
    //printf("Vergleich = %i", Vergleich);
    return Vergleich;
}
//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int           gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDate(TAppointment Appointment1, TAppointment Appointment2)
{
    //printf("\nI  %2i.%2i.%4i\n", Appointment1.DateOfAppointment.Day, Appointment1.DateOfAppointment.Month, Appointment1.DateOfAppointment.Year);
    //printf("II %2i.%2i.%4i\n", Appointment2.DateOfAppointment.Day, Appointment2.DateOfAppointment.Month, Appointment2.DateOfAppointment.Year);
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
    //printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDescription(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Beschreibung), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Beschreibung), sizeof(char));

    strcpy(App1, Appointment1.Beschreibung);
    strcpy(App2, Appointment2.Beschreibung);
    for( i = 0 ; i <= strlen(App1) ; i++)
    {
        if(*(App1+i) > 96)
            *(App1+i)-= 32;
    }

    for( i = 0 ; i <= strlen(App2); i++)
    {
        if(*(App2+i) > 96)
            *(App2+i)-= 32;
    }
    i=0;
    do
    {
        if (*(App1+i) > *(App2+i) )
            return 1;

        else if (*(App1+i) < *(App2+i) )
            return -1;

    }
    while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareLocation(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Location), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Location), sizeof(char));


    strcpy(App1, Appointment1.Location);
    strcpy(App2, Appointment2.Location);

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
            return 1;

        else if (*(App1+i) < *(App2+i) )
            return -1;

    }
    while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergleicht zwei Termine
 *
 * \param Appointment1 TAppointment*
 * \param Appointment2 TAppointment*
 * \return int          gibt bei Gleichheit 0 zurück
 *
 */
//  --------------------------------------------------------------------------------
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
/** \brief erstellt einen Termin in temporärem Kalender und speichert den Termin abschließend ins "calendar" Array.
 *
 * \return void
 *
 */
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
/** \brief bearbeitet einen Termin in temporärem Kalender und speichert den Termin abschließend nach "calendar".
 *
 * \return void
 *
 */
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
/** \brief löscht einen Termin indem der Zeiger auf das nächste Element gesetzt wird.
 *
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void deleteAppointment()
{
    int i;
    int WithDate = 1;

    char *Titel = "TermineListe";
    printf("\n%s\n", Titel);
    printLine('-', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
    printf("\n");
    if(countAppointments > 0)
    {
        //Ausgabe für Termin mit gleichem Datum
        for(i = 0 ; i < countAppointments; i++)
        {
            printf("%i.) ", countAppointments);
        }
    }
    else
    {
        printf("\nkeine Termine gespeichert.\n");
    }
    waitForEnter();


    waitForEnter();
}

void searchAppointment()
{
    printf("Termin suchen\n");

    waitForEnter();
}

//  --------------------------------------------------------------------------------
/** \brief ruft die (Quick-Sort)-funktionen, an den richtigen Indizes für die gewählte Sortierung auf.
 *
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void sortCalendar()
{
    int Gleich = 0;
    int endGleich = 1;

    int Anz = 5;
    int Ende = 1;
    int Wahl;
    char *Menu = "Termine sortieren";
    char *Menupunkte[] =   {"Sortieren nach Datum und Uhrzeit",
                            "Sortieren nach Beschreibung",
                            "Sortieren nach Ort",
                            "Sortieren nach Dauer",
                            "Zurueck zum Hauptmenue"
                           };
    do
    {
        //clearScreen();
        printf("\n");
        FORECOLOR_YELLOW;
        Wahl = getMenu( Menu, Menupunkte, Anz);

        switch(Wahl)
        {
        case 1:
            //printf("\n Abfrage I kleiner als II %i", compareDate(calendar[1],calendar[0]));
            quicksort(&(calendar), countAppointments, compareDate, swapAppointment );
            listCalendar();
            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                //printf("\n%i , %i | %i\n", Gleich, endGleich, countAppointments);
                if((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + endGleich) == 0))
                {
                    while((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + endGleich) == 0))
                    {
                        printf("\n%i , %i\n", Gleich, endGleich);
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                }
                else if(endGleich<countAppointments)
                    endGleich++;
            }
            Ende = 0;
            //clearScreen();
            printf("Sortierung Datum / Zeit.\n");
            listCalendar();
            break;

        case 2: //printf("%i", compareDescription(calendar[3],calendar[2]));
            quicksort(&(calendar), countAppointments, compareDescription, swapAppointment );
            listCalendar();

            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                endGleich = Gleich +1;
                if((endGleich<countAppointments) && (compareDescription( calendar[Gleich], calendar[endGleich])) == 0)
                {
                    printf("\nschon\n mal richtig", Gleich, endGleich);
                    while((endGleich<countAppointments) && (compareDescription( calendar[Gleich], calendar[endGleich] ) == 0))
                    {
                        printf("\n%i , %i\n", Gleich, endGleich);
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareDate, swapAppointment);
                    listCalendar();
                    endGleich = Gleich +1;
                    for(; Gleich <= endGleich; Gleich++)
                    {
                        if((endGleich<countAppointments) && (compareEquality( calendar + Gleich, calendar + endGleich )== 0))
                        {
                            while((endGleich<countAppointments) && (compareEquality( calendar + Gleich, calendar + endGleich )== 0))
                            {
                                endGleich++;
                            }
                            Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                        }
                        else if(endGleich<countAppointments)
                            endGleich++;
                    }
                }
                else if(endGleich<countAppointments)
                    endGleich++;
            }

            Ende = 0;
            //clearScreen();
            printf("Sortierung Beschreibung / Datum / Zeit.\n");
            listCalendar();
            break;

        case 3: //printf("%i", compareLocation(calendar[2],calendar[3]));
            quicksort( &calendar, countAppointments, compareLocation, swapAppointment );

            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                if((endGleich<countAppointments) && (compareLocation( *(calendar+Gleich), *(calendar+endGleich )) == 0))
                {
                    while((endGleich<countAppointments) && (compareLocation( *(calendar+Gleich), *(calendar+endGleich ) ) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareDate, swapAppointment);

                    endGleich = Gleich +1;                                                                   //Sortierung nach Zeit
                    for(; Gleich <= endGleich; Gleich++)
                    {
                        if((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich)) == 0))
                        {
                            while((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich) )== 0))
                            {
                                endGleich++;
                            }
                            Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                        }
                        else if(endGleich<countAppointments)
                            endGleich++;
                    }
                }
                else if(endGleich<countAppointments)
                    endGleich++;
            }

            Ende = 0;
            //clearScreen();
            printf("Sortierung Ort / Datum / Zeit.\n");
            break;


        case 4:
            //printf("  %i", compareDuration(calendar[0],calendar[1]));
            quicksort(&calendar, countAppointments, compareDuration, swapAppointment );



            Ende = 0;
            //clearScreen();
            printf("Sortierung Dauer / Datum / Zeit.\n");
            break;

        case 5:
            Ende = 0;
            break;
        }
        FORECOLOR_WHITE;
    }
    while (Ende);
    //listCalendar();
    //waitForEnter();
}

//  --------------------------------------------------------------------------------
/** \brief Gibt jeweils einen Termin aus. Termine gleichen Datums werden zusammen ausgegeben.
 *
 * \param Appointment TAppointment*
 * \param WithDate int wird gesetzt, bei Terminen gleichen Datums
 * \return void
 *
 */
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
/** \brief Bildschirmausgabe der geladenen Termine
 *
 * \return void
 *
 */
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
/** \brief löscht den im Programmspeicher angelegten Kalender
 *
 * \return void
 *
 */
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
void freeAppointment();
