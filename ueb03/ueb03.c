#include <stdio.h>

int main()
{
   double r1, r2, r3;          // vorgegebene Widerstaende
   double rGes, rParGes, rUnb; // Ergebnis-Widerstände
   rGes    = 0.0;
   rParGes = 0.0;
   rUnb    = 0.0;

   //Lies die Werte für Widerstände ein
   printf("Berechnung des Gesamtwiderstands, bei Reihen- und Parallelschaltung \nfür 3 Widerstände\n \n");
   printf("Geben Sie bitte 3 Werte für Widerstände ein:\n\nEingabe Widerstand          1:\n");
   scanf("%lf", &r1);
   printf("Geben Sie bitte Widerstand 2 ein:\n");
   scanf("%lf", &r2);
   printf("Geben Sie bitte Widerstand 3 ein:\n");
   scanf("%lf", &r3);

   // Reihenschaltung
   rGes = r1 + r2 + r3;
   printf("\n \n Reihenschaltung: \n %f Ohm + %f Ohm + %f Ohm = %f Ohm", r1, r2, r3, rGes);

   // Parallelschaltung
   rParGes = 1/(1/r1 + 1/r2 + 1/r3);
   printf("\n \n Parallelschaltung: \n 1 / %f Ohm + 1 / %f Ohm + 1 / %f Ohm = %f Ohm", r1, r2, r3, rParGes);

   // Wheatstonesche Messbrücke
   rUnb = r3 * (r1 / r2);
   printf("\n \n Wheatstonesche Messbrücke: \n %f Ohm * %f Ohm / %f Ohm = %f Ohm \n\n", r3, r1, r2, rUnb);

   return 0;
}

