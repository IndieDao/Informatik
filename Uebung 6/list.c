#include <stdio.h>
#include <stdlib.h>
//#include "calendar.h"
#include "datastructure.h"
#include "compare.h"
#include "datetime.h"
//#include "tools.h"
#include "list.h"

extern TAppointment *First, *Last;

/** einfach verkettete Liste

//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
int compare (TAppointment *L1, TAppointment *L2)
{
//    return L1->Index - L2->Index;
}
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
void insert(TAppointment *Neu)
{
    TAppointment *tmp = First;

    if(Neu)
    {
        Neu->Next = NULL;
        if(First==NULL)
        {
            First = Last = Neu;
            return;
        }
        if ( compare ( tmp, Neu) >= 0 )     //vergleiche mit erstem Datensatz
        {
            Neu->Next = First;
            First = Neu;
            return;
        }
        if ( compare ( Last, Neu) <= 0 )     //vergleiche mit erstem Datensatz
        {
            Neu->Next = tmp->Next;
            tmp->Next = Neu;
            return;
        }
        tmp = tmp->Next;
    }
}
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
TAppointment *Remove ( TAppointment *Del)
{

    TAppointment *tmp = First;
    TAppointment *tmp2 = First;

    if ( First == NULL)
        return NULL;

    if ( compare( First, Del) == 0)
    {
        First = First->Next;
        if ( First==NULL)
            Last = NULL;

        return tmp;
    }
    while ( tmp->Next)
    {
        if (compare(tmp->Next, Del) == 0)
        {
            tmp2 = tmp->Next;
            tmp->Next = tmp2->Next;
            if (Last == tmp2)
                Last= tmp;
            return tmp2;
        }
        tmp = tmp->Next;
    }
    return NULL;
}
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
void append(TAppointment *Neu)
{
    if (Neu)
    {
        Neu->Next = NULL;
        if(First == NULL)
        {
            First = Last = Neu;
            return;
        }
        Last->Next = Neu;
        Last = Neu;
    }
}
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------
void printList()
{
    TAppointment *tmp = First;
    if( tmp == NULL)
    {
        printf("Liste ist leer!\n");
        return;
    }
    while(tmp)
    {
        printf("%i:%f\n", tmp->Index, tmp->Wert);
        tmp = tmp->Next;
    }
}
*/

/** Doppelt verkettete Listen*/

/**********************************************************
* appendInList
* Haengt ein neues Listenelement an das Ende
* der doppelt verketteten Liste an.
* Parameter: Neu - Zeiger auf neues Listenelement
* Rueckgabe: Wahrheitswert, ob das neue Listenelement an
*            die Liste angehangen werden konnte
*********************************************************/
int appendInDList(TAppointment *Neu)
{
    // pruefen, ob Liste existiert
    if (First == NULL)
    {
        // Fall 1: Liste ist leer
        Neu->Next = Neu->Previous = NULL;
        First = Last = Neu;
    }

    // pruefen, ob neues Listenelement existiert
    else
    {
        // Fall 2: Liste ist nicht leer
        Neu->Next = NULL;
        Neu->Previous = Last;
        Last = Last->Next = Neu;
        //printDate(Last);
        //printf("letztes Element angehängt\n");
    }
    return 1;
}

/**********************************************************
* insertInList
* Fuegt ein neues Listenelement in eine doppelt verkettete
* Liste sortiert nach dem Index ein.
* Parameter: Neu - Zeiger auf das neue Listenelement
* Rueckgabe: Wahrheitswert, ob das neue Listenelement in
* der Liste eingefuegt werden konnte.
**********************************************************/
int insertInDList(TAppointment *Neu)
{
    TAppointment *temp;
    temp = First;

// pruefen, ob neues Listenelement existiert
    if (Neu == NULL)
    {
        return 0;
    }

// Fall 1: Liste ist leer
    if (First == NULL)
    {
        printf("\nKeine Termine im Kalender\n");

        Neu->Next = Neu->Previous = NULL;
        First = Last = Neu;
        return 1;
    }

// Fall 2: vor dem ersten Element einfuegen
    //printDate(Neu);
    switch (compareDate(First, Neu))
    {
    case 1:
        Neu->Next = First;
        Neu->Previous = NULL;
        First = First->Previous = Neu;
        return 1;

    case 0:
        if((compareTime(First, Neu)) != -1)
        {
            Neu->Next = First;
            Neu->Previous = NULL;
            First = First->Previous = Neu;
            return 1;
        }
        appendInDList(Neu);
        return 1;

    case -1:
        break;
    }

// Fall 3: nach dem letzten Element einfuegen
switch (compareDate(Last, Neu))
    {
    case -1:
        appendInDList(Neu);
        return 1;

    case 0:
        if((compareTime(Last, Neu)) == -1)
        {
        appendInDList(Neu);
        return 1;
        }

    case 1:
        break;
    }
    /*
    if(compareDate(Last, Neu) != 1)
    {
        if(compareTime(Last, Neu) != 1 )
        {
            printf("\nein letztes Element %i\n", compareDate(Last, Neu) );
            appendInDList(Neu);
        }
        return 1;
    }
*/
// Fall 4: zwischen zwei Listenelement einfuegen
    while (temp != Last->Next)
    {
        switch (compareDate(temp->Next, Neu))
        {
        case 1:
            Neu->Next = temp->Next;
            Neu->Previous = temp;
            temp->Next = temp->Next->Previous = Neu;
            return 1;

        case 0:
            if((compareTime(temp->Next, Neu)) != -1)
            {
                Neu->Next = temp->Next;
                Neu->Previous = temp;
                temp->Next = temp->Next->Previous = Neu;
                return 1;
            }
            break;

        case -1:
            break;
        }

        //printf("\nElement dazwischen %i\n", compareDate(temp, Neu) );
        // pruefen, ob neues Listenelement vor dem naechsten Element eingefuegt werden muss
        /*if (compareDate(temp->Next, Neu) == 1)
        {
            Neu->Next = temp->Next;
            Neu->Previous = temp;
            temp->Next = temp->Next->Previous = Neu;
            return 1;
        }
        */
        temp = temp->Next;
    }
    return 0;
}


/**********************************************************
 * removeFromList
 * Entfernt das (erste) Listenelement, dessen Index dem
 * delIndex (Parameter) entspricht, aus der verketteten
 * Liste.
 * Parameter: delIndex - der Index des zu entfernenden Elements
 * Rueckgabe: Zeiger auf das entfernte Listenelement bzw.
 *            NULL-Zeiger, wenn das Listenelement nicht
 *            gefunden wurde
 **********************************************************/
TAppointment *removeFromDList(int delIndex)
{
    TAppointment *tmp = NULL, *prev = NULL;

    // Fall 1: Liste leer?
    if (First == NULL)
        return NULL;

    // Fall 2: Listenanfang entfernen?
    if (delIndex == 1)
    {
        First = First->Next;
        // nur ein Element in Liste?
        if (First == NULL)
            Last = NULL;
        else
            First->Previous = NULL;
        return tmp;
    }

    // Fall 3: zu entfernendes Element suchen
    tmp = First->Next;

    for ( ; delIndex >= 3 ; delIndex--) // erstes Element wurde schon getestet
    {
        tmp = tmp->Next;
    }
    if (tmp != NULL)
    {
        // Fall 4: Listenende entfernen?
        if (tmp == Last)
        {
            Last = Last->Previous;
            Last->Next = NULL;
            return tmp;
        }
        else
        {
            prev = tmp->Previous;
            prev->Next = tmp->Next;
            prev->Next->Previous = prev;
            return tmp;
        }
    }
    else
        printf("Fehler! kein Datensatz vorhanden!");

    return NULL;
}
