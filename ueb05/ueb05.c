#include <stdio.h>

int main ()
{
   int ganzeZahl;
   int zTest;
   char Ploeschen;
   char W = 'j';

   // Eingabeaufforderung

   do
   { 
         printf("Geben Sie bitte eine ganze Zahl ein:"); 
         
         zTest = scanf("%d", &ganzeZahl);

         // Pufferlöschen
         do 
         {  
            scanf("%c", &Ploeschen);
         }while(Ploeschen != '\n');

         if (zTest == 0 )
            printf("falsche Eingabe! Die Eingabe ist keine ganze Zahl!\n");
         else
            printf("Sie haben die ganze Zahl %d eingegeben\n", ganzeZahl);

         // Wiederholungsfrage
         do
         {
            printf("Moechten Sie eine weitere Zahl berechnen? (j/n) ");
            scanf("%c", &W);

            // Pufferlöschen
            if (W != '\n')
               do 
               {  
                  scanf("%c", &Ploeschen);
               }while(Ploeschen != '\n');

            if ( W != 'j' && W != 'J' && W != 'n' && W != 'N' )
               printf("Geben Sie bitte j oder n ein!\n");
         } while (W != 'j' && W != 'J' && W != 'n' && W != 'N') ;


   } while (W == 'j' || W == 'J');

   printf("Programm wird beendet.\n");
   return 0;
}
