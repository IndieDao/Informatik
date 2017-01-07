#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include "datastructure.h"

int compareDate(TAppointment *Appointment1, TAppointment *Appointment2);
void createAppointment();
void editAppointment();
void deleteAppointment();
void searchAppointment();
void sortCalendar();
void listCalendar();
void listAppointment(TAppointment *Appointment, int WithDate);
void freeCalendar();
void freeAppointment();

#endif // CALENDAR_H_INCLUDED
