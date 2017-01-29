#pragma once
#include "datastructure.h"
#include "tools.h"
#include "calendar.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"

int saveCalendar(TAppointment *calendar, int numentries);
int saveAppointment(TAppointment *app, FILE *Datei);
int loadCalendar(TAppointment *calendar, int maxentries);
int loadAppointment(TAppointment *app, FILE *Datei);