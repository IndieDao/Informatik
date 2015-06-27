#include <stdio.h>
#include <math.h>
#include "escapesequenzen.h"

int main()
{
   double Op1, Op2, Erg;
   int Menuewahl, GueltigeEingabe;
   char Dummy;
   
   do
   {
      //Menue ausgeben
      CLEAR;
      HOME;
      printf("Einfacher Taschenrechner\n");
      printf("========================\n");
      POSITION(3, 4);
      printf("1. Addition\n");
      POSITION(4, 4);
      printf("2. Subtraktion\n");
      POSITION(5, 4);
      printf("3. Multiplikation\n");
      POSITION(6, 4);
      printf("4. Division\n");
      POSITION(7, 4);
      printf("9. Programmende\n");
  
      // Benutzereingabe Menue
      POSITION(9, 1);   //Eingabezeile loeschen
      CLEAR_LINE;
      POSITION(9, 1);
      INVERSE;
      printf ("Ihre Wahl:");      
      ATTRIBUTE_OFF;
      GueltigeEingabe = scanf("%i", &Menuewahl);
      do
      {
         scanf("%c", &Dummy);
      } while (Dummy != '\n');

      if (GueltigeEingabe)       //Eingabe ist wahr
      {
         POSITION(11,1);
         switch(Menuewahl)
         {
            case 1: printf("Addition\n");
                    printf("--------\n");
            break;
            case 2: printf("Subtraktion\n");
                    printf("-----------\n");
            break;
            case 3: printf("Multiplikation\n");
                    printf("--------------\n");
                    break;
            case 4: printf("Division\n");
                    printf("--------\n");
            break;
            default: GueltigeEingabe = 0;
            break;
         }
   
         if (GueltigeEingabe)  //ausser bei Programmende
         {
            //Operand 1 erfragen
            do
            {
               POSITION(14, 1); //Eingabezeile löschen
               printf("Geben Sie bitte den ersten Operanden ein: ");
               GueltigeEingabe = scanf("%lf", &Op1);
               if (GueltigeEingabe == 0)
                  POSITION(15,1);
                  printf("falsche Eingabe!\n");
               do          //Tastaturpuffer loeschen
                  scanf("%c", &Dummy);
               while (Dummy != '\n');
            } while (!GueltigeEingabe);        //solange bis gültige Eingabe

            //Operand 2 erfragen
            do
            {
               POSITION(15, 1); //Eingabezeile löschen
               printf("Geben Sie bitte den zweiten Operanden ein: ");
               GueltigeEingabe = scanf("%lf", &Op2);
               if (!GueltigeEingabe)
                  printf("falsche Eingabe!\n");
               else if (Menuewahl == 4 && Op2 == 0.0)
               {
                  printf("Division durch 0");
                  GueltigeEingabe = 0;
               }
               do          //Tastaturpuffer loeschen
                    scanf("%c", &Dummy);
               while (Dummy != '\n');
            }while (!GueltigeEingabe);      //solange bis gültige Eingabe
         }
         //Werte ausgeben
         POSITION(18, 1);
         switch(Menuewahl)
         {
            case 1:  Erg = Op1+Op2;
                     printf("%lf + %lf = %lf\n", Op1, Op2, Erg);
                     break;
            case 2:  Erg = Op1-Op2;
                     printf("%lf - %lf = %lf\n", Op1, Op2, Erg);
                     break;
            case 3:  Erg = Op1*Op2;
                     printf("%lf*%lf = %lf\n", Op1, Op2, Erg);
                     break;
            case 4:  Erg = Op1/Op2;
                     printf("%f / %f = %f\n", Op1, Op2, Erg);
                     break;
            case 9:  break;
            default: printf("falsche Eingabe!\n");
                     break;
         }
      }
      else
      {
         printf("Falsche Eingabe!\n");
      }  
      // Eingabetaste abwarten
      POSITION(20, 1);
      INVERSE;
      FORECOLOR_KOBALT;
      printf("Bitte druecken Sie die Eingabetaste ...\n");
      ATTRIBUTE_OFF;
      do
         scanf("%c", &Dummy);
      while (Dummy != '\n');
   } while (Menuewahl != 9); //bis Programmende
   return 0;
}
