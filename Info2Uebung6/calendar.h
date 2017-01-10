#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include "datastructure.h"


void swapAppointment(TAppointment Appointment1, TAppointment Appointment2);
int compareTime(TAppointment Appointment1, TAppointment Appointment2);
int compareDate(TAppointment Appointment1, TAppointment Appointment2);
int compareDescription(TAppointment Appointment1, TAppointment Appointment2);
int compareLocation(TAppointment Appointment1, TAppointment Appointment2);
int compareDuration(TAppointment Appointment1, TAppointment Appointment2);


void createAppointment();
void editAppointment();
void deleteAppointment();
void searchAppointment();
void listAppointment(TAppointment *Appointment, int WithDate);
int compareEquality(TAppointment *Appointment1, TAppointment *Appointment2);

void sortCalendar();
void listCalendar();

void freeCalendar();
void freeAppointment();

//compare comparePointer[] = { compareDate, compareTime, compareDescription, compareLocation };
#endif // CALENDAR_H_INCLUDED
