#include "datetime.h"
#include "tools.h"

TTime addTime(TTime *t1, TTime *t2) {

	TTime time;

	if (t1->hour + t2->hour >= 24) {
		time.hour = t1->hour + t2->hour - 24;
	}
	else {
		time.hour = t1->hour + t2->hour;
	}


	if (t1->minute + t2->minute >= 60) {
		time.hour++;
		time.minute = t1->minute + t2->minute - 60;
	}
	else {
		time.minute = t1->minute + t2->minute;
	}

	if (t1->second + t2->second >= 60) {
		time.minute++;
		time.second = t1->second + t2->second - 60;
	}
	else {
		time.second = t1->second + t2->second;
	}

	return time;
}

int getDate(char * prompt, TDate *date)
{
	char input[11];

	printf(prompt);

	scanf("%s", input);

	clearBuffer();

	return getDateFromString(input, date);
}

int getTime(char * prompt, TTime *time, int nonzero)
{
	char input[10];

	printf(prompt);

	scanf("%s", input);

	clearBuffer();

	return getTimeFromString(input, time, nonzero);
}

int isLeapYear(int *year) {
	if ((*year % 400) == 0)
		return 1;
	else if ((*year % 100) == 0)
		return 0;
	else if ((*year % 4) == 0)
		return 1;

	return 0;
}

int isDateValid(TDate *Date) {

	// month with 31 days
	if (Date->month == 1 || Date->month == 3 || Date->month == 5
		|| Date->month == 7 || Date->month == 8 || Date->month == 10
		|| Date->month == 12) {

		if (Date->day > 31 && Date->day < 1)
			return 0;
	}

	// months with 30 days
	else if (Date->month == 4 || Date->month == 6 || Date->month == 9
		|| Date->month == 11) {
		if (Date->day > 30 && Date->day < 1)
			return 0;
	}
	else if (Date->month == 2) {
		// years with 29 or 28 days in february
		if (isLeapYear(&Date->year)) {
			if (Date->day <= 29 && Date->day >= 1)
				return 1;
			else
				return 0;
		}
		else {
			if (Date->day <= 28 && Date->day >= 1)
				return 1;
			else
				return 0;
		}
	}
	else return 0;

	return 1;
}

// prove valid Input and get input from user
int getDateFromString(char* Input, TDate *Date) {
	int i;
	int numdots = 0;
	int dotpos = 0;

	// set Date = 0

	Date->day = 0;
	Date->month = 0;
	Date->year = 0;

	// get Input with loop
	for (i = 0; i < 20; i++) {

		// prove number of dots
		if (Input[i] == '.') {
			numdots++;
			dotpos = i;
			continue;
		}
		// if no dot set get input to int and at day
		if (numdots == 0) {
			Date->day = atoi(Input);

			// if one dot set get input to int and at month
		}
		else if (numdots == 1) {
			Date->month = atoi(Input + dotpos + 1);

			// if two dots set get input to int and at year
		}
		else if (numdots == 2) {
			Date->year = atoi(Input + dotpos + 1);

		}
		else {
			return 0;
		}
	}

	int y = Date->year % 1000 % 100;
	int c = Date->year / 100;

	int m = Date->month - 2;
	if (Date->month == 1)
		m = 11;
	else if (Date->month == 2)
		m = 12;

	// for for months jan and feb
	if (Date->month == 1 || Date->month == 2) {
		if (c != 0)
			c--;

		if (y != 0)
			y--;
		else
			y = 99;
	}

	// calc our weekday
	Date->weekday = (Date->day + floor(2.6 * m - 0.2) + y + floor(y / 4) + floor(c / 4) - 2 * c);
	Date->weekday %= 7;

	// fix for sundays
	if (Date->weekday == 0)
		Date->weekday = 7;

	// prove if Date is valid
	if (isDateValid(Date) == 1)
		return 1;
	else
		return 0;
}

// prove if time is valid
int isTimeValid(TTime *Time, int nonzero) {
	// validate hour
	if (Time->hour < 0 || Time->hour > 23) {
		return 0;
	}

	// validate minute
	if (Time->minute < 0 || Time->minute > 59) {
		return 0;
	}

	// validate seconds
	if (Time->second < 0 || Time->second > 59) {
		return 0;
	}

	if (nonzero) {
		if (Time->hour == 0 && Time->minute == 0 && Time->second == 0)
			return 0;
	}

	return 1;

}

// get string from input and prove if valid
int getTimeFromString(char *Input, TTime *Time, int nonzero /*indicates if nonzero time values are allowed*/) {
	int i;
	int numdots = 0;
	int separatorpos = 0;

	// set time = 0
	Time->hour = 0;
	Time->minute = 0;
	Time->second = 0;

	// read and save time with loop
	for (i = 0; i < 20; i++) {

		// prove numbers of dots
		if (Input[i] == ':' || Input[i] == '.') {
			numdots++;
			separatorpos = i;
			continue;
		}
		// if no dot set get input to int and at hour
		if (numdots == 0) {
			Time->hour = atoi(Input);

			// if one dot set get input to int and at minute
		}
		else if (numdots == 1) {
			Time->minute = atoi(Input + separatorpos + 1);

			// if two dots set get input to int and at seconds
		}
		else if (numdots == 2) {
			Time->second = atoi(Input + separatorpos + 1);

		}
		else {
			return 0;
		}
	}
	// prove if time is valid
	if ((isTimeValid(Time, nonzero)) == 1)
		return 1;
	else
		return 0;
}

void printDOW(TDate *date) {
	switch (date->weekday) {
	case  0:printf("Kein Tag"); break;
	case  1:printf("Mo"); break;
	case  2:printf("Di"); break;
	case  3:printf("Mi"); break;
	case  4:printf("Do"); break;
	case  5:printf("Fr"); break;
	case  6:printf("Sa"); break;
	case  7:printf("So"); break;
	default:
		printf("Ungültige Tagesangabe"); break;
	}
}

void printDate(TDate *date) {
	printf("%0.2i.%0.2i.%0.4i", date->day, date->month, date->year);
}

void printTime(TTime *time) {
	printf("%0.2i:%0.2i:%0.2i", time->hour, time->minute, time->second);
}

int sameDate(TDate *d1, TDate *d2) {
	if (d1->day == d2->day && d1->month == d2->month &&  d1->year == d2->year)
		return 1;
	else
		return 0;
}