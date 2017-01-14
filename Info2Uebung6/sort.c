#include <stdio.h>
#include <stdlib.h>
//#include "sort.h"
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
//#include <string.h>
#include "escapesequenzen.h"
extern TAppointment calendar[MAX_APPOINTEMENTS];
extern int countAppointments;
/** Quicksort Funktionen */
//compare comparePointer[] = { compareDate, compareTime, compareDuration, compareDescription, compareLocation };   /** Funktionsarray          */

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".#include "calendar.h"
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
//  Unterteilt das angegebene Array in zwei Teile, wobei im linken Teil alle Werte
//  kleiner und im rechten Teil alle Werte groesser als die mittlere Schranke sind.
//  Der Index der Schranke wird zurueckgegeben.
//  Parameter: Array - das zu sortierende Array
//             ui    - der untere Index des Teils des
//                     Arrays, der sortiert werden soll
//             oi    - der obere Index (entsprechend ui)
//  Rueckgabe: int   - Index der Schranke
//  --------------------------------------------------------------------------------
int Partition( TAppointment *A, int ui, int oi, int ( *cmp ) ( TAppointment , TAppointment  ),  void (*swp) (TAppointment *, TAppointment *) )                            /** FEHLER HIER **/
{
    printf("\nstart Part %i   %i\n", ui , oi);
    //int i = ui, j = oi;           //Script
    int i = ui+1, j = oi;           //Vorlesung
    TAppointment comp = *( A + ui );
    //comp = calloc(1, sizeof(TAppointment));
    //comp->Duration = calloc(1, sizeof(TTime));    // weil Dauer ein Zeiger ist
    while(i <= j)
    {
        printf("\n i<j? %i %i\n", i , j);
        // naechstes Element > comp von links suchen (im linken Teil)
        //while((i<=j)&&(cmp((A+i), &comp)>-1))

                                               /**hier muss der Comp und Swap hin*/
        while((i<=j)&&(cmp( *(A+i), comp ) < 1))
        {
            printf("\nlinks = -1 ?%i",(cmp(*(A+i),comp )) );
            i++;
        }
        // naechstes Element > comp von rechts suchen (im rechten Teil)
        //while ((j>=i) &&(cmp((A+j), &comp)<0))

        while ((j>=i) &&(cmp( *(A+j), comp) != -1))
        {
            printf("\nrechts > -1? %i",(cmp(*(A+j),comp )) );
             j--;
        }


        if( i < j )
        {
            printf("SWAPFUNKTION");
            printf("\n%2i.%2i.%4i\n",  calendar[i].DateOfAppointment.Day, calendar[i].DateOfAppointment.Month, calendar[i].DateOfAppointment.Year);
            printf("%2i.%2i.%4i\n",  calendar[j].DateOfAppointment.Day, calendar[j].DateOfAppointment.Month, calendar[j].DateOfAppointment.Year);

            swp( (A+i),  (A+j));
            printf("\n%2i.%2i.%4i\n",  calendar[i].DateOfAppointment.Day, calendar[i].DateOfAppointment.Month, calendar[i].DateOfAppointment.Year);
            printf("%2i.%2i.%4i\n",  calendar[j].DateOfAppointment.Day, calendar[j].DateOfAppointment.Month, calendar[j].DateOfAppointment.Year);
            i++;
            j--;
        }
    }
    i--;
    swp( (A+i), &comp);
    //free(Appointment);
    return i;
}

//  --------------------------------------------------------------------------------
//  Unterteilt das Array in zwei Teile (Funktion partition) und ruft sich selber
//  fuer beide Teile erneut auf.
//  Parameter: Array - das zu sortierende Array
//              ui    - der untere Index des Teils des
//                      Arrays, der sortiert werden soll
//              oi    - der obere Index (entsprechend ui)
//  --------------------------------------------------------------------------------

//(*swap) (TAppointment *, TAppointment *)
void Qsort (TAppointment *A, int ui, int oi, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *))
{
    TAppointment *Appointment;
    Appointment = calloc(1, sizeof(TAppointment));
    int i;

    int idx;                                                                              // Schranke einer Zerlegung
    if(ui >=oi)

        return;
                printf("Q0");
    idx = Partition(A, ui, oi, cmp, swp);
                printf("Q1");
    Qsort(A, ui, idx-1, cmp, swp);
                printf("Q2");                                                              // linken Teil rekursiv sortieren
    Qsort(A, idx+1, oi, cmp, swp);
                printf("Q3");                                                             // rechten Teil rekursiv sortieren

       for(i = 0 ; i < countAppointments; i++)
        {
            Appointment = &calendar[i];
            //printf("%i.) %2i.%2i.%4i\n", i, Appointment->DateOfAppointment.Day, Appointment->DateOfAppointment.Month, Appointment->DateOfAppointment.Year);
        }
        //free(Appointment);
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------

void quicksort(TAppointment *A, int Anz, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *))
//void quicksort(TAppointment *A, int Anz, int c)
{
    Qsort(A ,0, Anz-1, cmp, swp);
    //Qsort(A ,0, Anz-1, c);
}
