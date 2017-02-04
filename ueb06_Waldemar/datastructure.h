#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#define MAXAPPOINTMENTS 100
/**
 *
 */
typedef enum
{
	NotADay, Mo, Tu, We, Th, Fr, Sa, Su

} TDayOfTheWeek;


typedef struct
{
  int Day,
      Month,
      Year;
  TDayOfTheWeek weekDay;

}TDate;

typedef struct
{
  int Hour,
      Minute,
      Second;

}TTime;

typedef struct doubleList
{
  TDate appDate;
  TTime appTime;
  char * appTitle;
  char * appPlace;
  TTime * appDuration;
  struct doubleList * Next;
  struct doubleList * Prev;

}TAppointment;


extern int countAppointments;

extern TAppointment *First, *Last;

#endif
