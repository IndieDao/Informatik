#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "datetime.h"
#include "datastructure.h"
#include "datastructure.h"

TTime addTime(TTime * t1, TTime * t2);

int getDate(char *prompt, TDate* date);
int getTime(char *prompt, TTime* time, int nonzero);

int isLeapYear(int*);

int isDateValid(TDate*);

int isTimeValid(TTime*, int nonzero);

int getDateFromString(char*, TDate*);

int getTimeFromString(char*, TTime*, int nonzero);

void printDOW(TDate * date);

void printDate(TDate *date);

void printTime(TTime *time);

int sameDate(TDate * d1, TDate * d2);
