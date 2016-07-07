#ifndef TOOLS_H
  #define TOOLS_H TOOLS_H

  extern void clearBuffer();
  extern void countCharsPerType(unsigned char *ascii, int *anz, int *charCount);
  extern int getString(unsigned char *ascii);
  extern void clearArray(int * countPointer, int size);

#endif
