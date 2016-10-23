#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "calendar.h"
#include "menu.h"

static char Menupunkte[7][24] = {"1. Neuen Termin anlegen", "2. Termin bearbeiten", "3. Termin loeschen", "4. Termin suchen", "5. Termine sortieren", "6. Termine auflisten", "7. Programm beenden"};

int main()
{
   TDate Date;
   TTime Time;
   char Input[20];

   do
   {
      clearScreen();
      getMenu("Terminverwaltung V 0.2\n", *Menupunkte, 7);
      *Input = '\0';
      scanf("%19[^\n]", Input);
      clearBuffer();
      if (*Input)
         if (getDateFromString(Input, &Date))
            printf("Das Datum %02i.%02i.%04i ist gueltig!\n",
                   Date.Day, Date.Month, Date.Year);
         else
            printf("Das eingegebene Datum %s ist ungueltig!\n", Input);
      else
         printf("Sie haben nichts eingegeben!\n");
      printf("Geben Sie bitte eine gueltige Uhrzeit ein (st:mi:se): ");
      *Input = '\0';
      scanf("%19[^\n]", Input);
      clearBuffer();
      if (*Input)
         if (getTimeFromString(Input, &Time))
            printf("Die Uhrzeit %02i:%02i:%02i ist gueltig!\n",
                   Time.Hour, Time.Minute, Time.Second);
         else
            printf("Die eingegebene Uhrzeit ist ungueltig!\n");
      else
         printf("Sie haben nichts eingegeben!\n");
   } while (askAgain("Moechten Sie noch einmal (j//n) ? "));
   return 0;
}
