#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include "datastructure.h"

//  ruft die (Quick-Sort)-funktionen, an den richtigen Indizes für die gewählte Sortierung auf.
void sortCalendar();

//  tauscht die Stellen zweier Appointments
void swapAppointment(TAppointment *Appointment1, TAppointment *Appointment2);

//  vergĺeicht die Zeit von zwei Terminen
int compareTime(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht das Datum von zwei Terminen
int compareDate(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht die Beschreibung von zwei Terminen
int compareDescription(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht den Ort von zwei Terminen
int compareLocation(TAppointment Appointment1, TAppointment Appointment2);

//  vergĺeicht die Dauer von zwei Terminen
int compareDuration(TAppointment Appointment1, TAppointment Appointment2);

//  erstellt einen Termin in temporärem Kalender und speichert den Termin abschließend ins "calendar" Array.
void createAppointment();
//  bearbeitet einen Termin in temporärem Kalender und speichert den Termin abschließend nach "calendar".
void editAppointment();
//  löscht einen Termin indem der Zeiger auf das nächste Element gesetzt wird.
void deleteAppointment();
//
void searchAppointment();


//  vergĺeicht zwei Terminen auf Gleichheit
int compareEquality(TAppointment *Appointment1, TAppointment *Appointment2);
//  Bildschirmausgabe der geladenen Termine
void listCalendar();
//  Gibt jeweils einen Termin aus. Termine gleichen Datums werden zusammen ausgegeben.
void listAppointment(TAppointment *Appointment, int WithDate);
//  löscht den im Programmspeicher angelegten Kalender
void freeCalendar();
void freeAppointment();



//static int (*compare[])(TAppointment *, TAppointment *) = { compareDate, compareTime, compareDuration, compareDescription, compareLocation };   /** Funktionsarray          */
//static void (*exchange[])(TAppointment *, TAppointment *) = { swapAppointment };   /** Funktionsarray          */

//compare comparePointer[] = { compareDate, compareTime, compareDescription, compareLocation };

#endif // CALENDAR_H_INCLUDED
