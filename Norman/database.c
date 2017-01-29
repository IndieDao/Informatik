#include "database.h"

// function to save calendar in file with start and end indentification
int saveCalendar(TAppointment *calendar, int numentries) {
	int i = 0;

	// create textfile "appsave" in writemode
	FILE *CalFile = fopen("calendar.xml", "wt");
	if (CalFile) {
		fprintf(CalFile, "<calendar>\n");
		while (i < numentries)
		{
			saveAppointment(&calendar[i], CalFile);
			i++;
		}
		fprintf(CalFile, "</calendar>\n");
		fclose(CalFile);

		return 1;
	}
	else return 0;
}

// save appointment in file with start and end indification for every structure
int saveAppointment(TAppointment *app, FILE *Datei) {
	fprintf(Datei, "<Appointment>\n");
	fprintf(Datei, "<Date>%02i.%02i.%04i</Date>\n", app->date.day, app->date.month, app->date.year);
	fprintf(Datei, "<Time>%02i:%02i:%02i</Time>\n", app->time.hour, app->time.minute, app->time.second);
	fprintf(Datei, "<Description>%s</Description>\n", app->description);

	if (app->location) {
		fprintf(Datei, "<Location>%s</Location>\n", app->location);
	}
	if (app->duration) {
		fprintf(Datei, "<Duration>%02i:%02i:%02i</Duration>\n", app->duration->hour, app->duration->minute, app->duration->second);
	}
	fprintf(Datei, "</Appointment>\n");

	return 1;
}

int GetValues(char *str, char *tag, char *value) {
	memset(tag, '\0', 20);
	memset(value, '\0', 255);

	char endtag[20];

	int hasbegintag = 0, hasendtag = 0, herecomesthedata = 0;

	int i;
	int ccnt = 0;

	for (i = 0; i < 300; i++) {
		if (str[i] == '<') { // begin tag
			if (herecomesthedata) {
				herecomesthedata = 0;
				value[ccnt + 1] = '\0';
				ccnt = 0;
			}

			ccnt = 0;
		}
		else if (str[i] == '>') { // closing tag
			if (!hasbegintag) {
				hasbegintag = 1;
				herecomesthedata = 1;
				ccnt = 0;
			}
			else if (!hasendtag)
				hasendtag = 1;
		}
		else if (str[i] == '/') { // end tag
			ccnt = 0;
			endtag[ccnt] = str[i];
			ccnt++;
		}
		else if (str[i] == '\0') { // EOL
			if (strlen(tag) > 0)
				return 1;
			else return 0;
		}
		else // inc tag
		{
			if (!hasbegintag) {
				tag[ccnt] = str[i];
				ccnt++;
			}
			else if (herecomesthedata) {
				value[ccnt] = str[i];
				ccnt++;
			}
			else {
				endtag[ccnt] = str[i];
				ccnt++;
			}
		}

	}

	return 0;
}

// load all appointments in right order, return 0 on error or num of loaded entries on success
int loadCalendar(TAppointment *calendar, int maxentries) {
	int appcnt = 0;

	char line[255];
	char lasttag[20] = "", lastvalue[255];

	FILE *calfile = fopen("calendar.xml", "rt");

	if (calfile) {
		do {
			fgets(line, 255, calfile);
			line[strlen(line) - 1] = '\0';


			GetValues(line, lasttag, lastvalue);
			if (strcmp(lasttag, "Appointment") == 0) { // neues appointmrnt
				if (loadAppointment(calendar + appcnt, calfile)) {
					appcnt++;
				}
			}

			if (strcmp(lasttag, "/Calendar") == 0) { // neues appointmrnt
				return appcnt;
			}
		} while (!feof(calfile) && appcnt < maxentries);
		
		return appcnt;
	}
	else {
		printf("Es wurde keine Kalenderdatei gefunden.");
		return 0;
	}
}

int loadAppointment(TAppointment *app, FILE * Datei)
{
	char line[300];
	char lasttag[20] = "", lastvalue[255];

	fgets(line, 255, Datei);
	line[strlen(line) - 1] = '\0';

	// temp appointment init
	TAppointment tmpApp;
	tmpApp.description = (char*)malloc(255);
	memset(tmpApp.description, '\0', 255);

	tmpApp.location = (char*)malloc(255);
	memset(tmpApp.location, '\0', 255);

	tmpApp.duration = (TTime*)malloc(sizeof(TTime));

	getTimeFromString("00:00:00", &tmpApp.time, 0);
	getTimeFromString("00:00:00", tmpApp.duration, 0);
	getDateFromString("01.01.1970", &tmpApp.date);

	// examine the string
	while (GetValues(line, lasttag, lastvalue) == 1 && lasttag != "/Appointment") {

		if (strcmp(lasttag, "Date") == 0) {
			if (!getDateFromString(lastvalue, &tmpApp.date)) {
				printf("Beim Laden des Termins trat ein Fehler auf: Das Datum konnte nicht gelesen werden oder war ungültig.\n");
			}
		}
		else if (strcmp(lasttag, "Time") == 0) {
			if (!getTimeFromString(lastvalue, &tmpApp.time, 0)) {
				printf("Beim Laden des Termins trat ein Fehler auf: Die Uhrzeit konnte nicht gelesen werden oder war ungültig.\n");
			}
		}
		else if (strcmp(lasttag, "Duration") == 0) {
			if (!getTimeFromString(lastvalue, tmpApp.duration, 0)) {
				printf("Beim Laden des Termins trat ein Fehler auf: Die Dauer konnte nicht gelesen werden oder war ungültig.\n");
			}
		}
		else if (strcmp(lasttag, "Description") == 0) {
			strcpy(tmpApp.description, lastvalue);
		}
		else if (strcmp(lasttag, "Location") == 0) {

			strcpy(tmpApp.location, lastvalue);
		}

		// read from our db file
		fgets(line, 255, Datei);
		line[strlen(line) - 1] = '\0';
	}

	*app = tmpApp;
	return 1;
}
