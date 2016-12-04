//
//  calendar.c
//  a1
//
//  Created by BD on 23.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#include <stdio.h>
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"
#include <stdlib.h>
#include <string.h>

TAppointment calender[MAXAPPOINTMENTS];
int countAppointment = 0;

int compareDate(TAppointment *App1, TAppointment *App2)
{
    int Erg = App1->Datum.Year - App2->Datum.Year;
    
    if (Erg == 0)
    {
        Erg = App1->Datum.Month - App2->Datum.Month;
        
        if (Erg == 0)
            Erg = App1->Datum.Day - App2->Datum.Day;
    }
    return Erg;
}

void createAppointment()
{
    
    TTime Dauer;
   
    printf("Neuen Termin anlegen\n");
    printLine('=', (unsigned)strlen("Neuen Termin anlegen"));
    printf("\n");
    
    getDate("Datum", &(calender[countAppointment].Datum) );
    getTime("Uhrzeit", &(calender[countAppointment].Uhrzeit) );
    getText("Beschreibung", 100, &(calender[countAppointment].Beschreibung), 1);
    getText("Ort", 15, &(calender[countAppointment].Ort), 1);

    getTime("Dauer", &Dauer );
    calender[countAppointment].Termindauer = calloc(1, sizeof(TTime)); // weil Termindauer ein Zeiger ist im Datenstructur ist
    
    if( calender[countAppointment].Termindauer) // wurde der Speicher reserviert??
        *(calender[countAppointment].Termindauer) = Dauer;
    
    printf("%i.Termin wurde gespeichert!\n", countAppointment);
    countAppointment++;
  
    
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

void listAppointment(TAppointment *App, int WithDate)
{
    int j;
    
    if (WithDate)
    {
        printLine('=', 78);
        printDate( App );
        printLine('_', 15);
    }
    printTime( App );
    printf("%15s     |", App->Ort);
    
    
    int len_Beschreibung =  (unsigned) strlen(App->Beschreibung);
    
    if(len_Beschreibung <= 48)
        printf(" %s\n", App->Beschreibung);
    
    else if( len_Beschreibung > 48)
    {
        for(j = 0; j < 44; j++)
            printf("%c", (App->Beschreibung)[j]);
        
        printf(" ...\n");
    }
    
}

void listCalendar()
{
    int i;
    int WithDate = 1;
    
    printf("\nListe der Termine\n");
    printLine('=', (unsigned)strlen("Liste der Termine"));
    printf("\n");
    
    //Ausgabe für Termine mit gleichen Datum
    for( i = 0 ; i < countAppointment; i++)
    {
        listAppointment(calender + i, WithDate);
        if (i < countAppointment - 1)
            WithDate = (compareDate(calender + i, calender + i + 1) != 0);
        
    }
    
    if(countAppointment == 15)
        waitForEnter();
    
    waitForEnter();
    
}


void freeAppointment(TAppointment * calendar)
{
    int i = 0;
    
    for(i = 0; i < countAppointment; i++)
        free(&calendar[i]);
    
}

















