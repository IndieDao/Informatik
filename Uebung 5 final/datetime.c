#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "escapesequenzen.h"
//#include <string.h>

#define PUNKT '.'
#define DOPPELPUNKT ':'

/*************************************************************************
*   Die Funktionen in diesem Modul ermöglichen die korrekte Ein- und Ausgabe
*   der Zeit, dem Datum, sowie der Dauer von Kalendereinträgen.
*************************************************************************/

extern TAppointment calendar[MAX_APPOINTEMENTS];    //fester Kalender der Software
extern int countAppointments;                       //zählt Einträge
static char Input[11];
extern int q;

//  --------------------------------------------------------------------------------
/** \brief  schreibt die Tokens aus tmpToken() in Datumszeiger und setzt von dort aus Zeiger in die angelegte Datumsstruktur
 *          Prüft in Unterprogramm Validität der Eingabe.
 *
 * \param Eingabe char*
 * \param Datum TDate*
 * \return int
 *
 */
//  ------------------------------- -------------------------------------------------
int getDateFromString(char *Eingabe, TDate *Datum)
{
    q = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pDay;
    char *pMonth;
    char *pYear;

    int calcWithYear;
    if(*Eingabe)
    {
    pDay = tmpToken(Eingabe, PUNKT);
    Datum->Day      = atoi(pDay);
    pMonth = tmpToken(Eingabe, PUNKT);
    Datum->Month      = atoi(pMonth);
    pYear = tmpToken(Eingabe, PUNKT);
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
/** \brief  schreibt die Tokens aus tmpToken() in Zeitzeiger und setzt von dort aus Zeiger
 *          in die angelegte Zeitstruktur
 *          Prüft in Unterprogramm Validität der Eingabe.
 *
 * \param Eingabe char*
 * \param Zeit TTime*
 * \return int
 *
 */
//  --------------------------------------------------------------------------------
int getTimeFromString(char *Eingabe, TTime *Zeit)
{
    q = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pHour;
    char *pMinute;
    char *pSecond;

    if(Eingabe)
    {
    pHour = tmpToken(Eingabe, DOPPELPUNKT);
        if(atoi(pHour))                                                      // Sekunden sind optional
        {
            Zeit->Hour      = atoi(pHour);
        }
        else
            Zeit->Hour= 0;

    pMinute = tmpToken(Eingabe, DOPPELPUNKT);
        if(atoi(pMinute))                                                      // Sekunden sind optional
        {
            Zeit->Minute      = atoi(pMinute);
        }
        else
            Zeit->Minute = 0;

    pSecond = tmpToken(Eingabe, DOPPELPUNKT);
        if(atoi(pSecond))                                                      // Sekunden sind optional
        {
            Zeit->Second      = atoi(pSecond);
        }
    else
    Zeit->Second = 0;

    if (isTimeValid(Zeit->Second, Zeit->Minute, Zeit->Hour))           //ruft Pruefungs-Unterfunktion auf
        return 1;
    }

return 0;
}

//  --------------------------------------------------------------------------------
/** \brief gibt bei korrekter Zeitangabe "true" zurück, ansonsten false
 *
 * \param Sekunde unsigned int
 * \param Minute unsigned int
 * \param Stunde unsigned int
 * \return int       Ergebnis
 *
 */
//  --------------------------------------------------------------------------------
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde)
{
    int Erg = 0;
    if(Sekunde < 60 && Minute < 60 && Stunde < 24)
       Erg = 1;

    return Erg;
}

//  --------------------------------------------------------------------------------
/** \brief gibt bei Schaltjahr "true" zurück, ansonsten false
 *
 * \param Jahr int
 * \return int
 *
 */
//  --------------------------------------------------------------------------------
int isLeapYear(int Jahr)
{
    int Erg = 0;
 if (((Jahr % 100) != 0 && (Jahr % 4) == 0) || (Jahr % 400) == 0)
    Erg = 1;

return Erg;
}

//  --------------------------------------------------------------------------------
/** \brief gibt bei korrektem Datum "true" zurück, ansonsten false
 *
 * \param Tag unsigned int
 * \param Monat unsigned int
 * \param Jahr int
 * \return int
 *
 */
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
/** \brief  prüft Benutzereingabe eines Datum über Input und schreibt bei Validität die
 *          Daten via der Funktion getDateFromString in ein TDate Konstrukt
 *
 * \param Titel char*           Ausgabe eines Titeltext
 * \param Date TDate*
 * \return int
 *
 */
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
    //else return 1;
    return 0;
}

//  --------------------------------------------------------------------------------
/** \brief  prüft Benutzereingabe einer Uhrzeit über Input und schreibt bei Validität die
 *          Daten via der Funktion getTimeFromString in ein TTime Konstrukt
 *
 * \param Titel char*
 * \param Time TTime*
 * \return int
 *
 */
//  --------------------------------------------------------------------------------
int getTime(char *Titel, TTime *Time)
{
    *Input = '\0';
    int Erg = 0;
//  Prüft, ob nach der Dauer des Termins gefragt wurde
/*    if(*Titel == 'D')
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
*/
        CLEAR_LINE;
        printf("%s ", Titel);
        scanf("%10[^\n qwertzuiopü+*asdfghjklöä#'<>yxcvbnm,._;MNBVCXYÄÖLKJHGFDSAÜPOIUZTREWQ!""§$%&/()=?`'@€~]", Input);
        clearBuffer();

        if(!getTimeFromString(Input, Time))     //rekursiver Aufruf, falls Eingabe nicht valide
        {
            UP(1);
            getTime(Titel, Time);
        }
//    }
    return Erg;
}

//  --------------------------------------------------------------------------------
/** \brief  Gibt Datum eines Termins in Konsole aus und ruft Unterprogramm für weitere Daten
 *
 * \param cal TAppointment*
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void printDate(TAppointment *cal)
{
    int i=0;
    char *Wochentag;

    switch (cal->DateOfAppointment.DayOfTheWeek)
    {
        case 1:  Wochentag = "Mo";            break;
        case 2:  Wochentag = "Di";            break;
        case 3:  Wochentag = "Mi";            break;
        case 4:  Wochentag = "Do";            break;
        case 5:  Wochentag = "Fr";            break;
        case 6:  Wochentag = "Sa";            break;
        case 7:  Wochentag = "So";            break;
        default: Wochentag = "Not a Day";     break;
    }

    printf("%s, %02i.%02i.%04i:\n", Wochentag, cal->DateOfAppointment.Day, cal->DateOfAppointment.Month, cal->DateOfAppointment.Year);
i++;
}

//  --------------------------------------------------------------------------------
/** \brief Gibt Zeit und Dauer eines Termins auf der Konsole aus
 *
 * \param calendar TAppointment*
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void printTime(TAppointment *calendar)
{
//printf("%02i:%02i\n", calendar->Duration->Hour, calendar->Duration->Minute);

if((calendar->Duration->Hour + calendar->Duration->Minute))
{
    TTime endTime = addDuration(calendar);
    printf("%02i:%02i - %02i:%02i ->", calendar->TimeOfAppointment.Hour, calendar->TimeOfAppointment.Minute, endTime.Hour, endTime.Minute);
}
   else
    printf("%02i:%02i         ->", calendar->TimeOfAppointment.Hour, calendar->TimeOfAppointment.Minute);
}

//  --------------------------------------------------------------------------------
/** \brief  errechnet Endzeit eines Termins aus der Angabe von Dauer
 *
 * \param calendar TAppointment*
 * \return TTime
 *
 */
//  --------------------------------------------------------------------------------
TTime addDuration(TAppointment *calendar)
{
    TTime endTime;
    int pSecond;
    int pMinute;
    int pHour;

    pSecond = (*calendar).Duration->Second + calendar->TimeOfAppointment.Second;
    pMinute = (*calendar).Duration->Minute + calendar->TimeOfAppointment.Minute;
    pHour = (*calendar).Duration->Hour + calendar->TimeOfAppointment.Hour;

    if (pSecond >=60)
    {
        pSecond = pSecond-60;
        pMinute++;
    }
    if (pMinute >=60)
    {
        pMinute = pMinute-60;
        pHour++;
    }
        if (pHour >=24)
    {
        pHour = pHour-24;
    }
    endTime.Hour = pHour;
    endTime.Minute = pMinute;
    endTime.Second = pSecond;
    return endTime;
}

/*
void printDate(TAppointment *cal)
{
    char *Wochentag;
    int i=0;
    k = 1;
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
        if((k%15) == 0)
        {
            waitForEnter();
        }
        printf("%i", k);
        printf("\n");
        printLine('=', 78);
        printf("%s, %i.%i.%i:\n", Wochentag, cal->DateOfAppointment.Day, cal->DateOfAppointment.Month, cal->DateOfAppointment.Year);
        printLine('_', 15);
        printf("\n");
        printTime(cal);
        for (;i<k ;i++)
        {
            printf("%i,%i  ", i, k);
            cal++;
        }

    }
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

    while(  k <= (countAppointments)
     && (pDay == cal->DateOfAppointment.Day)
     && (pMonth == cal->DateOfAppointment.Month)
     && (pYear == cal->DateOfAppointment.Year))
    {
        if((k%15) == 0)
            {
            waitForEnter();
            }
        printf("%02i:%02i -> %s", cal->TimeOfAppointment.Hour, cal->TimeOfAppointment.Minute, cal->Location);
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
*/
