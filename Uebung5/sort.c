#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
#include <string.h>
#include "escapesequenzen.h"

void Tausche(int *D1, int *D2)
{
    int temp;
    temp = *D2;
    *D2= *D1;
    *D1=temp;
}

int partition( int *A, int ui, int oi )
{
    int i = ui+1, j = oi;
    int *comp = A+ui;
    while(i <=j)
    {
        while((i<=j)&&(*(A+i)<= *comp))
        i++;
        while ((j>=i) &&(*(A+j)>= *comp))
        j--;
        if(i<j)
        {
            Tausche(A+i, A+j);
            i++;
            j--;
        }
    }
    i--;
    Tausche(A+i, comp);
    return i;
}

void Qsort (int *A, int ui, int oi)
{
int idx;
    if(ui >=oi)
        return;
    idx = partition(A, ui, oi);
    Qsort(A, ui, idx-1);
    Qsort(A, idx+1, oi);
}

void Quicksort(int *A, int Anz)
{
    Qsort(A,0, Anz-1);
}
