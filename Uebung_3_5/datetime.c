#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "escapesequenzen.h"
#include <string.h>

#define PUNKT '.'
#define DOPPELPUNKT ':'

/*************************************************************************
*   Die Funktionen in diesem Modul ermöglichen die korrekte Ein- und Ausgabe
*   der Zeit, dem Datum, sowie der Dauer von Kalendereinträgen.
*************************************************************************/

extern TAppointment calendar[MAX_APPOINTEMENTS];    //fester Kalender der Software
extern int countAppointments;                       //zählt Einträge
static char Input[11];
//static char tmp[7];
static int q = 0;
static int k = 1;

//  --------------------------------------------------------------------------------
//  schreibt die Tokens aus tmpToken() in Datumszeiger und setzt von dort aus Zeiger
//  in die angelegte Datumsstruktur
//  Prüft in Unterprogramm Validität der Eingabe.
//  --------------------------------------------------------------------------------
int getDateFromString(char *Eingabe, TDate *Datum)
{
    q = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pDay;
    char *pMonth;
    char *pYear;
    int calcWithYear;
    if(*Eingabe)
    {
    pDay    = tmpToken(Eingabe, PUNKT);
    Datum->Day      = atoi(pDay);
    pMonth  = tmpToken(Eingabe, PUNKT);
    Datum->Month      = atoi(pMonth);
    pYear   = tmpToken(Eingabe, PUNKT);
    Datum->Year      = atoi(pYear);

    calcWithYear = Datum->Year;                                                                            // ab hier Berechnung des Wochentages
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    calcWithYear -= Datum->Month < 3;
    int W = ( calcWithYear + calcWithYear/4 - calcWithYear/100 + calcWithYear/400 + t[Datum->Month-1] + Datum->Day) % 7;  // W = Tag der Woche
    if (W == 0)    W = 7;
    Datum->DayOfTheWeek = (TDayOfTheWeek)W;

    if (isDateValid(Datum->Day, Datum->Month, Datum->Year))                 //ruft Pruefungs-Unterfunktion auf
        return 1;
    }
    return 0;
}

//  --------------------------------------------------------------------------------
//  schreibt die Tokens aus tmpToken() in Zeitzeiger und setzt von dort aus Zeiger
//  in die angelegte Zeitstruktur
//  Prüft in Unterprogramm Validität der Eingabe.
//  --------------------------------------------------------------------------------
int getTimeFromString(char *Eingabe, TTime *Zeit)
{
    q = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pHour;
    char *pMinute;
    char *pSecond;
    //Zeit->Second      = 0;
    if(Eingabe)
    {
    pHour       = tmpToken(Eingabe, DOPPELPUNKT);
    Zeit->Hour      = atoi(pHour);
    pMinute     = tmpToken(Eingabe, DOPPELPUNKT);
    Zeit->Minute    = atoi(pMinute);
    pSecond     = tmpToken(Eingabe, DOPPELPUNKT);
    if((atoi(pSecond)>0))                                                      // Sekunden sind optional
    {
        Zeit->Second      = atoi(pSecond);
    }
    if (isTimeValid(Zeit->Second, Zeit->Minute, Zeit->Hour))           //ruft Pruefungs-Unterfunktion auf
        return 1;
    }

return 0;
}

//  --------------------------------------------------------------------------------
//  gibt bei korrekter Zeitangabe "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde)
{
    int Erg = 0;
    if(Sekunde < 60 && Minute < 60 && Stunde < 24)
       Erg = 1;

    return Erg;
}

//  --------------------------------------------------------------------------------
//  gibt bei Schaltjahr "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isLeapYear(int Jahr)
{
    int Erg = 0;
 if (((Jahr % 100) != 0 && (Jahr % 4) == 0) || (Jahr % 400) == 0)
    Erg = 1;

    return Erg;
}
//  --------------------------------------------------------------------------------
//  gibt bei korrektem Datum "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr)
{
    int Erg = 1;
    int TageImMonat[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(Jahr))
        TageImMonat[2] = 29;
    else
        TageImMonat[2] = 28;

    if (((Monat < 1) || (Monat > 12)) || (Tag <= 0) || (Tag > TageImMonat[Monat]))
        Erg = TageImMonat[0];

    return Erg;
}
//  --------------------------------------------------------------------------------
//  prüft Benutzereingabe eines Datum über Input und schreibt bei Validität die
//  Daten via der Funktion getDateFromString in ein TDate Konstrukt
//  --------------------------------------------------------------------------------
int getDate(char *Titel, TDate *Date) // Einbage = Eingabebaufforderung
{
    *Input = '\0';

    CLEAR_LINE;
    printf("%s ", Titel);
    scanf("%10[^\n qwertzuiopü+*asdfghjklöä#'<>yxcvbnm,_:;MNBVCXYÄÖLKJHGFDSAÜPOIUZTREWQ!""§$%&/()=?`'@€~]", Input);
    clearBuffer();

    if(!getDateFromString(Input, Date)) //rekursiver Aufruf, falls Eingabe nicht valide
    {
        UP(1);
        getDate(Titel, Date);
    }
    else return 1;

    return 0;
}
//  --------------------------------------------------------------------------------
//  prüft Benutzereingabe einer Uhrzeit über Input und schreibt bei Validität die
//  Daten via der Funktion getTimeFromString in ein TTime Konstrukt
//  --------------------------------------------------------------------------------
int getTime(char *Titel, TTime *Time)
{
    *Input = '\0';
    int Erg = 0;
//  Prüft, ob nach der Dauer des Termins gefragt wurde
    if(*Titel == 'D')
    {
        TTime *Z = calloc (1, sizeof(TTime)); // Speicher für die Eingabe reservieren
        CLEAR_LINE;
        printf("%s ", Titel);
        scanf("%10[^\n qwertzuiopü+*asdfghjklöä#'<>yxcvbnm,._;MNBVCXYÄÖLKJHGFDSAÜPOIUZTREWQ!""§$%&/()=?`'@€~]", Input);
        clearBuffer();

        if(!getTimeFromString(Input, Z))     //rekursiver Aufruf, falls Eingabe nicht valide
        {
            UP(1);
            getTime(Titel, Time);
        }
        Time = Z;
        free(Z);
    }
    else
    {
// Für alle Zeitaufrufe ausser der Dauer
        CLEAR_LINE;
        printf("%s ", Titel);
        scanf("%10[^\n qwertzuiopü+*asdfghjklöä#'<>yxcvbnm,._;MNBVCXYÄÖLKJHGFDSAÜPOIUZTREWQ!""§$%&/()=?`'@€~]", Input);
        clearBuffer();

        if(!getTimeFromString(Input, Time))     //rekursiver Aufruf, falls Eingabe nicht valide
        {
            UP(1);
            getTime(Titel, Time);
        }
    }
    return Erg;
}

void printDate(TAppointment *cal)
{
char *Wochentag;

    switch (cal->DateOfAppointment.DayOfTheWeek)
    {
        case 1: Wochentag = "Mo";            break;
        case 2: Wochentag = "Di";            break;
        case 3: Wochentag = "Mi";            break;
        case 4: Wochentag = "Do";            break;
        case 5: Wochentag = "Fr";            break;
        case 6: Wochentag = "Sa";            break;
        case 7: Wochentag = "So";            break;
        case 0: Wochentag = "Not a Day";     break;
    }

    while(k <= countAppointments)
    {
    if((k%15) == 0)                                             //stoppt die Terminausgabe alle 15 Einträge
    {
    waitForEnter();
    }
    printf("\n");
    printLine('=', 78);
    printf("%s, %i.%i.%i:\n", Wochentag, cal->DateOfAppointment.Day, cal->DateOfAppointment.Month, cal->DateOfAppointment.Year);
    printLine('_', 15);
    printf("\n");

    printTime(cal);
    *cal = cal[k-1];
    }
    k = 1;
}

void printTime(TAppointment *cal)
{
int g = 0;
int pDay;
int pMonth;
int pYear;
//char *pBeschreibung = calloc((strlen(cal->Beschreibung)), sizeof(char));

    pDay = cal->DateOfAppointment.Day;
    pMonth = cal->DateOfAppointment.Month;
    pYear = cal->DateOfAppointment.Year;

    while(  k <= countAppointments
     && (pDay == cal->DateOfAppointment.Day)
     && (pMonth == cal->DateOfAppointment.Month)
     && (pYear == cal->DateOfAppointment.Year))
    {
        if((k%15) == 0)
            {
            waitForEnter();
            }
        printf("%i:%i -> %s", cal->TimeOfAppointment.Hour, cal->TimeOfAppointment.Minute, cal->Location);
        RIGHT((int)(15 - strlen(cal->Location)));
        if(strlen(cal->Beschreibung)>44)
        {
            printf(" | ");
            for( g = 0; g < 44; g++ )
            {
            printf("%c", *(cal->Beschreibung)++);
            }
            printf(" ...\n");
        }else{
            printf(" | %s\n", cal->Beschreibung );
        }
    k++;
    cal++;
    }
}
