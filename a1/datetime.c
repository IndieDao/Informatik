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
#include <string.h>
#include "math.h"


/********************************************************************
                                                                    *
Die Funktiion prüft ob es sich um ein Schaltjahr händelt oder nicht *
Parameter: das Year                                                 *
Ergebnis: return eine Wahrheitswert                                 *
                                                                    *
*********************************************************************/

int isLeapYear(int Year)
{
   int Erg = 0;
    
    if( ( (Year % 100) != 0 && (Year % 4) == 0) || (Year % 400) == 0)
        Erg = 1;
    else
        Erg = 0;
    
return Erg;
}

/*********************************************
                                             *
Diese Funktion prüft ob das Datum Valid ist  *
Parameter: Tag, Monat und Jahr               *
Ergebnis: return eine Wahrheitswert          *
**********************************************/

int isDateValid(int Day, int Month, int Year)
{
    int Erg = 0;
    
    if( ( (Day < 1) || (Day > 31) ) || ( (Month < 1) || (Month > 12) ) || (Year < 0) )
        return 0;; // es ist kein gültiges Datum
   
    if(Month == 2)
    {
        if (  isLeapYear(Year) ) // schaltjahr im Februar
        {
            if(Day > 29) // ist der Tag gösser 29, ist dann das datum falsch
                Erg = 0;
            else
                Erg = 1;
        }
       
        else
        {
            if(Day > 28) // ist der Tag gösser 29, ist dann das datum falsch
                Erg = 0;
            else
                Erg = 1;
        }
        
    }
    
    if( (Month <= 7) && ( (Month % 2) != 0 ) ) // alle Monate, die kleiner gleich 7 sind und ungerade sind 31 Tage lang
    {
        if( Day <= 30)
            Erg = 1;
        else
            Erg = 0;
    }
            
   if( (Month > 7) && ( (Month % 2) == 0 ) ) // alle Monate, die grösser als 7 sind und gerade sind 31 Tage lang
    {
        if(Day <= 31)
            Erg = 1;
        else
            Erg = 0;
    }
    
    if( (Month == 4) || (Month == 6) || (Month == 9) || (Month == 11) )
    {
        if(Day <= 30)
            Erg = 1;
        else
            Erg = 0;
    }
    
    
    if( (Erg == 1) && (Year >= 0) )
        return 1;
    
    if ( (Month == 2) && (Year == 0) )
        Erg = 1;

    return Erg;
}

/****************************************************
                                                    *
Diese Funktion erhält einen Text, und soll          *
dieser Text in 3 Zahlen zerlegen, die 3 Zahlen      *
werden in dem Datastruct gespeichert.               *
                                                    *
Parameter: Text und datastruct                      *
Ergebnis: return eine Wahrheitswert                 *
*****************************************************/

int getDateFromString(char * Eingabe, TDate * Datum)
{
    int    Erg = 0 , i; //Funktion Ergebnis und i ist Zählvariablen
    char * Tag = NULL;
    char * Monat = NULL;
    char * Jahr = NULL;
    char * Zeiger = Eingabe; // dieser Zeiger zeigt auf die eingebene Eingabe
    
    Tag = Zeiger;
    
    while(*Zeiger)
    {
        for(i = 0; (*Zeiger != '.') && (*Zeiger != '\0'); i++)
        {
            Zeiger++;
        }
        
        Zeiger++;
        Monat = Zeiger; // der zeiger ist jetzt gleich Monat
            
        for( ; (*Zeiger != '.') && (*Zeiger != '\0'); i++)
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
    
    if(Tag == 0)
        return 0; // der Benutzer muss etwas eingeben
    
    if( isDateValid(Jour, Mois, Annee) )
    {
        Erg = 1; //
        
        Datum->Day = Jour ;
        Datum->Month = Mois;
        Datum->Year = Annee;
    }
    
    
    
    //Wochentagsberechnung 
    int d = Jour;
    int m = Mois;
    int y = Annee;
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    int W = ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; // W = Tag der Woche
    
    switch(W)
    {
        case 1: Datum->Wochentag = Mo;      break;
        case 2: Datum->Wochentag = Tu;      break;
        case 3: Datum->Wochentag = We;      break;
        case 4: Datum->Wochentag = Th;      break;
        case 5: Datum->Wochentag = Fr;      break;
        case 6: Datum->Wochentag = Sa;      break;
        case 7: Datum->Wochentag = Su;      break;
        
    }

    
    return Erg;
}

/************************************************
                                                *
 Diese Funktion prüft ob die Uhrzeit Valid ist  * Fertig
 Parameter: Stunde, Minute und Sekunde          *
 Ergebnis: return eine Wahrheitswert            *
 ************************************************/
int isTimeValid(int Hour, int Minute, int Second)
{
    int Erg = 0;
    
    if( ((Hour < 24 ) && (Hour >= 0)) && ((Minute >= 0 ) && (Minute < 60)) && ((Second >= 0) && (Second < 60)))
    {
        Erg = 1;
    }
     //else Erg wäre = 0 wie initialisiert
   
    return Erg;
}

/*****************************************************
                                                     *
 Diese Funktion erhält einen Text, und soll          *
 dieser Text in 3 Zahlen zerlegen, die 3 Zahlen      *
 werden in dem Datastruct gespeichert.               * Fertig
 Parameter: Text und datastruct                      *
 Ergebnis: return eine Wahrheitswert                 *
 *****************************************************/
int getTimeFromString(char * Eingabe, TTime * Time)
{
    int Erg = 0, i; //Funktion Ergebnis und i ist Zählvariablen
    char * Std = NULL;
    char * Minute = NULL;
    char * Sekunde = NULL;
    char * Zeiger = Eingabe; // dieser Zeiger zeigt auf die eingebene Eingabe
    Std = Zeiger;
    
    while(*Zeiger)
    {
        for(i = 0; (*Zeiger != ':') && (*Zeiger != '\0'); i++)
        {
            Zeiger++;
        }
        
        if ( *Zeiger == ':')
        {
            Zeiger++;
            Minute = Zeiger; // der Zeiger ist jetzt gleich Minute
        
            for( ; (*Zeiger != ':') && (*Zeiger != '\0'); i++)
            {
                Zeiger++;
            }

            if ( *Zeiger == ':') // else Sekunde = NULL wie bei der Initialisierung
            {
                Zeiger++;
                Sekunde = Zeiger; // der zeiger ist jetzt gleich Sekunde
                for( ; *Zeiger != '\0'; i++)
                {
                    Zeiger++;
                }

            }
            
        }
        
    }
    
    if(Minute ==  NULL)
      return Erg = 0;
    
    int Heure = atoi(Std);    // Text in Zahlen konvertieren
    int Mn = atoi(Minute);
    int Seconde;
    
    if(Sekunde != 0)
        Seconde = atoi(Sekunde); // Mn = Minute
    else
        Seconde = 0;
    
    
    
    if( isTimeValid(Heure, Mn, Seconde) )
    {
        Erg = 1; //
        
        Time->Hour = Heure ;
        Time->Minute = Mn;
        Time->Second = Seconde;
        
    }
    
    
    return Erg;
}


/*****************************************************
                                                     *
 Diese Funktion erhält einen Text, und soll          *
 dieser Text in 3 Zahlen zerlegen, die 3 Zahlen      *
 werden in dem Datastruct gespeichert.               *
                                                     *
 Parameter: Text und datastruct                      *
 Ergebnis: return eine Wahrheitswert                 *
 *****************************************************/

void getDate(char * Titel, TDate * Date) // Einbage = Eingabebaufforderung
{
    char Input[20];
    
    do
    {
        printf("%s: ", Titel);
        scanf("%19[^\n]", Input);
        clearBuffer();
    
        if(*Input == '\0')
            continue; // springt zum Anfang der Schleife
        
    } while( getDateFromString(Input, Date) == 0);
    
    
    
}


/*****************************************************
                                                     *
 Diese Funktion erhält einen Text, und soll          *
 dieser Text in 3 Zahlen zerlegen, die 3 Zahlen      *
 werden in dem Datastruct gespeichert.               *
                                                     *
 Parameter: Text und datastruct                      *
 Ergebnis: return eine Wahrheitswert                 *
 *****************************************************/

void getTime(char * Titel, TTime * Time)
{
    char Input[20];
    //char * Z = NULL; // char **, weil der soll auf einen Zeiger zeigen und zwar auf 'char * Input'
   
    do
    {
        printf("%s: ", Titel);
        scanf("%19[^\n]", Input);
        clearBuffer();
    
        if( *Input == '\0' ) // if das erste Element Input == 0
            continue; // springt zum Anfang der Schleife
        
    } while (getTimeFromString(Input, Time) == 0);

    
}



void printTime( TAppointment * calender)
{
    int i = 0;
    
    if( (calender + i)->Uhrzeit.Second == 0)
        printf("   %02i:%02i -> ", (calender + i)->Uhrzeit.Hour, (calender + i)->Uhrzeit.Minute);
    
    else if ( (calender + i)->Uhrzeit.Second != 0)
        printf("   %02d:%02d:%02d -> ", (calender + i)->Uhrzeit.Hour, (calender + i)->Uhrzeit.Minute,(calender + i)->Uhrzeit.Second);
    i++;
    
}



void printDate( TAppointment * calender)
{
    int i = 0;
    
    switch( (calender + i)->Datum.Wochentag )
    {
        case 0:                      break;
        case 1: printf("Mo, ");      break;
        case 2: printf("Di, ");      break;
        case 3: printf("Mi, ");      break;
        case 4: printf("Do, ");      break;
        case 5: printf("Fr, ");      break;
        case 6: printf("Sa, ");      break;
        case 7: printf("So, ");      break;
    }

    printf("%02i.%02i.%04i:\n", (calender + i)->Datum.Day, (calender + i)->Datum.Month, (calender + i)->Datum.Year);
    i++;
    
}



void printDauer(TAppointment * calender)
{
    if( (calender + countAppointment)->Termindauer->Second == 0 )
        printf("%02i:%02i -> ", (calender + countAppointment)->Termindauer->Hour, (calender + countAppointment)->Termindauer->Minute);
   
    else  if( calender[countAppointment].Termindauer->Second != 0)
        printf("%02i:%02i:%02i -> ", (calender + countAppointment)->Termindauer->Hour, (calender + countAppointment)->Termindauer->Minute,(calender + countAppointment)->Termindauer->Second);
}







