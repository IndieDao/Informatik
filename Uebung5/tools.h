#ifndef TOOLS_H_INCLUDED
   #define TOOLS_H_INCLUDED
#define MAX_APPOINTEMENTS 100
char *tmpToken(char *Eingabe, char Token);
void waitForEnter();
void printLine(char Zeichen, int Anzahl);
int askAgain(char *);
void clearBuffer();
void clearScreen();
int getText(char *, char **, unsigned int, int AllowEmpty); // Prompt = Eingabeaufforderung, Bool = 1 oder 0 -> Wahrheitswert

void falscheEingabe();


#endif
