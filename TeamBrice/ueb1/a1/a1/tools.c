//
//  tools.c
//  a1
//
//  Created by BD on 07.10.16.
//  Copyright © 2016 BD. All rights reserved.
//
#include <stdio.h>
#include "tools.h"
#include <stdlib.h>
#include "escapesequenzen.h"



void clearBuffer()
{
    char Dummy;
    
    do
    {
        scanf("%c", &Dummy);
        
    } while (Dummy != '\n');
    
}


int askAgain()
{
    char Frage = 'j';
    int  W = 0;
    do
    {
        printf("\nMoechten Sie noch einmal (j/n)? ");
        scanf("%c", &Frage);
        
        if(Frage != '\n')
            clearBuffer();
        
        if( (Frage != 'j') && (Frage != 'J') && (Frage != 'N') && (Frage != 'n') )
            printf("\nFalsche Eingabe!");
        
        if((Frage == 'N') || (Frage == 'n'))
            W = 1;
        else if((Frage == 'J') || (Frage == 'j'))
            W = 1;
        else
            W = 0;
    } while ( W == 0);
    
    return ( (Frage == 'j') || (Frage == 'J') );
}


void clearScreen()
{
    CLEAR;
    
}


