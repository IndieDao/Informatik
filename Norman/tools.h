#pragma once
#include <string.h>
#include "datastructure.h"
#include "datetime.h"

char ToUpper(char c1);
void clearBuffer();
void waitForEnter();
void clearScreen();
int askYesOrNo();
void printLine(char c, int count);
int getText(char *prompt, int maxlen, char **str, int blank);

void printAppointment(TAppointment * app);
