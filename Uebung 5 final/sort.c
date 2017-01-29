#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "sort.h"
#include "calendar.h"
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
/** \brief  Unterteilt das angegebene Array in zwei Teile, wobei im linken Teil alle Werte
 *          kleiner und im rechten Teil alle Werte groesser als die mittlere Schranke sind.
 *          Der Index der Schranke wird zurueckgegeben.
 *
 * \param A TAppointment*       das zu sortierende Array
 * \param ui int                der untere Index des Teils des Arrays, der sortiert werden soll
 * \param oi int                der obere Index (entsprechend ui)
 * \param swp void (*,*)        Zeiger auf (Vergleichs)-Funktion
 * \param cmp int (*,*)         Zeiger auf (Tauschen)-Funktion
 * \return int                  Ausgabe der neuen unteren Schranke
 *
 */
//  --------------------------------------------------------------------------------
int Partition( TAppointment *A, int ui, int oi, int ( *cmp ) ( TAppointment, TAppointment  ),  void (*swp) (TAppointment *, TAppointment *) )
{
    //printf("\nstart Part %i, %i\n", ui, oi);
    int i = ui+1, j = oi;           //Vorlesung
    TAppointment *comp = A + ui ;
    //comp = calloc(1, sizeof(TAppointment));
    //comp->Duration = calloc(1, sizeof(TTime));    // weil Dauer ein Zeiger ist
    while(i <= j)
    {
        //printf("\n i%i<j%i?\n", i, j);
        // naechstes Element > comp von links suchen (im linken Teil)
        while((i<=j)&&(cmp( *(A+i), *comp ) != 1))
        {
            //printf("\nlinks = -1 ?%i",(cmp(*(A+i),*comp )) );
            i++;
        }
        // naechstes Element > comp von rechts suchen (im rechten Teil)

        while ((j>=i) &&(cmp( *(A+j), *comp) != -1))
        {
            //printf("\nrechts != -1? %i",(cmp(*(A+j),*comp )) );
            j--;
        }

        if( i < j )
        {
            //printf("SWAPFUNKTION");
            //printf("\n%i.) %2i.%2i.%4i\n", i, calendar[i].DateOfAppointment.Day, calendar[i].DateOfAppointment.Month, calendar[i].DateOfAppointment.Year);
            //printf("%i.)%2i.%2i.%4i\n", j, calendar[j].DateOfAppointment.Day, calendar[j].DateOfAppointment.Month, calendar[j].DateOfAppointment.Year);

            swp( &A[i],  &A[j]);

            //printf("%i.)\n%2i.%2i.%4i\n", i, calendar[i].DateOfAppointment.Day, calendar[i].DateOfAppointment.Month, calendar[i].DateOfAppointment.Year);
            //printf("%i.)%2i.%2i.%4i\n",j,  calendar[j].DateOfAppointment.Day, calendar[j].DateOfAppointment.Month, calendar[j].DateOfAppointment.Year);
            i++;
            j--;
        }
    }
    i--;
    //swp( (A+i), &comp);
    swp( &A[i], comp);
    //free(comp);
    return i;
}

//  --------------------------------------------------------------------------------
/** \brief  Unterteilt das Array in zwei Teile (Funktion partition) und ruft sich selber
 *          fuer beide Teile erneut auf.
 *
 * \param A TAppointment*       das zu sortierende Array
 * \param ui                -   der untere Index des Teils des Arrays, der sortiert werden soll
 * \param oi                -   der obere Index (entsprechend ui)
 * \param swp void (*,*)        Zeiger auf (Vergleichs)-Funktion
 * \param cmp int (*,*)         Zeiger auf (Tauschen)-Funktion
 * \return
 *
 */
//  --------------------------------------------------------------------------------
void Qsort (TAppointment *A, int ui, int oi, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *))
{
    int idx;                                                                              // Schranke einer Zerlegung
    if(ui >= oi)
        return;

    else
    {
        //printf("Q0");
        idx = Partition(A, ui, oi, cmp, swp);
        //printf("Q1");
        Qsort(A, ui, idx -1, cmp, swp);
        //printf("Q2");                                                              // linken Teil rekursiv sortieren
        Qsort(A, idx+1, oi, cmp, swp);
        //printf("Q3");

    }
}

//  --------------------------------------------------------------------------------
/** \brief Initialisiert Qsort
 *
 * \param A TAppointment*       das zu sortierende Array
 * \param Anz int               Größe des Arrays
 * \param swp void (*,*)        Zeiger auf (Vergleichs)-Funktion
 * \param cmp int (*,*)         Zeiger auf (Tauschen)-Funktion
 * \return void
 *
 */
//  --------------------------------------------------------------------------------
void quicksort(TAppointment *A, int Anz, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *))
{
    Qsort(A,0, Anz-1, cmp, swp);
}
