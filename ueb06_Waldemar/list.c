#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"


void insertInDList(TAppointment * newApp, int (*cmp)(const void*, const void*))
{
    TAppointment * tmpApp = First;
    if(newApp)
    {
        newApp->Next = newApp->Prev = NULL;
        if( !First )
        {
            First = Last = newApp;
            return;
        }

        if( cmp(First, newApp) >= 0 )
        {
            newApp->Next = First;
            First = First->Prev = newApp;
            return;
        }

        if( cmp(Last, newApp) <= 0 )
        {
            newApp->Prev = Last;
            Last = Last->Next = newApp;
            return;
        }

        while( tmpApp->Next != NULL)
        {
            if( cmp(tmpApp->Next, newApp) >= 0 )
            {
                newApp->Next = tmpApp->Next;
                newApp->Prev = tmpApp;
                tmpApp->Next->Prev = newApp;
                tmpApp->Next = newApp;
                return;
            }
            tmpApp = tmpApp->Next;
        }
    }
}

TAppointment * removeFromDList( TAppointment * delApp, int (*cmp)(const void*, const void*))
{
    TAppointment * tmpApp = First;
    TAppointment * rem = NULL;

    if( !First )
        return NULL;

    if( cmp(First, delApp) == 0 )
    {
        rem = First;
        First = First->Next;

        if( !First )
            Last = NULL;

        else
            First->Prev = NULL;

        return rem;
    }

    if( cmp(Last, delApp) == 0 )
    {
        rem = Last;
        Last = Last->Prev;
        Last->Next = NULL;
        return rem;
    }

    while( tmpApp->Next != NULL)
    {
        if( cmp(tmpApp->Next, delApp) == 0 )
        {
            rem = tmpApp->Next;
            tmpApp->Next = tmpApp->Next->Next;
            tmpApp->Next->Prev = tmpApp;
            return rem;
        }
        tmpApp = tmpApp->Next;
    }

    return NULL;
}
