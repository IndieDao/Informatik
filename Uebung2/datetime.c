#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"

#define PUNKT '.'
#define DOPPELPUNKT ':'

static char tmp[7];

static int i = 0;
//  --------------------------------------------------------------------------------
//  schreibt Teilstring (Token) bis zum Delimiter in den Zwischenstring tmp
//  und setzt die Zählvariable i auf den Wert, des nächsten Werts im Eingabestring
//  --------------------------------------------------------------------------------
char *tmpToken(char *Eingabe, char Token)
{
    int z = 0;

    while ( (*(Eingabe + i) != Token) && (*(Eingabe + i) != '\0') )
    {
        tmp[z] = Eingabe[i];
        z++;
        i++;
    }
    tmp[z] = '\0';
    i++;
    return tmp;
}

//  --------------------------------------------------------------------------------
//  schreibt die Tokens aus tmpToken() in Datumszeiger und setzt von dort aus Zeiger
//  in die angelegte Datumsstruktur
//  --------------------------------------------------------------------------------
int getDateFromString(char *Eingabe, TDate *Datum)
{
    i = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pTag;
    char *pMonth;
    char *pJahr;
    //
    pTag = tmpToken(Eingabe, PUNKT);
    Datum->Day     =    atoi(pTag);

    pMonth = tmpToken(Eingabe, PUNKT);
    Datum->Month   =    atoi(pMonth);

    pJahr = tmpToken(Eingabe, PUNKT);
    Datum->Year    =    atoi(pJahr);

    //ruft Pruefungs-Unterfunktion auf
    if (isDateValid(Datum->Day, Datum->Month, Datum->Year))
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//  --------------------------------------------------------------------------------
//  schreibt die Tokens aus tmpToken() in Zeitzeiger und setzt von dort aus Zeiger
//  in die angelegte Zeitstruktur
//  --------------------------------------------------------------------------------
int getTimeFromString(char *Eingabe, TTime *Zeit)
{
    i = 0; //zurücksetzen auf erste Stelle von (der) Eingabe
    char *pStd;
    char *pMin;
    char *pSec;


    tmpToken(Eingabe, DOPPELPUNKT);
    pStd = tmp;
    Zeit->Hour     = atoi(pStd);

    tmpToken(Eingabe, DOPPELPUNKT);
    pMin = tmp;
    Zeit->Minute   = atoi(pMin);

    tmpToken(Eingabe, DOPPELPUNKT);
    pSec = tmp;
    Zeit->Second    = atoi(pSec);

    //ruft Pruefungs-Unterfunktion auf
    if (isTimeValid(Zeit->Hour, Zeit->Minute, Zeit->Second))
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
//  --------------------------------------------------------------------------------
//  gibt bei korrekter Zeitangabe "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde)
{
    int Erg = 0;
    if(Sekunde < 60 && Minute < 60 && Stunde < 24)
    {
       Erg = 1;
    }
    return Erg;
};

//  --------------------------------------------------------------------------------
//  gibt bei Schaltjahr "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isLeapYear(int Jahr)
{

 if (((Jahr % 100) != 0 && (Jahr % 4) == 0) || (Jahr % 400) == 0)
    return 1;
 else
    return 0;
};
//  --------------------------------------------------------------------------------
//  gibt bei korrektem Datum "true" zurück, ansonsten false
//  --------------------------------------------------------------------------------
int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr)
{
    int Erg = 1;
    int TageImMonat[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(Jahr))
    {
        TageImMonat[2] = 29;
    }else{
        TageImMonat[2] = 28;
    }

    if (((Monat < 1) || (Monat > 12)) || (Tag <= 0) || (Tag > TageImMonat[Monat]))
    {
        Erg = TageImMonat[0];
    }
    return Erg;
};
