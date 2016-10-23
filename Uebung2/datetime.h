#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED

int isLeapYear(int Jahr);

char *tmpToken(char *Eingabe, char Token);

int daysInMonth(int Monat, int Jahr);

int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr);

int getDateFromString(char *Eingabe, TDate *Datum);

int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde);

int getTimeFromString(char *Eingabe, TTime *Zeit);

void clean();

#endif // DATETIME_H_INCLUDED
