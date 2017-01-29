#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "compare.h"
#include <string.h>


//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Zeit von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt (T1 > T2 = -1) , ( T1 = T2 = 0 ), ( T1 < T2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareTime(TAppointment *Appointment1, TAppointment *Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour) ? 0 : 1;
    if(Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour)
    {
        if ( Appointment1->TimeOfAppointment.Minute == Appointment2->TimeOfAppointment.Minute )
        {
            if ( Appointment1->TimeOfAppointment.Second == Appointment2->TimeOfAppointment.Second )
            {
                Vergleich = 0;
            }
            else if ( Appointment1->TimeOfAppointment.Second > Appointment2->TimeOfAppointment.Second )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1->TimeOfAppointment.Minute > Appointment2->TimeOfAppointment.Minute)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1->TimeOfAppointment.Hour > Appointment2->TimeOfAppointment.Hour)
    {
        Vergleich = 1;
    }
    //printf("Zeitindex = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int           gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDuration(TAppointment Appointment1, TAppointment Appointment2)
{
    int Vergleich = -1;
    //Vergleich = (Appointment1->TimeOfAppointment.Hour == Appointment2->TimeOfAppointment.Hour) ? 0 : 1;
    if(!Appointment1.Duration)
    {
        return -1;
    }

    if(Appointment1.Duration->Hour == Appointment2.Duration->Hour)
    {
        if ( Appointment1.Duration->Minute == Appointment2.Duration->Minute )
        {
            if ( Appointment1.Duration->Second == Appointment2.Duration->Second )
            {
                Vergleich = 0;
            }
            else if ( Appointment1.Duration->Second > Appointment2.Duration->Second )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1.Duration->Minute > Appointment2.Duration->Minute)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1.Duration->Hour > Appointment2.Duration->Hour)
    {
        Vergleich = 1;
    }
    printf("Vergleich = %i", Vergleich);
    return Vergleich;
}
//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int           gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDate(TAppointment *Appointment1, TAppointment *Appointment2)
{
    //printf("\nI  %2i.%2i.%4i\n", Appointment1.DateOfAppointment.Day, Appointment1.DateOfAppointment.Month, Appointment1.DateOfAppointment.Year);
    //printf("II %2i.%2i.%4i\n", Appointment2->DateOfAppointment.Day, Appointment2->DateOfAppointment.Month, Appointment2->DateOfAppointment.Year);
    int Vergleich = -1;
    //Vergleich = (Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year) ? 0 : 1;
    if(Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year)
    {
        if ( Appointment1->DateOfAppointment.Month == Appointment2->DateOfAppointment.Month )
        {
            if ( Appointment1->DateOfAppointment.Day == Appointment2->DateOfAppointment.Day )
            {
                Vergleich = 0;
            }
            else if ( Appointment1->DateOfAppointment.Day > Appointment2->DateOfAppointment.Day )
            {
                Vergleich = 1;
            }
        }
        else if ( Appointment1->DateOfAppointment.Month > Appointment2->DateOfAppointment.Month)
        {
            Vergleich = 1;
        }
    }
    else if (Appointment1->DateOfAppointment.Year > Appointment2->DateOfAppointment.Year)
    {
        Vergleich = 1;
    }
    //printf("Datumindex = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareDescription(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Beschreibung), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Beschreibung), sizeof(char));

    strcpy(App1, Appointment1.Beschreibung);
    strcpy(App2, Appointment2.Beschreibung);
    for( i = 0 ; i <= strlen(App1) ; i++)
    {
        if(*(App1+i) > 96)
            *(App1+i)-= 32;
    }

    for( i = 0 ; i <= strlen(App2); i++)
    {
        if(*(App2+i) > 96)
            *(App2+i)-= 32;
    }
    i=0;
    do
    {
        if (*(App1+i) > *(App2+i) )
            return 1;

        else if (*(App1+i) < *(App2+i) )
            return -1;

    }
    while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergĺeicht Dauer von zwei Terminen
 *
 * \param Appointment1 TAppointment
 * \param Appointment2 TAppointment
 * \return int          gibt als Ergebnis für (D1 > D2 = -1) , ( D1 = D2 = 0 ), ( D1 < D2 = 1 ) aus.
 *
 */
//  --------------------------------------------------------------------------------
int compareLocation(TAppointment Appointment1, TAppointment Appointment2)
{
    int i;
    int Vergleich = 0;
    char *App1;
    App1 = calloc(strlen(Appointment1.Location), sizeof(char));
    char *App2;
    App2 = calloc(strlen(Appointment2.Location), sizeof(char));


    strcpy(App1, Appointment1.Location);
    strcpy(App2, Appointment2.Location);

    for( i = 0 ; i <= strlen(Appointment1.Location) ; i++)
    {
        if(*(App1+i) > 96)
            *(App1+i)-= 32;
    }
    for( i = 0 ; i <= strlen(Appointment2.Location); i++)
    {
        if(*(App2+i) > 96)
            *(App2+i)-= 32;
    }
    i=0;
    do
    {
        if (*(App1+i) > *(App2+i) )
            return 1;

        else if (*(App1+i) < *(App2+i) )
            return -1;

    }
    while (*(App1+i) == *(App2+i++) );
    free(App1);
    free(App2);
    printf("Vergleich = %i", Vergleich);

    return Vergleich;
}

//  --------------------------------------------------------------------------------
/** \brief vergleicht zwei Termine
 *
 * \param Appointment1 TAppointment*
 * \param Appointment2 TAppointment*
 * \return int          gibt bei Gleichheit 0 zurück
 *
 */
//  --------------------------------------------------------------------------------
int compareEquality(TAppointment *Appointment1, TAppointment *Appointment2)
{
    if(    Appointment1->DateOfAppointment.Year == Appointment2->DateOfAppointment.Year
            && Appointment1->DateOfAppointment.Month == Appointment2->DateOfAppointment.Month
            && Appointment1->DateOfAppointment.Day == Appointment2->DateOfAppointment.Day)
        return 0;
    else if(    Appointment1->DateOfAppointment.Year >= Appointment2->DateOfAppointment.Year
                || Appointment1->DateOfAppointment.Month >= Appointment2->DateOfAppointment.Month
                || Appointment1->DateOfAppointment.Day >= Appointment2->DateOfAppointment.Day)
        return 1;
    else
        return -1;
}
