#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"

#define PUNKT '.'
#define DOPPELPUNKT ':'

static char tmp[7];

static int i = 0;

void tmpToken(char *Eingabe, char Token)
{
    int z = 0;

    while ( (*(Eingabe + i) != Token) && (*(Eingabe + i) != '\0') )
    {
        tmp[z] = Eingabe[i];
        z++;
        i++;
    }
    tmp[z] = '\0';
}

//trennt die Eingegebene Zeichenkette bei den ":", und schreibt den Zwischenstring in die angelegte Datumsstruktur
int getDateFromString(char *Eingabe, TDate *Datum)
{
    i = 0;
//    char **Pos = &Eingabe;

    tmpToken(Eingabe, PUNKT);
    i++;
    Datum->Day     = atoi(tmp);
    tmpToken(Eingabe, PUNKT);
    i++;
    Datum->Month   = atoi(tmp);
    tmpToken(Eingabe, PUNKT);
    i++;
    Datum->Year    = atoi(tmp);

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

//trennt die Eingegebene Zeichenkette bei den ":", und schreibt den Zwischenstring in die angelegte Zeitstruktur
int getTimeFromString(char *Eingabe, TTime *Zeit)
{
    i = 0; //zurücksetzen auf erste Stelle der Eingabe

    tmpToken(Eingabe, DOPPELPUNKT);
    i++;
    Zeit->Hour     = atoi(tmp);
    tmpToken(Eingabe, DOPPELPUNKT);
    i++;
    Zeit->Minute   = atoi(tmp);
    tmpToken(Eingabe, DOPPELPUNKT);
    i++;
    Zeit->Second    = atoi(tmp);

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

//gibt bei korrekter Zeitangabe "true" zurück, ansonsten false
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde)
{
    int Erg = 0;
    if(Sekunde < 60 && Minute < 60 && Stunde < 24)
    {
       Erg = 1;
    }
    return Erg;
};

//gibt bei Schaltjahr "true" zurück, ansonsten false
int isLeapYear(int Jahr)
{

 if (((Jahr % 100) != 0 && (Jahr % 4) == 0) || (Jahr % 400) == 0)
    return 1;
 else
    return 0;
};

//gibt bei korrektem Datum "true" zurück, ansonsten false
int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr)
{
    int Erg = 1;
    int TageImMonat[12] = {  31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(Jahr))
    {
            TageImMonat[1] = 29;
    }
    else
    {
            TageImMonat[1] = 28;
    }

    if ((Monat < 1) || (Monat > 12))
    {
        Erg = 0;
    }
    if ((Tag <= 0) || (Tag > TageImMonat[Monat-1]))
    {
        Erg = 0;
    }
    return Erg;
};
