//
//  datastructure.h
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#ifndef datastructure_h
#define datastructure_h

#define MAXAPPOINTMENTS 100

typedef enum
{
   NotADay, Mo, Tu, We, Th, Fr, Sa, Su
    
} TDayOfTheWeek;


typedef struct
{
   int Day,
       Month,
       Year;
    TDayOfTheWeek Wochentag; // Die Variable Wochentag kann nur die Werte von NotDay bis Su haben (von 0 bis 7)
    
} TDate; // TDate Today = Mo; => Today = 1

typedef struct
{
   int Hour,
       Minute,
       Second;
    
} TTime;

typedef struct sTAppointment
{
    TTime Uhrzeit;
    TDate Datum;
    TTime * Termindauer;
    char * Ort;
    char * Beschreibung;
    struct sTAppointment * Next;
}TAppointment;

extern int countAppointment;
extern TAppointment Calendar[];

#endif /* datastructure_h */
