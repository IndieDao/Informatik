#include <stdio.h>

int main()
{
    int zTest;
    int ganzeZahl;
    char pLoeschen;
    char Wieder = 'j';

    do 
    {
        // Eingabeaufforderung
        printf("\nGeben Sie bitte eine ganze Zahl ein: ");
        zTest = scanf("%d", &ganzeZahl);

        // Puffer loeschen
        do
        {
            scanf("%c", &pLoeschen);
        } while (pLoeschen != '\n');

        // Test auf falsche Eingabe
        if (zTest == 0)
            printf("falsche Eingabe! Keine ganze Zahl erkannt!\n");
        else
            printf("Sie haben die ganze Zahl %d eingegeben\n", ganzeZahl);

        // Programm Wiederholen?
        do
        {
            if (Wieder != 'j' && Wieder != 'J' && Wieder != 'n' && Wieder !='N')
                printf("\ngeben Sie bitte j oder n ein.\n");
            else
                printf("Moechten Sie noch einmal (j/n)?");
            scanf("%c", &Wieder);

            if (Wieder != '\n')
                do
                {
                    scanf("%c", &pLoeschen);
                } while (pLoeschen != '\n');

        } while (Wieder != 'j' && Wieder != 'J' && Wieder != 'n' && Wieder != 'N');
    } while (Wieder == 'j' || Wieder == 'J');

    printf("Programm wird beendet.\n");
    return 0;
}
