#include <string.h>
#include "menu.h"
#include "tools.h"

int getMenu(char *menutitle, char **menuentries, int entrycount) {
	int ret = 0;
	do {
		clearScreen();
		printf("%s\n", menutitle);

		printLine('=', strlen(menutitle));

		int count = 1;
		while (count <= entrycount) {
			printf("[%i] %s\n", count, *(menuentries + count - 1));
			count++;
		}

		printf("\nBitte treffen Sie Ihre Auswahl: ");

		while (scanf("%i", &ret) <= 0 && (ret<1 && ret>entrycount)) {
			while (getchar() != '\n');
		}


	} while (ret <1 && ret>entrycount);

	clearBuffer();

	return ret;
}