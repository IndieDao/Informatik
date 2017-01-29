#pragma once
#include "datetime.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "datetime.h"
#include "sort.h"
#include "tools.h"

void SwapAppointment(TAppointment * app1, TAppointment * app2);

int CmpAppDate(TAppointment * app1, TAppointment * app2, int asc);

int CmpAppDesc(TAppointment * app1, TAppointment * app2, int asc);

int CmpAppLoc(TAppointment * app1, TAppointment * app2, int asc);

int CmpAppDur(TAppointment * app1, TAppointment * app2, int asc);

void createAppointment(TAppointment *app);
void  editAppointment();
void  deleteAppointment();
void  searchAppointment();
void  sortCalendar(TAppointment *app, int entrycount);
void listCalendar(TAppointment *app, int entrycount);
