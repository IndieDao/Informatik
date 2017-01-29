#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "datastructure.h"
#include "calendar.h"
#include "datetime.h"
#include "tools.h"
#include "list.h"
#include "sort.h"
#include "compare.h"
#include <string.h>
#include "escapesequenzen.h"
/*************************************************************************
*   Alle Kalenderfunktionen des Hauptmenüs werden hier als Funktion
*   programmiert. Die Benutzerführung, sowie einzelne Unterprogramme.
*************************************************************************/

#define ORTEINGABE 15            /*max Laenge Ortseingabe   */
#define TERMIN 100              /*max Menge Termine   */

extern TAppointment *First, *Last;

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
    Appointment->Duration = calloc(1, sizeof(TTime));    // weil Dauer ein Zeiger ist

    printf("%s", Titel);
    printLine('=', (strlen(Titel)-2));                  //Umbruch muss abgezogen werden
    getDate("Datum        :", &Appointment->DateOfAppointment);
    getTime("Uhrzeit      :", &Appointment->TimeOfAppointment);
    getText("Beschreibung :", &Appointment->Beschreibung, TERMIN, 1);
    getText("Ort          :", &Appointment->Location, ORTEINGABE, 1);
    getTime("Dauer        :", Appointment->Duration);
    //getTime("Dauer        :",(*Appointment).Duration);
    insertInDList(Appointment);
    printf("Termin wurde gespeichert!");
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
    int Wahl = 1;
    int Eingabe = 0;
    TAppointment *temp = First;

    char *Titel = "Termin bearbeiten";
    printf("\n%s\n", Titel);
    printLine('-', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
    printf("\n");

    while ((Wahl > 0) || !Eingabe)                        // solange die Nutzereingabe nicht stimmt...
    {
        i = 1;
        temp = First;
        if(First != NULL)
        {
            while (temp != NULL)
            {
                printf("  %i: ", i);
                printDate(temp);
                printf(", %02i:%02i: %s\n", temp->TimeOfAppointment.Hour, temp->TimeOfAppointment.Minute, temp->Beschreibung);
                i++;
                temp = temp->Next;
            }
        }
        else
        {
            printf("\nkeine Termine gespeichert.\n");
            waitForEnter();
            return;
        }

        printf("\n");
        waitForEnter();
    }
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
    int Wahl = 100;
    int Eingabe = 0;
    TAppointment *temp = First;

    char *Titel = "Terminliste";
    printf("\n%s\n", Titel);
    printLine('-', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
    printf("\n");

    while ((Wahl != 0) || !Eingabe)                        // solange die Nutzereingabe nicht stimmt...
    {
        i = 1;
        temp = First;
        if(First != NULL)
        {
            while (temp != NULL)
            {
                printf("  %i: ", i);
                printDate(temp);
                printf(", %02i:%02i: %s\n", temp->TimeOfAppointment.Hour, temp->TimeOfAppointment.Minute, temp->Beschreibung);
                i++;
                temp = temp->Next;
            }
        }
        else
        {
            printf("\nkeine Termine gespeichert.\n");
            waitForEnter();
            return;
        }

        printf("\n");
        CLEAR_LINE;
        printf("Welchen Termin moechten Sie loeschen (0 fuer Abbrechen) ?");
            Eingabe = scanf("%i", &Wahl);
            clearBuffer();
            if( (Wahl > i) || !Eingabe )                      // der eingegebe Wert muss zwischen 1 und Anz sein
            {
                for ( ; i >= 0 ; i--)
                {
                    UP(1);
                    CLEAR_LINE;
                }
                UP(1);
                FORECOLOR_RED;
                printf("   Eine ordentliche Zahl wählen!\n");
                ATTRIBUTE_OFF;
            }
            else
            {
                if (Wahl != 0)
                    removeFromDList(Wahl);
                for ( ; i >= 0 ; i--)
                {
                    UP(1);
                    CLEAR_LINE;
                }
        }
    }
    return;
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
    /*
    TAppointment calendar[255];    //fester Kalender der Software
    int countAppointments;                       //zählt Einträge
    int Gleich = 0;
    int endGleich;

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
            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                if((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + Gleich + endGleich) == 0))
                {
                    while((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + Gleich + endGleich) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                }
            }
            Ende = 0;
            break;

        case 2: //printf("%i", compareDescription(calendar[3],calendar[2]));
            quicksort(&(calendar), countAppointments, compareDescription, swapAppointment );

            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                endGleich = Gleich +1;
                if((endGleich<countAppointments) && (compareDescription( *(calendar+Gleich), *(calendar+endGleich )) == 0))
                {
                    while((endGleich<countAppointments) && (compareDescription( *(calendar+Gleich), *(calendar+endGleich ) ) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareDate, swapAppointment);
                    endGleich = Gleich +1;
                    for(; Gleich <= endGleich; Gleich++)
                    {
                        if((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich) )== 0))
                        {
                            while((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich) )== 0))
                            {
                                endGleich++;
                            }
                            Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                        }
                    }
                }
            }

            Ende = 0;
            break;

        case 3: //printf("%i", compareLocation(calendar[2],calendar[3]));
            quicksort( &calendar, countAppointments, compareLocation, swapAppointment );

            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                endGleich = Gleich +1;
                if((endGleich<countAppointments) && (compareLocation( *(calendar+Gleich), *(calendar+endGleich )) == 0))
                {
                    while((endGleich<countAppointments) && (compareLocation( *(calendar+Gleich), *(calendar+endGleich ) ) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareDate, swapAppointment);
                    endGleich = Gleich +1;
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
                    }
                }
            }

            Ende = 0;
            break;


        case 4:
            //printf("  %i", compareDuration(calendar[0],calendar[1]));
            quicksort(&(calendar), countAppointments, compareDate, swapAppointment );
            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                if((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + Gleich + endGleich) == 0))
                {
                    while((endGleich<countAppointments) && (compareEquality(calendar + Gleich, calendar + Gleich + endGleich) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                }
            }
            quicksort(&calendar, countAppointments, compareDuration, swapAppointment );
            /* stürzt hiernach beim abspeichern ab
            for(Gleich = 0; Gleich < countAppointments; Gleich++)
            {
                endGleich = Gleich +1;
                if((endGleich<countAppointments) && (compareDuration( *(calendar+Gleich), *(calendar+endGleich) ) == 0))
                {
                    while((endGleich<countAppointments) && (compareDuration( *(calendar+Gleich), *(calendar+endGleich ) ) == 0))
                    {
                        endGleich++;
                    }
                    Qsort(&(calendar), Gleich, endGleich, compareDate, swapAppointment);
                    endGleich = Gleich +1;
                    for(; Gleich <= endGleich; Gleich++)
                    {
                        if((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich) )== 0))
                        {
                            while((endGleich<countAppointments) && (compareEquality( (calendar + Gleich), (calendar + endGleich)) == 0))
                            {
                                endGleich++;
                            }
                            Qsort(&(calendar), Gleich, endGleich, compareTime, swapAppointment);
                        }
                    }
                }
            }
            //
            Ende = 0;
            break;

        case 5:
            Ende = 0;
            break;
        }
        FORECOLOR_WHITE;
    }
    while (Ende);
    //waitForEnter();
           */
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
        ATTRIBUTE_OFF;
        printDate( Appointment);
        printf(":\n");
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
    int i = 0;
    int WithDate = 1;
    TAppointment *temp = First;


    char *Titel = "Liste der Termine";
    printf("\n%s\n", Titel);
    printLine('=', (strlen(Titel)-2)); //Umbruch muss abgezogen werden
    printf("\n");

    if(First != NULL)
    {
        //Ausgabe für Termin mit gleichem Datum
        while(temp != Last->Next)
        {
            listAppointment(temp, WithDate);
            i++;
            if (temp->Next != NULL)
                WithDate = (compareEquality(temp, temp->Next) != 0);

            if(i!= 0 && (i %15) == 0)
                waitForEnter();

            temp = temp->Next;
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
    TAppointment *temp = First;

    while(temp->Next != NULL)
    {
        free(temp);
        /*
            temp->Beschreibung = NULL;
            temp->DateOfAppointment.Day = NULL;
            temp->DateOfAppointment.Month = NULL;
            temp->DateOfAppointment.Year = NULL;
            temp->Location = NULL;
            temp->TimeOfAppointment.Hour = NULL;
            temp->TimeOfAppointment.Minute = NULL;
            temp->TimeOfAppointment.Second = NULL;
            temp->Duration = NULL;
        */
        temp = temp->Next;
    }
}

//  --------------------------------------------------------------------------------
void freeAppointment();
