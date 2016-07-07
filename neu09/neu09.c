#include <stdio.h>
#include"escapesequenzen.h"
#include "matrix.h"
#include "tools.h"
//#define MaxRows 5
//#define MaxColumns 5

int main()
{
    int Matrix1[MaxRows][MaxColumns];
    int Matrix2[MaxRows][MaxColumns];
    int (MatrixResult[MaxRows][MaxColumns]);
    int RowCount1, ColCount1;
    int RowCount2, ColCount2;
    int RowCountResult, ColCountResult;
   
    do
    {
        CLEAR;
        HOME;

        RowCount1 = getNumberOfRows(1, 1, 1);
        ColCount1 = getNumberOfColumns(2, 1, 1);
        getMatrix(4,1, RowCount1, ColCount1, Matrix1);


        RowCount2 = ColCount1;
        ColCount2 = getNumberOfColumns((5 + RowCount1), 1, 2);
        getMatrix(7 + RowCount1, 1, RowCount2, ColCount2, Matrix2);
        

        RowCountResult = RowCount1;
        ColCountResult = ColCount2;
        calcMatrix(RowCount1, ColCount1, ColCount2, Matrix1, Matrix2, MatrixResult);

        CLEAR;
        HOME;
        printMatrix(1, 1, RowCount1, ColCount1, Matrix1);
        POSITION((RowCount1 + RowCount2) / 4+1, ColCount1 * 7+5);
        printf("*");
        printMatrix(1, ColCount1 * 7 +9, RowCount2, ColCount2, Matrix2);
        POSITION((RowCount1 + RowCount2) / 4+1, (ColCount1 + ColCount2) * 7 +13);
        printf("=");
        printMatrix(1, (ColCount1+ColCount2) * 7 + 17, RowCountResult, ColCountResult, MatrixResult);

    }while (askAgain(2+((RowCount1>RowCount2) ? RowCount1 : RowCount2), 1));
    CLEAR;
    HOME;
    printf("bye bye! \n\n");
    return 0;
}
