#include <stdio.h>

#include "escapesequenzen.h"
#include "tools.h"

void clearBuffer()
{
  char foo;
  do
  {
    scanf("%c",&foo);
  } while (foo != '\n');
}


int askAgain(int Row, int Col)
{
  char usrInputChar = 'a';


  while ( (usrInputChar != 'j') && (usrInputChar != 'n' ) && (usrInputChar != 'J') && (usrInputChar != 'N' ) )  //Bei Falscheingabe der yes/no-Abfrage
  {
    POSITION( (Row-1) ,Col);
    CLEAR_LINE;
    printf("Moechten Sie noch einmal (j/n)? ");
    clearBuffer();
    POSITION( (Row-1) , 33);
    scanf("%c",&usrInputChar);
  }
  clearBuffer();
  switch (usrInputChar)
  {
    case 'j': return 1;
    case 'J': return 1;
    case 'n': return 0;
    case 'N': return 0;
  } 
  printf("Serious input error\n");
  return 0;
}
