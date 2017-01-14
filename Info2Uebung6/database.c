#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "datastructure.h"
#include "datetime.h"
#include "calendar.h"
#include "tools.h"

#define DATE "<Date>"
#define TIME "<Time>"
#define DESCRIPTION "<Description>"
#define LOCATION "<Location>"
#define DURATION "<Duration>"
#define APPOINTMENT "<Appointment>"

#define DATEEND "</Date>"
#define TIMEEND "</Time>"
#define DESCRIPTIONEND "</Description>"
#define LOCATIONEND "</Location>"
#define DURATIONEND "</Duration>"
#define APPOINTMENTEND "</Appointment>"

/*************************************************************************
*   Alle Datenbank-Funktionen werden hier als Funktion programmiert.
*   Die Fallunterscheidung für einzelne Tags findet hier statt.
*************************************************************************/
extern int countAppointments;                       //zählt Einträge
extern TAppointment calendar[MAX_APPOINTEMENTS];
//extern TTime Duration[MAX_APPOINTEMENTS];
static char *lineContent;

//  --------------------------------------------------------------------------------
//  Gibt den Inhalt einer Zeile ohne die umschliessenden Tags zurück
//  --------------------------------------------------------------------------------
char *extractLineContent(char * Line, char *Tag, char *endTag)
{
    int Len = 0;
    int TagLength = strlen(Tag);
    int endTagLength = TagLength+1;

    lineContent = calloc( Len, sizeof(char));
    //printf("%s",Line);
    if ( strncmp( Line, Tag, TagLength) == 0)                               //Wenn Zeile und angegebenes Tag uebereinstimmen
    {
        while ( (strncmp((Line + TagLength + Len), endTag, endTagLength) != 0) || ((Line + TagLength + Len) == '\0')) //ist ein Ende Tag vorhanden?
        {
            Len++;
            lineContent = realloc( lineContent, Len*sizeof(char));
                          //schreibe Inhalt der Zeile
        }
        if (lineContent)
            strncpy(lineContent, (Line + TagLength), Len);
        else
        {
            lineContent = "";                                                  // setze  - falls leeres Feld
        }
    }
    return lineContent;
}

//  --------------------------------------------------------------------------------
//  lädt Daten genau eines Appointment aus dem *.XML File und kopiert dieses
//  abschließend in die Kalenderstruktur
//  --------------------------------------------------------------------------------
int loadAppointment(FILE *XML)
{
int i;
TAppointment *Appointment;
Appointment = calloc(1, sizeof(TAppointment));
char Zeile[100];
char *Zeilenanfang = NULL;
char * del         = NULL;
Zeilenanfang = calloc(100, sizeof(char));
Appointment->Duration = calloc(1, sizeof(TTime));    // weil Dauer ein Zeiger ist
    do
    {
        //lineContent = calloc(100, sizeof(char));
        fgets(Zeile, 100, XML);
        //fscanf(XML, "%100[^\n]", Zeile);

        del = Zeilenanfang = Zeile;

        if (*(del+strlen(Zeilenanfang) -1) == '\r')
            *(del+strlen(Zeilenanfang) -1) = '\0';

        while ((*Zeilenanfang == ' ') || (*Zeilenanfang == 9))                          //loescht führende Leerstellen
            Zeilenanfang++;

        if (feof(XML))                                                                  //bei unerwartetem Ende
        {
            break;
        }
        else if (strncmp(Zeilenanfang, "<Date>", 6) == 0)                               //Datumsroutine
        {
            extractLineContent(Zeilenanfang, DATE, DATEEND);
            getDateFromString(lineContent, &Appointment->DateOfAppointment);
            //free(lineContent);                                                        // bringt alles zum Absturz
        }
        else if (strncmp(Zeilenanfang, "<Time>", 6) == 0)                               //Zeitroutine
        {
            extractLineContent(Zeilenanfang, TIME, TIMEEND);
            getTimeFromString(lineContent, &Appointment->TimeOfAppointment);
        }
        else if (strncmp(Zeilenanfang, "<Description>", 6) == 0)                        //Beschreibung-Routine
        {
            extractLineContent(Zeilenanfang, DESCRIPTION, DESCRIPTIONEND);
            while (isspace(*lineContent)) lineContent++;
            Appointment->Beschreibung = lineContent;
        }
        else if (strncmp(Zeilenanfang, "<Location>", 6) == 0)                           //Ort-Routine
        {
            extractLineContent(Zeilenanfang, LOCATION, LOCATIONEND);
            while (isspace(* lineContent)) lineContent++;
            Appointment->Location = lineContent;
        }
        else if (strncmp(Zeilenanfang, "<Duration>", 6) == 0)                           //Dauerroutine
        {
            //Appointment.Duration = realloc (Appointment.Duration, 1*sizeof(TTime));                   // weil Dauer ein Zeiger ist
            extractLineContent(Zeilenanfang, DURATION, DURATIONEND);
            getTimeFromString(lineContent,  Appointment->Duration);
            //getTimeFromString(lineContent,  &Duration[countAppointments]);
        }
    }while (strncmp(Zeilenanfang, APPOINTMENTEND, 14) != 0);

    if( Appointment->Location == NULL )
    {
        Appointment->Location = "";
    }
                                                                                //Ab hier Übertrag in Kalender
    calendar[countAppointments] = *Appointment;
    //printf("q%02i:%02i\n", calendar[countAppointments].Duration->Hour, calendar[countAppointments].Duration->Minute);
    countAppointments++;
    free(Appointment);

    for ( i = 0 ; i < 101 ; i++)
    {
        *(Zeile + i) = '\0';
    }
    //free(Zeilenanfang);
    return 0;
}

//  --------------------------------------------------------------------------------
//  Oeffnet bei Start die angegebene Datei und ruft für alle Appointments
//  innerhalb der <Calender> Tags loadAppointment auf.
//  --------------------------------------------------------------------------------
int loadCalendar()
{
char Zeile[100];
char *Zeilenanfang;
//*Zeile = '\0';
FILE *Load = fopen( "calendar.xml", "r");
if(!Load)
    {
        fprintf(stderr, "Die Datei konnte nicht geoeffnet werden.\n");
        return 0;
    }

if (Load)
    {
    fgets(Zeile, 100, Load);
    if ( strncmp(Zeile, "<Calendar>", 10) == 0)         //Anfang eines XML Dokuments
        {
            do
            {
            fgets(Zeile, 100, Load);

            Zeilenanfang = Zeile;

            while ((*Zeilenanfang == ' ') || (*Zeilenanfang == 9))
            Zeilenanfang++;

                if ( strncmp(Zeilenanfang, APPOINTMENT, 13) == 0)
                {
                loadAppointment(Load);

                    if (feof(Load))
                        {
                            printf("EOF\n");
                            fclose(Load);
                            return 0;
                        }
                }
            }while(strncmp(Zeile, "</Calendar>", 11) != 0);
        }
    }
    fclose(Load);
    return 1;
}

//  --------------------------------------------------------------------------------
//  schreibt ein Appointment aus dem Kalender in XML in die angegebene Datei
//  --------------------------------------------------------------------------------
int saveAppointment(FILE * Save, int indexOfAppointment)
{
fprintf(Save, " <Appointment>\n");
fprintf(Save, "  <Date>%02i.%02i.%04i</Date>\n", calendar[indexOfAppointment].DateOfAppointment.Day, calendar[indexOfAppointment].DateOfAppointment.Month, calendar[indexOfAppointment].DateOfAppointment.Year);
fprintf(Save, "  <Time>%02i:%02i:%02i</Time>\n", calendar[indexOfAppointment].TimeOfAppointment.Hour, calendar[indexOfAppointment].TimeOfAppointment.Minute, calendar[indexOfAppointment].TimeOfAppointment.Second);
fprintf(Save, "  <Description>%s</Description>\n", calendar[indexOfAppointment].Beschreibung);
fprintf(Save, "  <Location>%s</Location>\n", calendar[indexOfAppointment].Location);
fprintf(Save, "  <Duration>%02i:%02i</Duration>\n", calendar[indexOfAppointment].Duration->Hour, calendar[indexOfAppointment].Duration->Minute);
fprintf(Save, " </Appointment>\n");
return 0;
}

//  --------------------------------------------------------------------------------
//  Oeffnet oder erstellt Sicherungsdatei (die überschrieben wird)
//  ruft für alle gespeicherten Appointments saveAppointment auf.
//  --------------------------------------------------------------------------------
int saveCalendar()
{
int i;
FILE *Save = fopen( "calendar2.xml", "w");
if (Save)
    {
    fprintf(Save, "<Calendar>\n");
    for(i = 0; i < countAppointments ; i++)
        {
        saveAppointment(Save, i);
        }
    }
    fprintf(Save, "</Calendar>");
    fclose(Save);
    return 1;
}

/*
char extractLineContent(char * Line, char *Tag, char *endTag)
{
    int Len = 0;
    int TagLength = strlen(Tag);
    int endTagLength = TagLength+1;

    if ( strncmp( Line, Tag, TagLength) == 0)                               //Wenn Zeile und angegebenes Tag uebereinstimmen
    {
        Len = strlen(Line);
        Len -= TagLength;
        Len -= endTagLength;
        Len--;
        if ( strncmp((Line + TagLength + Len), endTag, endTagLength) == 0) //ist ein Ende Tag vorhanden?
        {
            lineContent = calloc( Len + 1, sizeof(char));
            if (lineContent)
                strncpy(lineContent, (Line + TagLength), Len);              //schreibe Inhalt der Zeile
        }
        else
        {
            lineContent = "";                                                  // setze  - falls leeres Feld
        }
    }
    return lineContent;
}
*/
