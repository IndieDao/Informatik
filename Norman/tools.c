#include <stdio.h>
#include "tools.h"

char ToUpper(char c1)
{
	if ((c1 > 96) && (c1 < 122))
		return (c1 - 32);

	else if ((c1 < 96) && (c1 > 122))
		return (c1);

	return 0;
}

void clearBuffer() {
	while (getchar() != '\n');
};

void waitForEnter() {
	printf("\nBitte geben Sie ENTER ein.\n");
	clearBuffer();
};

int AskForOrder() {
	printf("Bitte wählen Sie die Sortierreihenfolge\n");
	printf("1. Aufsteigend\n");
	printf("2. Absteigend\n");

	int inp;
	int valid = 0;
	do
	{
		printf("Ihre Wahl: \n");
		valid = scanf("%i", &inp);
		clearBuffer();
	} while ((inp != 1 || inp != 2) && !valid);

	return inp;
};

void clearScreen() {
	system("cls");
};
int askYesOrNo() {
	char c1;
	int valid = 0;
	do
	{
		printf("| Moechten Sie noch einmal  j / n?  |\n");
		valid = scanf("%c", &c1);
		clearBuffer();
		c1 = ToUpper(c1);
	} while ((c1 != 'J' || c1 != 'N') && !valid);

	if (c1 == 'J')
		return 1;

	return 0;
};

void printLine(char c, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		printf("%c", c);
	}

	printf("\n");
}

int getText(char *prompt, int maxlen, char **str, int mandatory) {
	printf(prompt);

	char *input = (char*)malloc(maxlen);

	scanf("%s", input);

	clearBuffer();

	if (strlen(input) == 0 && mandatory) {
		free(input);
		printf("Bitte geben Sie eine Zeichenkette ein, die mindestens 1 Zeichen und höchstens %i Zeichen lang ist!\n", maxlen);
		return 0;
	}

	*str = (char*)malloc(strlen(input));
	strcpy(*str, input);

	free(input);

	return 1;
}

void printAppointment(TAppointment *app) {
	char descshort[49];
	memset(descshort, '\0', 49);

	if (app->description == NULL)
		return;

	printTime(&app->time);
	printf(" - ");

	TTime addedtime = addTime(&app->time, app->duration);

	printTime(&addedtime);
	

	if (strlen(app->location) == 0)
		printf(" -> (kein Ort)");
	else
		printf(" -> %s", app->location);

	if (strlen(app->description) > 44) {
		strncpy(descshort, app->description, 44);
		strcat(descshort, " ...");
	}
	else {
		strcpy(descshort, app->description);
	}

	printf(" | %s", descshort);
	//printTime(app->duration);
	//printf(" Stunden)\n");

}

