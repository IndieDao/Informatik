#pragma once
#include "datastructure.h"

//typedef int(*Cmp)(TDate*, TDate*, int);
//typedef int(*SwapDate)(TDate*, TDate*);

int partition(TAppointment * cal, int ui, int oi, int(*CmpFunc)(TAppointment *, TAppointment *, int), void(*SwapDate)(TAppointment *, TAppointment *),  int asc);

void Qsort(TAppointment * cal, int ui, int oi, int(*Cmp)(TAppointment *, TAppointment *, int), void(*SwapDate)(TAppointment *, TAppointment *), int asc);

void QuickSort(TAppointment * cal, int amount, int(*Cmp)(TAppointment *, TAppointment *, int), void(*SwapDate)(TAppointment *, TAppointment *), int asc);
