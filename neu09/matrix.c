#include <stdio.h>
#include "escapesequenzen.h"
#include "matrix.h"
#include "tools.h"

const int MaxRows = 5; 
const int MaxColumns = 5;

static  int  i, j, k, l = 0;

//  Eingabe-Abfrage
void getNumber(int Row, int Col, int *number) 
{
    POSITION (Row, Col);
    while(!scanf("%i", number))
    {
        clearBuffer();
        POSITION (Row, Col);
        printf("                                                                         ");
        POSITION (Row, Col);
    }
}

//Abfrage Anzahl der Matrix-Reihen

int getNumberOfRows(int Row, int Col, int MatrixNo)
{
    int number;
    POSITION(Row, Col);
    printf("Geben Sie bitte die Zeilenanzahl der %i. Matrix ein (1...%i):____", MatrixNo, MaxRows);
    getNumber(Row, 62, &number);
    while( number < 1 || number > MaxRows)
    {
        getNumber(Row, 62, &number); 
    }

   return number;
}

//Abfrage Anzahl der Matrix-Spalten

int getNumberOfColumns(int Row, int Col, int MatrixNo)
{
    int number;
    POSITION(Row, Col);
    printf("Geben Sie bitte die Spaltenzahl  der %i. Matrix ein (1...%i):____", MatrixNo, MaxRows);
    getNumber(Row, 62, &number);
   while( number < 1 || number > MaxColumns)
    {
        getNumber(Row, 62, &number); 
    }

   return number;
}

//Befuellen der Matrix

    //leere Matrix zeichnen
    void drawEmptyMatrix(int x, int y, int Row, int Col, int RowCount, int ColCount)
    {
    for(k=x; k < RowCount ; k++)
        {

        POSITION((Row+k),Col);
        printf("|");
            for (l=y; l < ColCount; l++)
            {     
            POSITION((Row+k),(Col+1+(7*l)));
            CLEAR_LINE;
            BACKCOLOR_BLUE;
            printf(" ---- ");
            ATTRIBUTE_OFF;
            }
        printf("|");
        }
    }


void getMatrix(int Row, int Col, int RowCount, int ColCount, int Matrix[MaxRows][MaxColumns])
{
    drawEmptyMatrix(0,0, Row, Col, RowCount, ColCount );
    //Zahlenabfrage
  
    for(i=0; i < RowCount; i++)
    {
        for (j = 0; j < ColCount; j++)
        {

            BACKCOLOR_BLUE;
            POSITION((Row+i),(Col+3 + (7*j)));
            while(!scanf("%i", &Matrix[i][j]) || Matrix[i][j] <= -1000
                                              || Matrix[i][j] >= 10000 )
            {
                drawEmptyMatrix(i, j, Row, Col, RowCount, ColCount ); 
                clearBuffer();
                ATTRIBUTE_OFF;
                POSITION((Row + i), Col+3+(7*j));
                BACKCOLOR_BLUE;
            }
            POSITION((Row + i), Col + 2 +(7*j));
            printf("%4i", Matrix[i][j]);
            ATTRIBUTE_OFF;
        }
    }
}


void calcMatrix(int RowCount1, int ColCount1, int ColCount2, int M1[MaxRows][MaxColumns], int M2[MaxRows][MaxColumns], int MErg[MaxRows][MaxColumns])
{
    int sum;

     for (i = 0; i < RowCount1; i++)

     {
           for (j = 0; j < ColCount2; j++)
           {
                  sum = 0;
                  for (k = 0; k < ColCount1; k++) 
                  {
                         sum = sum + M1[i][k]*M2[k][j];
                  }
                  MErg[i][j] = sum;
            }
      }
}

void printMatrix(int Row, int Col, int RowCount, int ColCount, int Matrix[MaxRows][MaxColumns])
{
drawEmptyMatrix(0,0, Row, Col, RowCount, ColCount);


    for(i=0; i < RowCount; i++)
    {
        for (j = 0; j < ColCount; j++)
        {

            BACKCOLOR_BLUE;
            POSITION((Row + i), Col + 2 +(7*j));
            printf("%4i",Matrix[i][j]);
            ATTRIBUTE_OFF;
        }
    }
}
