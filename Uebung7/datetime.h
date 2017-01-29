#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED

//  schreibt die Tokens aus tmpToken() in Datumszeiger und setzt von dort aus Zeiger in die angelegte Datumsstruktur
//  Prüft in Unterprogramm Validität der Eingabe.
int getDateFromString(char *Eingabe, TDate *Datum);
//  schreibt die Tokens aus tmpToken() in Zeitzeiger und setzt von dort aus Zeiger
//  in die angelegte Zeitstruktur. Prüft in Unterprogramm Validität der Eingabe.
int getTimeFromString(char *Eingabe, TTime *Zeit);
//  gibt bei korrekter Zeitangabe "true" zurück, ansonsten false
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde);
//  gibt bei korrektem Datum "true" zurück, ansonsten false
int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr);
//  gibt bei Schaltjahr "true" zurück, ansonsten false
int isLeapYear(int Jahr);
//  prüft Benutzereingabe eines Datum über Input und schreibt bei Validität die
//  Daten via der Funktion getDateFromString in ein TDate Konstrukt.
int getDate(char *, TDate *);
//  prüft Benutzereingabe einer Uhrzeit über Input und schreibt bei Validität die
//  Daten via der Funktion getTimeFromString in ein TTime Konstrukt.
int getTime(char *, TTime *);
//  Gibt Datum eines Termins in Konsole aus und ruft Unterprogramm für weitere Daten.
void printDate(TAppointment *cal);
//  Gibt Zeit und Dauer eines Termins auf der Konsole aus
void printTime(TAppointment *cal);
//  errechnet Endzeit eines Termins aus der Angabe von Dauer
TTime addDuration(TAppointment *);
#endif // DATETIME_H_INCLUDED
