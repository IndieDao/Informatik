#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

//  Gibt den Inhalt einer Zeile ohne die umschliessenden Tags zurück
char *extractLineContent(char * Line, char *Tag, char *endTag);
//  Oeffnet oder erstellt Sicherungsdatei (die überschrieben wird), ruft für alle gespeicherten Appointments saveAppointment auf.
int saveCalendar();
//  schreibt ein Appointment aus dem Kalender in XML in die angegebene Datei
int saveAppointment(FILE *, int indexOfAppointment);
//  Oeffnet bei Start die angegebene Datei und ruft für alle Appointments innerhalb der <Calender> Tags loadAppointment auf.
int loadCalendar();
//  lädt Daten genau eines Appointment aus dem *.XML File und kopiert dieses abschließend in die Kalenderstruktur.
int loadAppointment(FILE *XML);

#endif // DATABASE_H_INCLUDED
