#include <stdio.h>
#include <math.h>


int main()
{
    double r1, r2, r3;          // Widerstaende
    double rGes, rPar, rUnb;    // Ergebnisse
    rGes = 0.0;
    rPar = 0.0;
    rUnb = 0.0;

    /*  - Eingabeaufforderung für drei Widerstände 
        - und Speicherung in R1, R2, R3     */
    printf("\n-------------------------------------------------------------------------\n\n");
    printf("\nBerechnungen fuer drei Widerstaende in Reihen | Parallel |\n\nsowie fuer den fehlenden Widerstand bei einer Wheatstoneschen Messbruecke\n\n");
    printf("-------------------------------------------------------------------------\n\n");
    printf("Geben Sie bitte für drei Widerstände Werte (in Ohm) ein:\n\nWelchen Wert für Widerstand 1 ?: ");
    scanf("%lf", &r1);
    printf("\n\nWelchen Wert für Widerstand 2 ?: ");
    scanf("%lf", &r2);
    printf("\n\nWelchen Wert für Widerstand 3 ?: ");
    scanf("%lf", &r3);
   
    //  Berechnungen    
    rGes = r1 + r2 +r3;              //Reihenschaltung
    rPar =1/( 1/r1 + 1/r2 + 1/r3 );  //Parallelschaltung
    // rPar = pow(rGes, -1.0);
    rUnb = r3*(r1/r2);               //Wheatstonesche Messbruecke

    // Bildschirm-Ausgabe
    printf("\n\n---------------------------------------------------------------------\n\n");
    printf("Berechnung einer Reihenschaltung:\n");
    printf("%.2f Ohm + %.2f Ohm + %.2f Ohm = %.2f Ohm\n", r1, r2, r3, rGes);
    printf("\nBerechnung einer Parallelschaltung:\n");
    printf("1 / %.2f Ohm + 1 / %.2f Ohm + 1 / %.2f Ohm = 1 / %.2f Ohm\n", r1, r2, r3, rPar);
    printf("\nBerechnung des vierten Widerstandes einer Wheatstoneschen Messbruecke\n");
    printf("%.2f Ohm * %.2f Ohm / %.2f Ohm = %.2f Ohm\n\n", r3, r1, r2, rUnb);

    return 0;
}

