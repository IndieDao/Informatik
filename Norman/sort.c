#include "sort.h"

int partition(TAppointment *cal, int ui, int oi, int(*CmpFunc)(TAppointment *, TAppointment *, int ),void(*SwpFunc)(TAppointment *, TAppointment*), int asc)
{
	int i = ui, j = oi;       // Laufindizes
	//int temp;                 // fuer Austausch zweier Elemente
	TAppointment comp = *(cal + ui); // Vergleichselement (Schranke)

	while (i <= j)
	{
		// naechstes Element > comp von links suchen (im linken Teil)
		while ((i <= j) && CmpFunc(cal + i, &comp, asc) <= 0)
			i++;
		// naechstes Element < comp von rechts suchen (im rechten Teil)
		while ((j >= i) && CmpFunc(cal + j, &comp, asc) >= 0)
			j--;
		if (i < j)
		{
			SwpFunc(cal + i, cal + j);
			i++;
			j--;
		}
	}
	i--;

	SwpFunc(cal + ui, cal + i);

	return i;
}

void Qsort(TAppointment *cal, int ui, int oi, int(*CmpFunc)(TAppointment *, TAppointment *, int), void(*SwpFunc)(TAppointment *, TAppointment*), int asc)
{
	int idx;      // Schranke einer Zerlegung

	if (ui >= oi) // Abbruchbedingung der Rekursion
		return;
	else
	{
		idx = partition(cal, ui, oi, CmpFunc, SwpFunc, asc);
		Qsort(cal, ui, idx - 1, CmpFunc, SwpFunc, asc); // linken Teil rekursiv sortieren
		Qsort(cal, idx + 1, oi, CmpFunc, SwpFunc, asc); // rechten Teil rekursiv sortieren
	}
}



void QuickSort(TAppointment *cal, int amount, int (*CmpFunc)(TAppointment *, TAppointment *, int), void (*SwpFunc)(TAppointment *, TAppointment*), int asc)
{
	Qsort(cal, 0, amount - 1, CmpFunc, SwpFunc, asc);
}

