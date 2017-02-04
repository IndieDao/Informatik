#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timedate.h"
#include "tools.h"
#include "datastructure.h"
#include "escapesequenzen.h"


TTime *addTime(TTime start, TTime * Duration)
{
    TTime * endTime = calloc( 1, sizeof( TTime ));
    if( !endTime )
        return NULL;

    int checkTime = 0,
        endH      = start.Hour,
        endM      = start.Minute,
        endS      = start.Second;

    if( Duration )
    {
        endS += Duration->Second;
        endM += Duration->Minute;
        endH += Duration->Hour;
    }

    if( endS >= 60 )
    {
        endM ++;
        endS = endS - 60;
    }

    if( endM >= 60 )
    {
        endH ++;
        endM = endM - 60;
    }

    if( endH >= 24 )
        endH = endH - 24;

    if( ((endS < 60) && (endS >=0) ) && ((endM < 60) && (endM >= 0)) && ((endH < 24) && (endH >= 0)) )
        checkTime = 1;

    if( checkTime )
    {
        endTime->Hour   = endH;
        endTime->Minute = endM;
        endTime->Second = endS;
        return endTime;
    }
    else
        return NULL;

    return NULL;

}


int getDayOfWeek(TDate dateStruct)
{
    int y = dateStruct.Year;
    int m = dateStruct.Month;
    int d = dateStruct.Day;

    if (m < 3)
        y = y - 1;

    int w = (int)((d + (int)floor(2.6 * ((m + 9) % 12 + 1) - 0.2) + y % 100 + (int)floor(y % 100 / 4) + (int)floor(y / 400) - 2 * (int)floor(y / 100) - 1) % 7 + 7) % 7 + 1;
    return w;
}


int isLeapYear(TDate * date)
{
    if(date->Year % 400 == 0)
        return 1;

    else if(date->Year % 100 == 0)
        return 0;

    else if(date->Year % 4 == 0)
        return 1;

    else
        return 0;
}


int checkthirty(TDate * date)
{
    if((date->Day < 31) && (date->Day > 0))
        return 1;
    else
        return 0;
}


int ckeckthirtyone(TDate * date)
{
    if((date->Day < 32) && (date->Day > 0))
        return 1;
    else
        return 0;
}


int checkfebr(TDate * date)
{
    int leapyear = isLeapYear(date);

    if(leapyear == 0)
    {
        if((date->Day < 29) && (date->Day > 0))
            return 1;
        else
            return 0;
    }
    else if(leapyear == 1)
    {
        if((date->Day < 30) && (date->Day > 0))
            return 1;
        else
            return 0;
    }

    else
        return 0;
}


int isDateValid(TDate * date)
{
    int valid = 0;

    switch(date->Month)
    {
        case  4:
        case  6:
        case  9:
        case 11:    valid = checkthirty(date);
                    break;

        case  2:    valid = checkfebr(date);
                    break;

        default:    valid = ckeckthirtyone(date);

    }
    return valid;
}


int isTimeValid(TTime * time)
{
    int validhour = 0,
        validminute = 0,
        validsecond = 0;

    if((time->Hour < 24) && (time->Hour >= 0))
        validhour = 1;

    if((time->Minute < 60) && (time->Minute >= 0))
        validminute = 1;

    if((time->Second < 60) && (time->Second >= 0))
        validsecond = 1;

    if((validhour == 1) && (validminute == 1) && (validsecond == 1))
        return 1;

    else
        return 0;
}


int getDateFromString(char *Input, TDate *date)
{
    TDate tmpDate;
    char * day   = Input;
    char * month = NULL;
    char * year  = NULL;

    int valid    = 0,
            i    = 0;

    while((*(Input+i) != '.') && (*(Input+i) != '\0'))
        i++;

    month = Input+ ++i;

    while((*(Input+i) != '.') && (*(Input+i) != '\0'))
        i++;

    year = Input+ ++i;

    tmpDate.Day   = atoi(day);
    tmpDate.Month = atoi(month);
    tmpDate.Year  = atoi(year);

    if((tmpDate.Month < 1) || (tmpDate.Month > 12))
        return 0;


    if(isDateValid(&tmpDate))
    {
        date->Day   = tmpDate.Day;
        date->Month = tmpDate.Month;
        date->Year  = tmpDate.Year;
        date->weekDay = getDayOfWeek(tmpDate);
        valid = 1;
    }

    else
        valid = 0;

    return valid;
}


int getTimeFromString(char *Input, TTime *time)
{
    TTime tmpTime;
    char * hour   = Input;
    char * minute = NULL;
    char * second = NULL;

    int valid = 0,
        i     = 0;

    if( time == NULL)
        return 0;

    while((*(Input+i) != ':') && (*(Input+i) != '\0'))
        i++;

    minute = Input+ ++i;
    if(*minute == '\0')
        return 0;

    while((*(Input+i) != ':') && (*(Input+i) != '\0'))
        i++;

    second = Input+ ++i;

    tmpTime.Hour   = atoi(hour);
    tmpTime.Minute = atoi(minute);
    tmpTime.Second = atoi(second);

    if(isTimeValid(&tmpTime))
    {

        time->Hour   = tmpTime.Hour;
        time->Minute = tmpTime.Minute;
        time->Second = tmpTime.Second;
        valid = 1;
    }

    else
        valid = 0;

    return valid;
}


int getDate(char * text, TDate * dateStruct)
{
    int valid = 0;
    char * input = NULL;

    getText(text, 10, &input, 0);
    valid = getDateFromString(input, dateStruct);

    free(input);
    return valid;
}

int getTime(char * text, TTime * timeStruct, int Leer)
{
    int valid = 0;
    char * input = NULL;

    getText(text, 10, &input, Leer);

    if (input != NULL)
        valid = getTimeFromString(input, timeStruct);
    else
        valid = 1;

    free(input);

    return valid;

}

void printDate(TDate dateStruct)
{
    char * tmpday[] = {"NotADay", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    printf("%s, %02d.%02d.%04d:\n", tmpday[dateStruct.weekDay], dateStruct.Day, dateStruct.Month, dateStruct.Year);
    printLine('-', 15);
}


void printTime(TTime timeStruct, TTime * Duration)
{
    TTime * endTime = addTime(timeStruct, Duration);
    if( !endTime )
    {
        perror("endTime fail.");
        return;
    }
    if( (timeStruct.Hour == endTime->Hour) && (timeStruct.Minute == endTime->Minute) && (timeStruct.Second == endTime->Second))
        printf("%02d:%02d         -> ", timeStruct.Hour, timeStruct.Minute);
    else
        printf("%02d:%02d - %02d:%02d -> ", timeStruct.Hour, timeStruct.Minute, endTime->Hour, endTime->Minute);

    free(endTime);
}

