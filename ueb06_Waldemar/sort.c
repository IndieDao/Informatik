#include "sort.h"
#include "calendar.h"
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "tools.h"
#include "menu.h"
#include "timedate.h"
#include "escapesequenzen.h"


int partition(TAppointment **Array, int ui, int oi, int (*cmp)(const void*, const void*), void (*exchange)(TAppointment*, TAppointment*))
{
    int i = ui, j = oi;

    TAppointment *comp = *(Array + ui);

    while (i <= j)
    {

        while (i <= j && cmp( *(Array+i), comp ) <= 0)
            i++;

        while (j >= i && cmp( *(Array+j), comp ) >= 0)
            j--;
        if (i < j)
        {
            exchange(*(Array+i), *(Array+j));
            i++;
            j--;
        }
    }

    i--;

    exchange(*(Array+ui), *(Array+i));

    return(i);
}


void cracksort(TAppointment **Array, int ui, int oi, int (*cmp)(const void*, const void*), void (*exchange)(TAppointment*, TAppointment*))
{
    int idx;
    if (ui >= oi)
        return;
    else
    {
        idx = partition(Array, ui, oi, cmp, exchange);
        cracksort(Array, ui, idx-1, cmp, exchange);
        cracksort(Array, idx + 1, oi, cmp, exchange);
    }
}


void QuickSort(TAppointment**calArray, int Anzahl, int (*cmp)(const void*, const void*), void (*exchange)(TAppointment*, TAppointment*))
{
    cracksort(calArray, 0, Anzahl - 1, cmp, exchange);
}

