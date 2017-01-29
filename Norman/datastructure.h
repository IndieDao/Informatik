#pragma once

#define MAXAPPOINTMENTS 100

typedef enum TDayOfTheWeek {
	NotADay = 0,
	Mo = 1,
	Tu = 2,
	We = 3,
	Th = 4,
	Fr = 5,
	Sa = 6,
	Su = 7
}TDayOfTheWeek;

typedef struct TDate{
	int day;
	int month;
	int year;
	TDayOfTheWeek weekday;
}TDate;

typedef struct TTime {
	int hour;
	int minute;
	int second;
}TTime;

typedef struct TAppointment {
	TDate date;
	TTime time;
	char *description;
	char *location;
	TTime *duration;
}TAppointment;

extern int countAppointments;
extern TAppointment calendar[];