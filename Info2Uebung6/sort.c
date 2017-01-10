#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
//#include <string.h>jhbknm
#include "escapesequenzen.h"

/** Quicksort Funktionen */

//typedef int (*compare) (TAppointment *, TAppointment *);
//compare comparePointer[] = { compareDate, compareTime, compareDuration, compareDescription, compareLocation };   /** Funktionsarray          */

//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void Tausche(int *D1, int *D2)
{
    int temp;
    // setze Vergleichselement (Schranke zwischen beide Teile)
    temp = *D2;
    *D2= *D1;
    *D1=temp;
}

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
int Partition( TAppointment *A, int ui, int oi, int compareFkt )
{
        printf("P");
    int i = ui+1, j = oi;
    TAppointment comp;
    //comp = calloc(1, sizeof(TAppointment));
    //comp->Duration = calloc(1, sizeof(TTime));    // weil Dauer ein Zeiger ist
    comp = A[ui];
    while(i <=j)
    {
        // naechstes Element > comp von links suchen (im linken Teil)
        //while((i<=j)&&(*(A+i)<= *comp))                                              /**hier muss der Comp und Swap hin*/
        //while( ( ( i<j )&& (compare( comp, *(A+i) ) == 1 ) ) || ( ( i==j )&&(compare( *comp, *(A+i) ) == 0 ) ) )
        //while( ( ( i<j )&& (comparePointer[1]( comp, (A+i) ) == 1 ) ) || ( ( i==j )&&(comparePointer[1]( comp, (A+i) ) == 0 ) ) )
        while( ( ( i<j ) && (compareDate( comp, A[i] ) == 1 ) ) || ( ( i==j )&&(compareDate( comp, A[i] ) == 0 ) ) )
        i++;
        // naechstes Element > comp von rechts suchen (im rechten Teil)
        //while ((j>=i) &&(*(A+j)>= *comp))
        //while ( ( ( j>i ) && (comparePointer[1]( comp, (A+i) ) == -1 ) ) || ( ( i==j )&&(comparePointer[1]( comp, (A+i) ) == 0 ) ) )
        while( ( ( j>i )&& (compareDate( A[j], comp ) == 1 ) ) || ( ( i==j )&&(compareDate( comp, A[j] ) == 0 ) ) )
        j--;
        if(i<j)
        {
            swapAppointment(A[i], A[j]);
            i++;
            j--;
        }
    }
    i--;
    swapAppointment(A[i], comp);
    //Tausche(A+i, comp);
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

//void Qsort (int *A, int ui, int oi, int (*compa (TAppointment *, TAppointment *), int (*swap) (TAppointment *, TAppointment *)))
void Qsort (TAppointment *A, int ui, int oi, int compareFkt)
{
    printf("S");
    int idx;                                                                              // Schranke einer Zerlegung
    if(ui >=oi)
        return;

    idx = Partition(A, ui, oi, compareFkt);
    Qsort(A, ui, idx-1, compareFkt);                                                              // linken Teil rekursiv sortieren
    Qsort(A, idx+1, oi, compareFkt);                                                              // rechten Teil rekursiv sortieren
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void quicksort(TAppointment *A, int Anz, int compareFkt)
{
    printf("Q");
    Qsort(A ,0, Anz-1, compareFkt);
}
