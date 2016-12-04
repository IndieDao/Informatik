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
#include "string.h"



/**********************************
 
 *********************************/
void clearBuffer()
{
    char Dummy;
    
    do
    {
        scanf("%c", &Dummy);
        
    } while (Dummy != '\n');
    
}

/**********************************
 
 *********************************/
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


/**********************************
 
 *********************************/
void clearScreen()
{
    
   system("clear");
}


/**********************************
 
 *********************************/
void waitForEnter()
{
    char Dummy;
    
    printf("\nBitte druecken Sie die Eingabetaste ...\n");
    
    do
        scanf("%c", &Dummy);
    while(Dummy !='\n');
    
}


/**********************************
 
 *********************************/
void printLine(char Zeichen, int Anz)
{
    
    int i;
    
    for( i = 0; i < Anz; i++)
    {
        printf("%c", Zeichen);
    }
    
    printf("\n");

}


/**********************************
 
 *********************************/

int getText(char * Prompt, int Maxlen,  char ** Zeiger , int Bool) // Prompt = Eingabeaufforderung, Bool = 1 oder 0 -> Wahrheitswert
{
    char *Input = NULL;
    char Format[20];
    int ScanErg;
    int Len;
    
    
    if(Maxlen <= 0) // falls die eingegeben Maxlen kleiner gleuch Null ist => falsch
        return 0;
    
    if(Zeiger == NULL)
        return 0;
    
    *Zeiger = NULL;
    
    Input = calloc( Maxlen + 1, sizeof(char) );
    
    if(Input) // if Input != Null => Speicher wurde reserviert
    {
        sprintf(Format, "%%%i[^\n]", Maxlen); // Format[20] = "%Maxlen[^\n]",  %% = %, %i = Maxlen
        
        do
        {
            printf("%s: ",Prompt); // Ausgabe der Eingabeaufforderung
            ScanErg = scanf(Format, Input); // scanf("%Maxlen[^\n]", Input)
            clearBuffer();
            
            if(ScanErg == 1) // Falls der Benutzer etwas gültiges eingegeben hat ****Abfrage****
            {
                Len = (unsigned)strlen(Input); // die Länge der Text wird gezählt
                
                if(Len > 0)
                {
                    
                    *Zeiger = calloc (Len + 1, sizeof(char) ); // Speicher für genau der Eingegebene Text reservieren
                    
                    if(*Zeiger) // Speicher wurde reserviert
                    {
                        strcpy(*Zeiger, Input);
                    }
                    
                    else // der Speicher auf dem Zeiger zeigt wurde nicht reserviert
                    {
                        free(Input);
                        return 0;
                    }
                }
                
                else if(Bool) //Bool = AllowEmpty != 0 ->  prüft ob es sich um eine Pflichteingabe oder optional Eingabe händelt
                {
                    break; // man könnte auf free(Input) und return 1 schreiben
                }
            
                else
                    ScanErg = 0;
                
            }// Ende von ****Abfrage****
            
            else if(Bool) // Bool != 0
            {
                break;
            }
            
            else
                printf("Falsche Eingabe");
            
        } while( ScanErg == 0); // solange der Benutzer nichts eingegeben hast
        
        free(Input); //reservierter Speicher muss immer am Ende freigegeben werden
          return 1;
        
    }
    

    return 0;
}

