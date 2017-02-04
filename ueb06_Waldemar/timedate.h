#ifndef TIMEANDDATE_H_
#define TIMEANDDATE_H_

#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

int getDateFromString(char *Input, TDate *date);

int getTimeFromString(char *Input, TTime *time);
int getDate(char * text, TDate * dateStruct);
int getTime(char * text, TTime * timeStruct, int Leer);
void printDate(TDate dateStruct);
void printTime(TTime timeStruct, TTime * Duration);
TTime *addTime(TTime start, TTime * Duration);

#endif
