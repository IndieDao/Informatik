#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
#include <string.h>
#include "escapesequenzen.h"

/** verkettete Liste */

TLE *First = NULL;
TLE *Last = NULL;
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void append(TLE *Neu)
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
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void printList()
{
    TLE *tmp = First;
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

/** Doppelt verkettete Listen*/

/**********************************************************
* appendInList
* Haengt ein neues Listenelement an das Ende
* der doppelt verketteten Liste an.
* Parameter: Neu - Zeiger auf neues Listenelement
* Rueckgabe: Wahrheitswert, ob das neue Listenelement an
*            die Liste angehangen werden konnte
*********************************************************/
int appendInList(TLE *Neu)
{
   // pruefen, ob neues Listenelement existiert
   if (Neu == NULL)
      return 0;
   if (First == NULL)
   {  // Fall 1: Liste ist leer
      Neu->Next = Neu->Previous = NULL;
      First = Last = Neu;
   }
   else
   {  // Fall 2: Liste ist nicht leer
      Neu->Next = NULL;
      Neu->Previous = Last;
      Last = Last->Next = Neu;
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
int insertInList(TLE *Neu)
{
   TLE *temp = First;
   // pruefen, ob neues Listenelement existiert
   if (Neu == NULL)
      return 0;

   if (First == NULL)
   {  // Fall 1: Liste ist leer
      Neu->Next = Neu->Previous = NULL;
      First = Last = Neu;
      return 1;
   }

   if (First->Index >= Neu->Index)
   {  // Fall 2: vor dem ersten Element einfuegen
      Neu->Next = First;
      Neu->Previous = NULL;
      First = First->Previous = Neu;
      return 1;
   }

   if (Last->Index <= Neu->Index)
   {  // Fall 3: nach dem letzten Element einfuegen
      Neu->Previous = Last;
      Neu->Next = NULL;
      Last = Last->Next = Neu;
      return 1;
   }

   // Fall 4: zwischen zwei Listenelement einfuegen
   while (temp->Next != NULL)
   {  // pruefen, ob neues Listenelement vor dem
      // naechsten Element eingefuegt werden muss
      if (temp->Next->Index >= Neu->Index)
      {
         Neu->Next = temp->Next;
         Neu->Previous = temp;
         temp->Next = temp->Next->Previous = Neu;
         return 1;
      }
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
TLE *removeFromList(int delIndex)
{
   TLE *tmp = NULL, *prev = NULL;

   // Fall 1: Liste leer?
   if (First == NULL)
      return NULL;

   // Fall 2: Listenanfang entfernen?
   if (First->Index == delIndex)
   {
      tmp = First;
      First = First->Next;
      // nur ein Element in Liste?
      if (First == NULL)
         Last = NULL;
      else
         First->Previous = NULL;
      return tmp;
   }

   // Fall 3: Listenende entfernen?
   if (Last->Index == delIndex)
   {
      tmp = Last;
      Last = Last->Previous;
      Last->Next = NULL;
      return tmp;
   }

   // Fall 4: zu entfernendes Element suchen
   tmp = First->Next;
   while (tmp != NULL)
   {
      if (tmp->Index == delIndex)
      {
         prev = tmp->Previous;
         prev->Next = tmp->Next;
         prev->Next->Previous = prev;
         return tmp;
      }
      tmp = tmp->Next;
   }

   return NULL;
}


typedef enum {forward, backward} TDirection;

/**********************************************************
 * printList
 * Gibt Index und Wert der doppelt verketteten Liste in
 * der gewünschten Richtung auf dem Bildschirm aus.
 * Parameter: TDirection: gibt die Ausgaberichtung an
 *               - forward: vorwaerts
 *               - backward: rueckwaerts
 * Rueckgabe: -
 **********************************************************/
void printListDirection(TDirection Direction)
{
   TLE *tmp = (Direction == forward) ? First : Last;
   int AnzahlElemente = 0;

   printf("\nIndex ");
   while (tmp)
   {
      printf("| %3i ", tmp->Index);
      tmp = (Direction == forward) ? tmp->Next : tmp->Previous;
      AnzahlElemente++;
   }

   printf("\n------");
   while (AnzahlElemente--)
      printf("------");

   printf("\nWert ");
   tmp = (Direction == forward) ? First : Last;
   while (tmp != NULL)
   {
      printf("| %3.0f ", tmp->Wert);
      tmp = (Direction == forward) ? tmp->Next : tmp->Previous;
   }
   printf("\n");
}
//  --------------------------------------------------------------------------------
//  Doppelt verkettete Liste
//
//  --------------------------------------------------------------------------------


void printListDoppelt(int Dir)                                                      // ==0 -> vorwärts    == 1 -> rückwärts
{
    TLE *tmp = (Dir == 0) ? First : Last;
    if( tmp == NULL)
    {
        printf("| Index | Value |\n");
        printf("|-------|-------|\n");
        //return;
    }
    while(tmp)
    {
        printf("| %5i | %5.2f |\n", tmp->Index, tmp->Wert);
        tmp = (Dir == 0) ? tmp->Next : tmp->Previous;
    }
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
int compare (TLE *L1, TLE *L2)
{
    return L1->Index - L2->Index;
}
//  --------------------------------------------------------------------------------
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
void insert(TLE *Neu)
{
    TLE *tmp = First;

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
//  erstellt einen Termin in temporärem Kalender und speichert den Termin
//  abschließend nach "calendar".
//  --------------------------------------------------------------------------------
TLE *Remove ( TLE *Del)
{

    TLE *tmp = First;
    TLE *tmp2 = First;

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
