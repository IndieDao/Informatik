#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAX_APPOINTEMENTS 100

typedef enum {NotADay = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6, Sunday = 7}TDayOfTheWeek;

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
    char            *Location;
    TTime           *Duration;
}TAppointment;

extern int countAppointements;
extern TAppointment Calendar[MAX_APPOINTEMENTS];

#endif // DATASTRUCTURE_H_INCLUDED
