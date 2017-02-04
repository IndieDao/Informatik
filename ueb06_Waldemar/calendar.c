#include "calendar.h"
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "menu.h"
#include "timedate.h"
#include "escapesequenzen.h"
#include "datastructure.h"
#include "database.h"
#include "sort.h"
#include "list.h"

int countAppointments = 0;

TAppointment * First = NULL;
TAppointment * Last = NULL;


void copyAppointment(TAppointment* newListMember, TAppointment * oldMember)
{
    newListMember->appDate.weekDay = oldMember->appDate.weekDay;
    newListMember->appDate.Day     = (*oldMember).appDate.Day;
    newListMember->appDate.Month   = (*oldMember).appDate.Month;
    newListMember->appDate.Year    = (*oldMember).appDate.Year;
    newListMember->appTime.Hour    = (*oldMember).appTime.Hour;
    newListMember->appTime.Minute  = (*oldMember).appTime.Minute;
    newListMember->appTime.Second  = (*oldMember).appTime.Second;
    newListMember->appPlace        = oldMember->appPlace;
    newListMember->appTitle        = (*oldMember).appTitle;
    newListMember->appDuration     = (*oldMember).appDuration;


}


void exchange (TAppointment * a, TAppointment * b)
{
    TAppointment tmp = *a;
    *a = *b;
    *b = tmp;
}


int cmpDate(const void * a, const void * b )
{
    TAppointment *aa = (TAppointment*)a;
    TAppointment *bb = (TAppointment*)b;
    int difDate = ((aa->appDate.Year - bb->appDate.Year) *10000) + ((aa->appDate.Month - bb->appDate.Month)*100) + ((aa->appDate.Day - bb->appDate.Day));
    int difTime = ((aa->appTime.Hour - bb->appTime.Hour) *10000) + ((aa->appTime.Minute - bb->appTime.Minute)*100) + (aa->appTime.Second - bb->appTime.Second);
    if ( difDate )
        return difDate;
    else
        return difTime;
}


int cmpTitle(const void * a, const void * b )
{
    TAppointment *aa = (TAppointment*)a;
    TAppointment *bb = (TAppointment*)b;
    return strcmp(aa->appTitle, bb->appTitle);
}

int cmpPlace( const void * a, const void * b )
{
    TAppointment * aa = (TAppointment*)a;
    TAppointment * bb = (TAppointment*)b;

    if( bb->appPlace && aa->appPlace )
        return strcmp(aa->appPlace, bb->appPlace);

    else if( !aa->appPlace && bb->appPlace )
        return -1;
    else if( aa->appPlace && !bb->appPlace )
        return 1;
    else
        return 0;
}

int cmpDuration( const void * a, const void * b )
{
    TAppointment * aa = (TAppointment*)a;
    TAppointment * bb = (TAppointment*)b;
    if( bb->appDuration && aa->appDuration)
        return ((aa->appDuration->Hour - bb->appDuration->Hour)*100) + (aa->appDuration->Minute - bb->appDuration->Minute);

    else if( !aa->appDuration && bb->appDuration )
        return -1;
    else if( aa->appDuration && !bb->appDuration )
        return 1;
    else
        return 0;
}

void freeAppointment( TAppointment * tmpApointment )
{
    free( tmpApointment->appTitle );

    if( tmpApointment->appPlace )
        free( tmpApointment->appPlace );

    if( tmpApointment->appDuration )
        free( tmpApointment->appDuration );

    free(tmpApointment);
}


void printAppointment(TAppointment * appStruct, int trueDate)
{
    int i = 0;
    char *tmpTittle = appStruct->appTitle;

    if(trueDate)
    {
        printf("\n");
        printLine('=', 78);
        printDate(appStruct->appDate);
    }
    printf("   ");
    printTime(appStruct->appTime, appStruct->appDuration);

    if( appStruct->appPlace )
    {
        printf("%s", appStruct->appPlace);
        for(i = 0; i < 15 - strlen(appStruct->appPlace); i++)
            printf(" ");

        printf(" | ");
    }
    else
        printf("                | ");

    if(strlen(tmpTittle) <= 40)
        printf("%s\n", tmpTittle);
    else
    {
        for(i = 0; i < 36; i++)
            printf("%c", *(tmpTittle+i));
        printf(" ...\n");
    }
}


void createAppointment()
{
    char * headline = "Erfassung eines neuen Termins";
    int valid = 0;
    TAppointment tmpApp;
    tmpApp.appDuration = NULL;
    tmpApp.appPlace = NULL;

    clearScreen();
    printf("%s\n", headline);
    printLine('=', strlen(headline));

    do
    {
        POSITION(4,1);
        valid = getDate("Datum        : ", &tmpApp.appDate);
        if(!valid)
        {
            POSITION(4,1);
            CLEAR_LINE;
            POSITION(4,30);
            printf("Das Datum ist ungueltig.");
        }
        else
        {
            POSITION(4,30);
            CLEAR_LINE;
        }
    }while(!valid);

    do
    {
        POSITION(5,1);
        valid = getTime("Uhrzeit      : ", &tmpApp.appTime, 0);

        if(!valid)
        {
            POSITION(5,1);
            CLEAR_LINE;
            POSITION(5,30);
            printf("Die Uhrzeit ist ungueltig.");
        }
        else
        {
            POSITION(5,30);
            CLEAR_LINE;
        }
    }while(!valid);

    POSITION(6,1);
    getText("Beschreibung : ", 100, &tmpApp.appTitle, 0);

    POSITION(7,1);
    getText("Ort          : ", 15, &tmpApp.appPlace, 1);

    tmpApp.appDuration = calloc(1, sizeof(TTime));
    if(tmpApp.appDuration == NULL)
    {
        perror("Speicherplatz konnte nicht bereitgestellt werden.\n");
        return;
    }

    do
    {
        POSITION(8,1);
        valid = getTime("Dauer        : ", tmpApp.appDuration, 1);

        if(!valid)
        {
            POSITION(8,1);
            CLEAR_LINE;
            POSITION(8,30);
            printf("Die Uhrzeit ist ungueltig.");
        }
        else
        {
            POSITION(8,30);
            CLEAR_LINE;
        }
    }while(!valid);

    TAppointment * newApp = calloc(1, sizeof(TAppointment));
    if( !newApp )
    {
        perror("Termin konnte nicht geladen werden. Celloc error.");
        return;
    }
    newApp->appDate.weekDay = tmpApp.appDate.weekDay;
    newApp->appDate.Day     = tmpApp.appDate.Day;
    newApp->appDate.Month   = tmpApp.appDate.Month;
    newApp->appDate.Year    = tmpApp.appDate.Year;
    newApp->appTime.Hour    = tmpApp.appTime.Hour;
    newApp->appTime.Minute  = tmpApp.appTime.Minute;
    newApp->appTime.Second  = tmpApp.appTime.Second;
    newApp->appPlace        = tmpApp.appPlace;
    newApp->appTitle        = tmpApp.appTitle;
    newApp->appDuration     = tmpApp.appDuration;

    insertInDList(newApp, cmpDate);

    printf("\n\nTermin wurde gespeichert.\n");
    countAppointments++;
}


void editAppointment()
{
    printf("Termin bearbeiten.\n");
}


void deleteAppointment()
{
    TAppointment * tmp = First;
    TAppointment * rem = NULL;
    TAppointment * pPermu[countAppointments];

    char * tmpday[] = {"NotADay", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    int Index     = 0,
        breakloop = 0,
        i         = 0,
        j         = 0,
        y         = 1,
        Valid     = 0;

    clearScreen();
    if( !tmp )
    {
        printf("Der Kalender ist leer.\n");
        waitForEnter();
        return;
    }

    printf("Liste der Termine: \n");
    printf("==================\n\n");

    while( tmp )
    {
        if(breakloop == 25)
        {
            printf("\nDer darstellbare Bereich wurde ausgegeben. Fuer den naechsten Bereich...\n");
            waitForEnter();
            clearScreen();
            breakloop = 0;
            y = 1;
        }
        printf("%d: %s, %02d.%02d.%04d, ", i+1, tmpday[tmp->appDate.weekDay], tmp->appDate.Day, tmp->appDate.Month, tmp->appDate.Year);
        if( strlen(tmp->appTitle) > 52)
        {
            printf("%02d:%02d: ", tmp->appTime.Hour, tmp->appTime.Minute);
            for(j = 0; j < 48; j++)
                printf("%c", tmp->appTitle[j]);
            printf(" ...\n");
        }
        else
            printf("%02d:%02d: %s\n", tmp->appTime.Hour, tmp->appTime.Minute, tmp->appTitle);
        y++;
        breakloop++;
        pPermu[i] = tmp;
        i++;
        tmp = tmp->Next;
    }

    printf("\nWelchen Termin moechten Sie loeschen (0 fuer Abbrechen) ?   ");
    y += 4;
    do
    {
        POSITION(y, (int)strlen("Welchen Termin moechten Sie loeschen (0 fuer Abbrechen) ?   "));
        CLEAR_LINE;
        Valid = scanf("%i", &Index);
        clearBuffer();

    }while(!Valid || Index > countAppointments || Index < 0);

    if( Index == 0)
        return;
    else
    {
        rem = removeFromDList(pPermu[Index-1], cmpDate);
        freeAppointment(rem);
        printf("\nTermin wurde geloescht.\n\n");
        countAppointments--;
        waitForEnter();
    }

}


void searchAppointment()
{
    printf("Termin suchen.\n");
}


void sortCalendar()
{
    const char *MenuTitle = "Termine sortieren";

	const char *sortMenu[] = {
                                "1. Sortieren nach Datum und Uhrzeit",
                                "2. Sortieren nach Beschreibung",
                                "3. Sortieren nach Ort",
                                "4. Sortieren nach Dauer",
                                "5. Zurueck zum Hauptmenue"
                            };
    int Input      = 0,
        backToMain = 0,
        sortDate   = 0,
        sortTitle  = 0,
        sortPlace  = 0,
        sortDur    = 0;
    TAppointment * tmp = First;
    TAppointment * rem = NULL;

	do
	{
		Input = getMenu(MenuTitle, sortMenu, 5);

		switch( Input )
		{
            case 1:  sortDate = 1; 	    break;
            case 2:  sortTitle = 1;     break;
            case 3:  sortPlace = 1;  break;
            case 4:  sortDur   = 1;     break;
            case 5:  backToMain = 1;     break;
		}

       if( !backToMain && Input < 6 )
       {

            if(sortDate == 1)
            {
                while(tmp)
                {
                    TAppointment * newListMember = calloc(1, sizeof(TAppointment));
                    if(!newListMember)
                    {
                        perror("Speicher konnte nicht reserviert werden <sortList>.");
                        return;
                    }
                    *newListMember = *tmp;
                    rem = removeFromDList(tmp, cmpTitle);
                    freeAppointment(rem);
                    insertInDList(newListMember, cmpDate);
                    tmp = tmp->Next;
                }
            }
            if(sortTitle == 1)
            {
                while(tmp)
                {
                    TAppointment *newListMember = calloc(1, sizeof(TAppointment));
                    if(!newListMember)
                    {
                        perror("Speicher konnte nicht reserviert werden <sortList>.");
                        return;
                    }
                    copyAppointment(newListMember, tmp);
                    rem = removeFromDList(tmp, cmpTitle);
                    freeAppointment(rem);
                    insertInDList(newListMember, cmpTitle);
                    tmp = tmp->Next;
                }
            }
            if(sortPlace == 1)
            {
                while(tmp)
                {
                    TAppointment *newListMember = calloc(1, sizeof(TAppointment));
                    if(!newListMember)
                    {
                        perror("Speicher konnte nicht reserviert werden <sortList>.");
                        return;
                    }
                    *newListMember = *tmp;
                    rem = removeFromDList(tmp, cmpTitle);
                    freeAppointment(rem);
                    insertInDList(newListMember, cmpPlace);
                    tmp = tmp->Next;
                }
            }
            if(sortDur == 1)
            {
                while(tmp)
                {
                    TAppointment *newListMember = calloc(1, sizeof(TAppointment));
                    if(!newListMember)
                    {
                        perror("Speicher konnte nicht reserviert werden <sortList>.");
                        return;
                    }
                    *newListMember = *tmp;
                    rem = removeFromDList(tmp, cmpTitle);
                    freeAppointment(rem);
                    insertInDList(newListMember, cmpDuration);
                    tmp = tmp->Next;
                }
            }
            printf("\nWurde sortiert.\n");
            waitForEnter();
       }


	} while ( !backToMain );

}


void listCalendar()
{
    TAppointment * tmpApp = First;
    char * headline = "Liste der Termine";
    char tmpDate[11];
    char tmpDate1[11];
    int breakloop = 0;

    if ( countAppointments == 0)
    {
        printf("Kalender ist leer.\n");
        return;
    }
    sprintf(tmpDate, "%02d.%02d.%04d",0 , 0, 0);

    clearScreen();
    printf("%s\n", headline);
    printLine('=', strlen(headline));

    while( tmpApp != NULL )
    {
        if(breakloop == 15)
        {
            printf("\nDer darstellbare Bereich wurde ausgegeben. Fuer den naechsten Bereich...\n");
            waitForEnter();
            breakloop = 0;
        }
        sprintf(tmpDate1, "%02d.%02d.%04d",tmpApp->appDate.Day, tmpApp->appDate.Month, tmpApp->appDate.Year);
        printAppointment(tmpApp, strcmp(tmpDate1, tmpDate));
        sprintf(tmpDate, "%02d.%02d.%04d",tmpApp->appDate.Day, tmpApp->appDate.Month, tmpApp->appDate.Year);
        breakloop ++;
        tmpApp = tmpApp->Next;
    }
}


void freeCalender()
{
    TAppointment * tmpApp = First;

    while( tmpApp!= NULL)
    {
        tmpApp = removeFromDList(First, cmpTitle);

        if (tmpApp)
            freeAppointment(tmpApp);
    }
}
