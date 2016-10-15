//
//  datetime.c
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
#include "tools.h"
#include "datastructure.h"
#include "escapesequenzen.h"

/******************************************
                                          *
                                          *
                                          *
*******************************************/
int isLeapYear(int Year) // corriger
{
   int Erg;
    
    if( (Year % 400) == 0)
        Erg = 1; // est ist ein Schaltjahr
    else
        Erg = 0;
    
    if( (Year % 100) == 0)
        Erg = 0;
    
    if( (Year % 4) == 0)
        Erg = 1;
    else
        Erg = 0;
    if( (Year == 1700) || (Year == 1800) || (Year == 1900) || (Year == 2100) ) // alle diese Jahre sind kein schaltjahre obwohl sie durch 4 teilbar sind
        Erg = 0;
    
    return Erg;
}

/******************************************
                                          *
                                          *
                                          *
 ******************************************/
int isDateValid(int Day, int Month, int Year)
{
    int Erg = 0;
    
    if((Day < 1) || (Day > 31) || (Month < 1) || (Month > 12))
       Erg = 0; // es ist kein gültiges Datum
       
    if( ( isLeapYear(Year) ) && (Month == 2) ) // schaltjahr im Februar
    {
        if(Day > 29) // ist der Tag gösser 29, ist dann das datum falsch
            Erg = 0;
        else
            Erg = 1;
    }
    
    if( (Month <= 7) && ((Month % 2) != 0) ) // alle Monate, die kleiner gleich 7 sind und ungerade sind 31 Tage lang
    {
        if( Day > 31)
            Erg = 0;
        else
            Erg = 1;
    }
            
    else if( (Month > 7) && ((Month % 2) == 0) ) // alle Monate, die grösser als 7 sind und gerade sind 31 Tage lang
    {
        if(Day > 31)
            Erg = 0;
        else
            Erg = 1;
    }
    
    if( (Month == 4) || (Month == 6) )
    {
        if(Day > 30)
            Erg = 0;
        else
            Erg = 1;
    }
    
    else if( (Month == 9) || (Month == 11) )
    {
        if(Day > 30)
            Erg = 0;
        else
            Erg = 1;
    }
    
    return Erg;
}

//**********************************



//**********************************

int getDateFromString(char *Eingabe, TDate * Datum)
{
    int Erg = 0 , i; //Funktion Ergebnis und i ist Zählvariablen
    char * Tag = NULL;
    char * Monat = NULL;
    char * Jahr = NULL;
    char * Zeiger = Eingabe; // dieser Zeiger zeigt auf die eingebene Eingabe
    
    Tag = Zeiger;
    
    while(*Zeiger)
    {
        for(i = 0; *Zeiger != '.'; i++)
        {
            Zeiger++;
        }
        Zeiger++;
        
        Monat = Zeiger; // der zeiger ist jetzt gleich Monat
        
        for( ;  *Zeiger != '.'; i++)
        {
            Zeiger++;
        }
        Zeiger++;
        
        Jahr = Zeiger; // der zeiger ist jetzt gleich Jahr
        
        for( ; *Zeiger != '\0'; i++)
        {
            Zeiger++;
        }
        
    }
    
    int Jour = atoi(Tag);    // Text in Zahlen konvertieren
    int Mois = atoi(Monat);
    int Annee = atoi(Jahr);
    
    
    if(isDateValid(Jour, Mois, Annee))
    {
        Erg = 1; //
        
        Datum->Day = Jour ;
        Datum->Month = Mois;
        Datum->Year = Annee;
    }
    
    return Erg;

}
//**********************************



//**********************************
int isTimeValid(int Hour, int Minute, int Second)
{
    int Erg = 0;
    
    if( (Hour < 1) || (Hour > 12) || (Minute < 1) || (Minute > 60) || (Second < 1) || (Second > 60))
    {
        Erg = 0;
    }
   else
       Erg = 1;
    
    return Erg;
}
//**********************************



//**********************************
int getTimeFromString(char *Eingabe, TTime * Time)
{
    int Erg = 0, i; //Funktion Ergebnis und i ist Zählvariablen
    char * Std = NULL;
    char * Minute = NULL;
    char * Sekunde = NULL;
    char * Zeiger = Eingabe; // dieser Zeiger zeigt auf die eingebene Eingabe
    
    Std = Zeiger;
    
    while(*Zeiger)
    {
        for(i = 0; *Zeiger != ':'; i++)
        {
            Zeiger++;
        }
        Zeiger++;
        
        Minute = Zeiger; // der zeiger ist jetzt gleich Stunde
        
        for( ;  *Zeiger != ':'; i++)
        {
            Zeiger++;
        }
        Zeiger++;
        
        Sekunde = Zeiger; // der zeiger ist jetzt gleich Sekunde
        
        for( ; *Zeiger != '\0'; i++)
        {
            Zeiger++;
        }
        
    }
    
    int Heure = atoi(Std);    // Text in Zahlen konvertieren
    int Mn = atoi(Minute);
    int Seconde = atoi(Sekunde); // Mn = Minute
    
    
    if( isTimeValid(Heure, Mn, Seconde) )
    {
        Erg = 1; //
        
        Time->Hour = Heure ;
        Time->Minute = Mn;
        Time->Second = Seconde;

    }
    return Erg;
    
}

