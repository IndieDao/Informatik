#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"


void insertInDList( TAppointment * newApp, int (*cmp)(const void*, const void*));

TAppointment * removeFromDList( TAppointment * delApp, int (*cmp)(const void*, const void*));

#endif
