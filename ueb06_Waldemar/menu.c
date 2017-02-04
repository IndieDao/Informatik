#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"


int getMenu(const char *title, const char **menuset, int menuCount)
{
	int i;
	int valid = 0;
	int Input = 0;
	char inputBuff[20];

	do
	{
		clearScreen();
		memset(inputBuff, 0, 20);
		printf("%s\n", title);
		printLine('=', strlen(title));

		for ( i=0; i < menuCount; i++)
		{
			printf("%s\n", menuset[i]);
		}

		printf("\n");

		printf("Ihre Wahl: ");
		valid = scanf("%19[^\n]", inputBuff);
		clearBuffer();

		if (valid)
		{

			Input = atoi(inputBuff);

			if (Input > 0 && Input <= menuCount)
			{
				break;
			}
			else
			{
                printf("Eingabe nicht korrekt\n");
            }
		}

	} while (!valid);

	return Input;
}
