#ifndef TOOLS_H
   #define TOOLS_H

void printFrame();
short getNumber(int);
void printInputNumber(int, short);

char getOperator();
void printInputOperator(char);
short calcResult(short, short, char);
void printResultNumber(int, short);
void printBinary(int, short);
void printResultOperator(char);
int askAgain();
void clearBuffer();

#endif
