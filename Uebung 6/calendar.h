#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include "datastructure.h"

//  ruft die (Quick-Sort)-funktionen, an den richtigen Indizes für die gewählte Sortierung auf.
void sortCalendar();

//  tauscht die Stellen zweier Appointments
void swapAppointment(TAppointment *Appointment1, TAppointment *Appointment2);

//  erstellt einen Termin in temporärem Kalender und speichert den Termin abschließend ins "calendar" Array.
void createAppointment();
//  bearbeitet einen Termin in temporärem Kalender und speichert den Termin abschließend nach "calendar".
void editAppointment();
//  löscht einen Termin indem der Zeiger auf das nächste Element gesetzt wird.
void deleteAppointment();
//
void searchAppointment();

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
