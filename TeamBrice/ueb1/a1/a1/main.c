//
//  main.c
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//

#include <stdio.h> 
#include "datastructure.h" 
#include "datetime.h" 
#include "tools.h"
#include "escapesequenzen.h"

int main()
{
    TDate Date;
    TTime Time;
    char Input[20];
    
    do
    {
        clearScreen();
        printf("Geben Sie bitte ein gueltiges Datum ein: ");
        *Input = '\0';
        scanf("%19[^\n]", Input);
        clearBuffer();
        if (*Input)
            if (getDateFromString(Input, &Date))
                printf("Das Datum %02i.%02i.%04i ist gueltig!\n", Date.Day, Date.Month, Date.Year);
            else
                printf("Das eingegebene Datum %s ist ungueltig!\n", Input);
            else
                printf("Sie haben nichts eingegeben!\n");
    
        printf("Geben Sie bitte eine gueltige Uhrzeit ein: "); *Input = '\0';
        scanf("%19[^\n]", Input);
        clearBuffer();
        if (*Input)
            if (getTimeFromString(Input, &Time))
                printf("Die Uhrzeit %02i:%02i:%02i ist gueltig!\n", Time.Hour, Time.Minute, Time.Second);
            else
                printf("Die eingegebene Uhrzeit ist ungueltig!\n");
            else
                printf("Sie haben nichts eingegeben!\n");
    
    } while (askAgain("Moechten Sie noch einmal (j/n) ? "));

  return 0;
}