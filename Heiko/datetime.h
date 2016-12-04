#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED


char *tmpToken(char *Eingabe, char Token);

int daysInMonth(int Monat, int Jahr);

int getDateFromString(char *Eingabe, TDate *Datum);
int getTimeFromString(char *Eingabe, TTime *Zeit);
int isTimeValid(unsigned int Sekunde, unsigned int Minute, unsigned int Stunde);
int isDateValid(unsigned int Tag, unsigned int Monat, int Jahr);
int isLeapYear(int Jahr);

//int getDate(char *, TDate *);
//int getTime(char *, TTime *);

void clean();

#endif // DATETIME_H_INCLUDED
