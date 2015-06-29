#include <stdio.h>
#include "tools.h"
#include "escapesequenzen.h"

/****************************************************
 Breite der Spalten 62 zeichen
 Eingabe Zahl 1: 4, 30

 */

int main()
{
   int Zahl1, Zahl2, Result;
   char Op;
   do
   {
      printFrame();

      Zahl1 = getNumber(4);

      Op = getOperator();

      Zahl2 = getNumber(6);

      Result = calcResult(Zahl1, Zahl2, Op);

      printResultNumber(11, Zahl1);

      printResultOperator(Op);

      printResultNumber(13, Zahl2);

      printResultNumber(15, Result);

   } while (askAgain());

   return 0;
}
