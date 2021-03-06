#include <stdio.h>
#include "escapesequenzen.h"
#include "matrix.h"
#include "tools.h"

const int MaxRows = 5;
const int MaxColumns = 5;

static void getNumber(int Row, int Col, int *number);


int getNumberOfRows(int Row, int Col, int MatrixNo)
{
  int number;
  POSITION(Row,Col);
  printf("Geben Sie bitte die Zeilenanzahl  der %i. Matrix ein (1..%i): ", MatrixNo, MaxRows);

  getNumber(Row, 62, &number);
  while( (number < 1) || (number > MaxRows))
  {
    getNumber(Row, 62, &number);
  }

  return number;
}


int getNumberOfColumns(int Row, int Col, int MatrixNo)
{
  int number;
  POSITION(Row,Col);
  printf("Geben Sie bitte die Spaltenanzahl der %i. Matrix ein (1..%i): ", MatrixNo, MaxRows);

  getNumber(Row,62,&number);
  while( (number < 1) || (number > MaxColumns) )
  {
    getNumber(Row, 62, &number);
  }

  return number;
}


void getMatrix(int Row, int Col, int RowCount, int ColCount, int Matrix[MaxRows][MaxColumns])
{
  int i,j,k;

  for(i = 0; i < RowCount; i++)
  {
    POSITION( (Row+i),(Col));
    CLEAR_LINE;
    printf("| ");
    for(j = 0; j < ColCount; j++)
    {
      printf("---- ");
    }
    printf("|\n");
  }

  for(i = 0; i < RowCount; i++)
  {
    for(j = 0; j < ColCount; j++)
    {
      POSITION( (Row + i),(Col + 2 + (5*j)) );
      while( !(scanf("%i", &Matrix[i][j])) )  //Einlesen aktuelles Element
      {  //Bei Falscheingabe:
	POSITION( (Row + i),Col );
	printf("| ");
	for (k = 0; k < j; k++)  //Neuschreiben der bisherigen Eingaben der Zeile
	{
	  printf("%4i ", Matrix[i][k]);
	}
	for (k = k; k < ColCount; k++)  //Neuschreiben der Platzhalter für einzuschreibende Elemente der Zeile
	{
	  printf("---- ");
	}
	printf("|");
	clearBuffer();
	POSITION( (Row + i),(Col + 2 + (5 * j)) );  //Zurück an Position aktuell einzulesenden Elements springen
      }
      POSITION( (Row + i),(Col + 2 + (5 * j)) );
      printf("%4i", Matrix[i][j]);
    }
  }
}


void calcMatrix(int RowCount1, int ColCount1, int ColCount2, int M1[MaxRows][MaxColumns], int M2[MaxRows][MaxColumns], int MErg[MaxRows][MaxColumns])
{
  int aktRowErg,aktColErg,aktCol1Row2;
  for (aktRowErg = 0; aktRowErg < RowCount1; aktRowErg++)
  {
    for (aktColErg = 0;aktColErg < ColCount2; aktColErg++)
    {
      MErg[aktRowErg][aktColErg] = 0;  //Nullen des aktuellen Eintrages der Ergebnismatrix
      for (aktCol1Row2 = 0; aktCol1Row2 < ColCount1; aktCol1Row2++)
      {
	MErg[aktRowErg][aktColErg] = MErg[aktRowErg][aktColErg] + (M1[aktRowErg][aktCol1Row2] * M2[aktCol1Row2][aktColErg]);
      }
    }
  }
}


void printMatrix(int Row, int Col, int RowCount, int ColCount, int Matrix[MaxRows][MaxColumns])
{
  int i,j;
  

  for (i = 0; i < RowCount; i++)
  {
    POSITION( (Row+i),Col);
    printf("| ");
    for (j = 0; j < ColCount; j++)
    {
      printf("%4i ", Matrix[i][j]);
    }
    printf("|");
  }
}



static void getNumber(int Row, int Col, int *number)
{
  POSITION(Row,Col);
  printf("           ");
  POSITION(Row,Col);
  while ( !(scanf("%i",number)) )
  {
    clearBuffer();
    POSITION(Row,Col);
    printf("           ");
    POSITION(Row,Col);
  }
}
