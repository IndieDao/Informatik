#ifndef SORT_H_
#define SORT_H_
#include "calendar.h"
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "tools.h"
#include "menu.h"
#include "timedate.h"
#include "escapesequenzen.h"

void QuickSort(TAppointment**calArray, int Anzahl, int (*cmp)(const void*, const void*), void (*exchange)(TAppointment*, TAppointment*));

#endif
