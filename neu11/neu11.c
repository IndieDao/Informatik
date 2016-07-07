#include <stdio.h>
#include"limit.h"
#include"tools.h"

int main()
{
    unsigned char Text[MAX];
    unsigned int Anzahl[ASCIIMAX];
    unsigned int Stringlaenge;
    do
    {
        printInputMask();
        getText(Text);
        Stringlaenge = (countInAscii(Text, Anzahl));
        printCounted(Anzahl, Stringlaenge);
    } while(askAgain());
    return 0;
}
