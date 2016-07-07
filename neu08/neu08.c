#include <stdio.h>
#include <stddef.h>
#include "tools.h"
#include "escapesequenzen.h"

int main()
{
    int Zahl1, Zahl2, result, Dez, Okt, Hex, Bin;
    char Op, Dummy;

    do
    {
        printFrame();

        Zahl1 = getNumber(4);

        Op = getOperator(5);

        Zahl2 = getNumber(6);

        result = calcResult(Zahl1, Zahl2, Op);

        printResultNumber(11, Zahl1);

        printResultOperator(Op);

        printResultNumber(13, Zahl2);

        printResultNumber(15, result);
    }while (askAgain());
}
