#ifndef TOOLS_H
   #define TOOLS_H

void printInputMask();

int Strlen(char *str);

void getText(unsigned char *text);

int countInAscii(unsigned char *text, unsigned int *anzahl);

void printCounted(unsigned int *counted, int stringlaenge);

int askAgain();
void clearBuffer();
#endif
