#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAX_APPOINTEMENTS 100

typedef enum
{
NotADay = 0, Mo = 1, Tu = 2, We = 3, Th = 4, Fr = 5, Sa = 6, Su = 7
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
    TDate           DateOfAppointement;
    TTime           TimeOfAppointment;
    TTime           *Duration;
    char            *Location;
    char            *Beschreibung;
}TAppointment;

extern int countAppointements;
extern TAppointment Calendar[MAX_APPOINTEMENTS];

#endif // DATASTRUCTURE_H_INCLUDED
