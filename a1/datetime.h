//
//  datetime.h
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#ifndef datetime_h
#define datetime_h


#include <stdio.h>
#include "datastructure.h"
#include "escapesequenzen.h"

int isLeapYear( int);
int isDateValid(int , int , int);
int isTimeValid(int, int, int);
int getDateFromString(char *, TDate *);
int getTimeFromString(char *, TTime *);
void getDate(char *, TDate *);
void getTime(char *, TTime *);
void printTime(TAppointment *);
void printDate(TAppointment *);
void printDauer(TAppointment *);


#endif /* datetime_h */
