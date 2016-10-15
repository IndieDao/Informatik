#include <stdio.h>
#include "text.h"
#include "tools.h"
#include "escapesequenzen.h"

//fgetpos fsetpos fwrite

void getText(char *Anweisung, char *EingabeSatz)
{
    printf(Anweisung);
    do
    {
        POSITION(4, 1);
        fgets(EingabeSatz, 200, stdin);
   } while (*(EingabeSatz) == 10);
}

void getWidth(char *Anweisung, int minBreite, int maxBreite, int *EingabeBreite)
{
    int korrekteEingabe = 0;

    printf(Anweisung, minBreite, maxBreite);

    do
    {
        POSITION(7, 1);
        CLEAR_LINE;
        korrekteEingabe = scanf("%d", EingabeBreite);
    }while (!(*EingabeBreite >= minBreite && *EingabeBreite <= maxBreite) && printf("Eingabe ausserhalb des gueltigen Bereichs") && korrekteEingabe);
}

void printText(char *EingabeSatz, int Breite)
{
    int i = 0;
    int j = 0;
    int k = 1;
    int l = 0;
    int m = 0;
    int UmbruchMoeglich[201] = {[0 ... 200] = 0};

    POSITION(9, 1);
    while (*(EingabeSatz + i))
    {
        if ((*(EingabeSatz + i) >= 'A' && *(EingabeSatz +i) <= 'Z') || (*(EingabeSatz +i) >= 'a' && *(EingabeSatz + i) <= 'z'))
        {
            *(UmbruchMoeglich + j) = 2;
            k++;
        } else
        {
            *(UmbruchMoeglich + j) = 1;
            k = 0;
        }
        if(!(k % Breite))
        {
            *(UmbruchMoeglich + j) = 3;
        }
        j++;
        i++;
    }

    printf("|");
    for (m = 0; m != Breite - 2; m++)
    {
        printf("-");
    }
    printf("|\n");

    if (i <= Breite)
    {
        printf("%s", EingabeSatz);
    } else
    {
        while (*(UmbruchMoeglich + l))
        {
            switch (*(UmbruchMoeglich +l))
            {
                case 1: printf("%c\n", *(EingabeSatz +l)); break;
                case 2: printf("%c", *(EingabeSatz + l)); break;
                case 3: printf("\n"); break;
            }
            l++;
        }
    }
}

