#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

void Tausche(int *D1, int *D2);
int Partition( TAppointment *A, int ui, int oi, int compareFkt );
void Qsort (TAppointment *A, int ui, int oi, int compareFkt);
void quicksort(TAppointment *A, int Anz, int compareFkt);

#endif // SORT_H_INCLUDED
