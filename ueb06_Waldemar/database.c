#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "datastructure.h"
#include "timedate.h"
#include "list.h"

 int cmpDateload(const void * a, const void * b )
{
    TAppointment *aa = (TAppointment*)a;
    TAppointment *bb = (TAppointment*)b;
    int difDate = ((aa->appDate.Year - bb->appDate.Year) *1000) + ((aa->appDate.Month - bb->appDate.Month)*10) + ((aa->appDate.Day - bb->appDate.Day));
    int difTime = ((aa->appTime.Hour - bb->appTime.Hour) *1000) + ((aa->appTime.Minute - bb->appTime.Minute)*10) + (aa->appTime.Second - bb->appTime.Second);
    if ( difDate )
        return difDate;
    else
        return difTime;
}

void saveAppointment(FILE * fp, TAppointment * appStruct)
{
    char tmpDate[11];
    char tmpTime[9];
    char tmpDuration[6];
    sprintf(tmpDate, "%02d.%02d.%04d", appStruct->appDate.Day, appStruct->appDate.Month, appStruct->appDate.Year);
    sprintf(tmpTime,"%02d:%02d:%02d", appStruct->appTime.Hour, appStruct->appTime.Minute, appStruct->appTime.Second);

    fprintf(fp," <Appointment>\n");
    fprintf(fp,"  <Date>%s</Date>\n",tmpDate);
    fprintf(fp,"  <Time>%s</Time>\n",tmpTime);
    fprintf(fp,"  <Description>%s</Description>\n",appStruct->appTitle);

    if(appStruct->appPlace != NULL)
        fprintf(fp,"  <Location>%s</Location>\n",appStruct->appPlace);

    if(appStruct->appDuration)
    {
        if((appStruct->appDuration->Hour != 0) || (appStruct->appDuration->Minute != 0))
        {
            sprintf(tmpDuration,"%02d:%02d", appStruct->appDuration->Hour, appStruct->appDuration->Minute);
            fprintf(fp,"  <Duration>%s</Duration>\n",tmpDuration);
        }
    }

    fprintf(fp," </Appointment>\n");
}

int loadAppointment(FILE * fp, int (*cmp)(const void*, const void*))
{
    TAppointment tmpApp;
    tmpApp.appDuration = NULL;
    tmpApp.appPlace    = NULL;
    tmpApp.appTitle    = NULL;
    char tmpline[101] = { 0 };
    char * line        = NULL;
    char * Date        = NULL;
    char * Time        = NULL;
    char * Description = NULL;
    char * tmpdes      = NULL;
    char * tmpdes1     = NULL;
    char * Location    = NULL;
    char * Duration    = NULL;
    char * del         = NULL;

    int Len       = 0,
        checkDate = 0,
        checkTime = 0,
        checkDesc = 0;

    do
    {
        if(fscanf( fp, "%100[^\n]", tmpline ) == 0)
            return 0;

        // next line in FILE
        seekNewLineFILE(fp);

        del = line = tmpline;

        // delete \r (WINDOWS OS)
        if (*(del+strlen(line) -1) == '\r')
            *(del+strlen(line) -1) = '\0';

        // skip white space
        while ( ( *line == ' ' ) || ( *line == 9 ) )
            line++;

        // get date string
        if ( strncmp( line, "<Date>", 6) == 0 )
        {
            //subtract length of end tag
            Len = strlen( line + 6 ) - 7;

            //check end tag
            if ( strncmp( line + 6 + Len, "</Date>", 7 ) == 0 )
            {
                Date = calloc( Len + 1, sizeof( char ) );
                if ( Date )
                    strncpy( Date, line + 6, Len );
            }
        }

        // get time string
        else if ( strncmp( line, "<Time>", 6) == 0 )
        {
            Len = strlen( line + 6 ) - 7;
            if ( strncmp( line + 6 + Len, "</Time>", 7 ) == 0 )
            {
                Time = calloc( Len + 1, sizeof( char ) );
                if ( Time )
                    strncpy( Time, line + 6, Len );
            }
        }

        // get description string
        else if ( strncmp( line, "<Description>", 13) == 0 )
        {
            if ( checkDesc == 0 )
            {
                Len = strlen( line + 13 ) - 14;
                if ( strncmp( line + 13 + Len, "</Description>", 14 ) == 0 )
                {
                    Description = calloc( Len + 1, sizeof( char ) );
                    if ( Description )
                        strncpy( Description, line + 13, Len );
                }
            }

            // if there is another entry
            if ( checkDesc == 1)
            {
                // save last entry
                Len = strlen( Description );
                tmpdes = calloc( Len + 1, sizeof( char ) );
                if ( tmpdes )
                    strncpy( tmpdes, Description, Len );
                free( Description );

                // get new entry
                Len = strlen( line + 13 ) - 14;

                if ( strncmp( line + 13 + Len, "</Description>", 14 ) == 0 ) // prüfen, ob Ende-Tag
                {
                    tmpdes1 = calloc( Len + 1, sizeof( char ) );
                    if ( tmpdes1 )
                        strncpy( tmpdes1, line + 13, Len );

                    // merge the two entries
                    Description = calloc( Len + 1 + strlen( tmpdes ) + 12, sizeof( char ) );
                    if ( Description )
                        sprintf(Description, "%s%s%s",tmpdes, "...*Zusatz: ", tmpdes1);
                }

                free(tmpdes1);
                free(tmpdes);
            }
            checkDesc = 1;
        }

        // get Location string
        else if ( strncmp( line, "<Location>", 10) == 0 )
        {
            Len = strlen( line + 10 ) - 11;
            if ( strncmp( line + 10 + Len, "</Location>", 11 ) == 0 )
            {
                Location = calloc( Len + 1, sizeof( char ) );
                if ( Location )
                    strncpy( Location, line + 10, Len );
            }
        }

        // get Duration string
        else if ( strncmp( line, "<Duration>", 10) == 0 )
        {
            Len = strlen( line + 10 ) - 11;
            if ( strncmp( line + 10 + Len, "</Duration>", 11 ) == 0 )
            {
                Duration = calloc( Len + 1, sizeof( char ) );
            if ( Duration )
                strncpy( Duration, line + 10, Len );
            }
        }
        else
        {
            break;
        }


    } while ( strncmp(line, "</Appointment>", 11) != 0 );

    // transform into struct
    if ( Date )
        checkDate = getDateFromString(Date, &tmpApp.appDate);

    if ( Time )
        checkTime = getTimeFromString(Time, &tmpApp.appTime);

    if ( Description )
    {
        tmpApp.appTitle = Description;
        checkDesc = 1;
    }
    if ( Location )
        tmpApp.appPlace = Location;

    if ( Duration )
    {
        tmpApp.appDuration = calloc(1, sizeof(TTime));
        if(tmpApp.appDuration == NULL)
        {
            perror("Speicherplatz konnte nicht bereitgestellt werden.\n");
            return 0;
        }
        getTimeFromString(Duration, tmpApp.appDuration);
    }

    if(checkDate && checkDesc && checkTime)
    {
        TAppointment *newApp = calloc(1, sizeof(TAppointment));
        if( !newApp )
        {
            perror("Termin konnte nicht geladen werden. Celloc error.");
            return 0;
        }
        newApp->appDate.weekDay = tmpApp.appDate.weekDay;
        newApp->appDate.Day     = tmpApp.appDate.Day;
        newApp->appDate.Month   = tmpApp.appDate.Month;
        newApp->appDate.Year    = tmpApp.appDate.Year;
        newApp->appTime.Hour    = tmpApp.appTime.Hour;
        newApp->appTime.Minute  = tmpApp.appTime.Minute;
        newApp->appTime.Second  = tmpApp.appTime.Second;
        newApp->appPlace        = tmpApp.appPlace;
        newApp->appTitle        = tmpApp.appTitle;
        newApp->appDuration     = tmpApp.appDuration;
        insertInDList(newApp, cmp);
        countAppointments++;
        free( Date );
        free( Time );
        return 1;
    }

    else
    {
        free( Date );
        free( Time );
        return 0;
    }
    return 0;
}


int saveCalendar()
{
    TAppointment * tmp = First;

    FILE * fp = fopen("calendar.xml", "w");

    if(!fp)
    {
        perror("Die Datei konnte nicht geoeffnet werden.\n");
        return 0;
    }

    fprintf(fp,"<Calendar>\n");

    while( tmp )
    {
        saveAppointment(fp, tmp);
        tmp = tmp->Next;
    }

    fprintf(fp,"</Calendar>");
    fclose(fp);
    return 1;
}


int loadCalendar(int (*cmp)(const void*, const void*))
{
    char tmpline[101];
    char * del = NULL;
    char * line = NULL;

    FILE * fp = fopen("calendar.xml", "r");
    if(!fp)
    {
        fprintf(stderr, "Die Datei konnte nicht geoeffnet werden.\n");
        return 0;
    }

    do
    {
        if(fscanf( fp, "%100[^\n]", tmpline ) == 0)
            return 0;

        seekNewLineFILE(fp);

        if( feof( fp ) )
            break;

        del = line = tmpline;

        if (*(del+strlen(line) -1) == '\r')
            *(del+strlen(line) -1) = '\0';

        while ( (*line == ' ') || (*line == 9) )
            line++;

        if ( strncmp( line, "<Appointment>", 13) == 0 )
        {
            if( loadAppointment(fp, cmpDateload) == 0 )
                return 0;
        }
    } while ( strncmp(line, "</Calendar>", 11) != 0 );

    fclose(fp);
    return 1;
}
