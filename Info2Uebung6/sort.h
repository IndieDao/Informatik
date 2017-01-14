#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

void Tausche(int *D1, int *D2);
int Partition( TAppointment *A, int ui, int oi, int (*cmp) (TAppointment *, TAppointment *));
void Qsort (TAppointment *A, int ui, int oi, int (*cmp) (TAppointment *, TAppointment *));
void quicksort(TAppointment *A, int Anz, int (*cmp) (TAppointment *, TAppointment *),void (*swp) (TAppointment *, TAppointment *));

int (*cmp) (TAppointment *, TAppointment *);
int (*Swap) (TAppointment *, TAppointment *);

#endif // SORT_H_INCLUDED
