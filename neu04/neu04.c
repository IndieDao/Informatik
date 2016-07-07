#include <stdio.h>
#include <math.h>

/*Dieses Programm loest eine quadratische Gleichung 2ten Grades*/

int main()
{
    double p, q;          // p und q der Formel
    double wurzel;        // Wurzelteil der pq-Formel
    double x1, x2;        // Ergebnis-Widerstaende

    // Eingabemaske
    printf("\n|--------------------------------------------------------------------|\n");
    printf("| Dieses Programm loest eine quadratische Gleichung zweiten Grades:  |\n");
    printf("| x² + p * x + q = 0                                                 |\n");
    printf("|                                                                    |\n");
    printf("| Geben Sie bitte die Faktoren p und q ein:                          |\n");
    printf("|--------------------------------------------------------------------|\n\n");

    // Einlesen von p und q
    printf("p = ");
    scanf("%8lf", &p);
    printf("\nq = ");
    scanf("%8lf", &q);

    // Berechnung
    wurzel = sqrt( ( (p * p) / 4) - q);
    x1 = 0.5 * p + wurzel;
    x2 = 0.5 * p - wurzel;

    // Ausgabemaske der quadratischen Gleichung
    printf("|--------------------------------------------------------------------|\n");
    printf("| Es wird nun die quadratische Gleichung zweiten Grades              |\n");
    printf("| x² + %8.2f * x + %8.2f = 0                                   |\n", p, q);
    printf("| geloest.                                                           |\n");
    printf("|                                  ____________________________      |\n");
    printf("|           1                +    /   %8.2f²                \\     |\n", p);
    printf("| x    = - --- *   %8.2f - \\  /  ------------- - %-8.2f         |\n", p, q);
    printf("|  1,2      2                  \\/          4                         |\n");
    printf("|                                                                    |\n");
    printf("| x1 = %-8.2f                                                      |\n", x1);
    printf("| x2 = %-8.2f                                                      |\n", x2);
    printf("|--------------------------------------------------------------------|\n");

    return 0;
}

