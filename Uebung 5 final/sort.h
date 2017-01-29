#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

//  Unterteilt das angegebene Array in zwei Teile, wobei im linken Teil alle Werte
//  kleiner und im rechten Teil alle Werte groesser als die mittlere Schranke sind.
//  Der Index der Schranke wird zurueckgegeben.
int Partition( TAppointment *A, int ui, int oi, int ( *cmp ) ( TAppointment, TAppointment  ),  void (*swp) (TAppointment *, TAppointment *) );
//  Unterteilt das Array in zwei Teile (Funktion partition) und ruft sich selber
//  fuer beide Teile erneut auf.
void Qsort (TAppointment *A, int ui, int oi, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *));
//  Initialisiert Qsort
void quicksort(TAppointment *A, int Anz, int (*cmp) (TAppointment *, TAppointment *),  void (*swp) (TAppointment *, TAppointment *));

//int (*cmp) (TAppointment *, TAppointment *);
//int (*Swap) (TAppointment *, TAppointment *);

#endif // SORT_H_INCLUDED
