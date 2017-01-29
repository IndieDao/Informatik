#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED
//#include "datastructure.h"

//  vergĺeicht die Zeit von zwei Terminen
int compareTime(TAppointment *Appointment1, TAppointment *Appointment2);

//  vergĺeicht das Datum von zwei Terminen
int compareDate(TAppointment *Appointment1, TAppointment *Appointment2);

//  vergĺeicht die Beschreibung von zwei Terminen
int compareDescription(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht den Ort von zwei Terminen
int compareLocation(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht die Dauer von zwei Terminen
int compareDuration(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht zwei Terminen auf Gleichheit
int compareEquality(TAppointment *Appointment1, TAppointment *Appointment2);

#endif // COMPARE_H_INCLUDED
