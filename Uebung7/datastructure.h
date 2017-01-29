#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

typedef enum
{
NotADay, Mo, Tu, We, Th, Fr, Sa, Su
}TDayOfTheWeek;

/**< Datums-Konstrukt */
typedef struct sDate
{
    int             Day;
    int             Month;
    int             Year;
    TDayOfTheWeek   DayOfTheWeek;
}TDate;

/**< Zeit-Konstrukt */
typedef struct sTime
{
    int Hour;
    int Minute;
    int Second;
}TTime;

/**< Kalendereintags-Konstrukt */
typedef struct sAppointment
{
    TDate           DateOfAppointment;
    TTime           TimeOfAppointment;
    char            *Location;
    char            *Beschreibung;
    TTime           *Duration;
    struct sAppointment *Next;
    struct sAppointment *Previous;
}TAppointment;

#endif // DATASTRUCTURE_H_INCLUDED
