#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

char *extractLineContent(char * Line, char *Tag, char *endTag);
int saveCalendar();
int saveAppointment(FILE *, int indexOfAppointment);
int loadCalendar();
int loadAppointment(FILE *XML);

#endif // DATABASE_H_INCLUDED
