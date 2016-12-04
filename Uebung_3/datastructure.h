#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

typedef enum
{
NotADay, Mo, Tu, We, Th, Fr, Sa, Su
}TDayOfTheWeek;

typedef struct
{
    int             Day;
    int             Month;
    int             Year;
    TDayOfTheWeek   DayOfTheWeek;
}TDate;

typedef struct
{
    int Hour;
    int Minute;
    int Second;
}TTime;

typedef struct
{
    TDate           DateOfAppointment;
    TTime           TimeOfAppointment;
    char            *Location;
    char            *Beschreibung;
    TTime           *Duration;
}TAppointment;

#endif // DATASTRUCTURE_H_INCLUDED
