#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getText(const char * myStr, const int TxtLaenge, char **InputTxt, int Leer);

void clearBuffer();

int askYesOrNo(char *Question);

void waitForEnter();

void clearScreen();

void printLine(const char elem, int length);

int fakultaet(int x);

char *toFilename(char *date);
void textBLUE(int i);
void seekNewLineFILE(FILE * fp);


#endif
