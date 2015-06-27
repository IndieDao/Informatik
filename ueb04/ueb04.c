#include <stdio.h>
#include <math.h>
 
 int main()
 {  
      double p, q;         // Eingabevariablen
      double wurzel;       // Wurzelteil der pq Formel
      double x1, x2;       // Ergebnis-Widerstände
                
   // Lies p und q ein
   printf("\n|-------------------------------------------------------------------|\n");
   printf("| Dieses Programm loest eine quadratische Gleichung zweiten Grades: |\n");
   printf("| x^2 + p * x +q                                                    |\n");
   printf("| geben Sie bitte die Faktoren ""p"" und ""q"" ein:                         |\n");
   printf("|-------------------------------------------------------------------|\n");
                                                          
   printf("p = ");
   scanf("%8lf", &p);
   printf("\nq = ");
   scanf("%8lf", &q);

   // Rechnung pq Formel
   wurzel = sqrt(((p*p)/4)-q);
   x1 = 0.5 * p + wurzel;
   x2 = 0.5 * p - wurzel;
                                      
    printf("\n|-------------------------------------------------------------------|\n");
    printf("| Es wird nun die quadratische Gleichung zweiten Grades             |\n");
    printf("| x^2 + %8.2lf * x +%8.2lf                                      |\n", p, q);
    printf("| geloest.                                                          |\n");
    printf("|                              ____________________________         |\n");
    printf("|          1            +     /%8.2lf ^ 2                \\        |\n", p);
    printf("| x   = - --- *%8.2lf - \\  /  -------------- -%8.2lf            |\n", p, q);
    printf("|  1,2     2               \\/      4                                |\n");
    printf("|                                                                   |\n");
    printf("| x1 = %5.2lf                                                        |\n",x1);                
    printf("| x2 = %5.2lf                                                        |\n",x2);
    printf("|-------------------------------------------------------------------|\n"); 
   return 0;
}
