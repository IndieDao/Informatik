#include <stdio.h>
#include <ctype.h>

//int Print(char *);
//int GetMax(int, int);
//int F1( char, int *);
//int F2( char);
//char F3( int);

//int ZaehleZiffern(char *);
int Strlen(char *);

void Trim( char *  );
int countSpace(char *);

int i, j;

int countSpaces(char *text)
{
    int Z = 0;
   while(*text++)
   {
       if (*text == ' ')
           Z++;
   }
   return Z;
}

void Trim(char *text)
{
    int end = Strlen(text) -1;

    while ((end >= 0) && (*(text+end)==' '))
    {
    *(text+end) = '\0';
    end--;
    }
}

int main()
{
    char Text[10][50] = {"Dies ist ein langer           ", "Text, der in mehreren       ", "Zeilen untergebracht          ", "ist und der auch noch            ", "in manchen Zeilen mehrere", "Leerzeichen am Ende       ", "beinhaltet! Die Leer-        ","zeichen dieses Textes       ", "sollen gezaehlt werden!       ", "                     "};

int leer = 0;
for (i = 0; i<= 10; i++)
    {
        Trim(*(Text+i));
        leer += countSpaces(*(Text+i));
    }

printf("\nIn dem Text sind %i Leerzeichen enthalten!\n", leer);

/*    char *Text = "Dieser 1 Text hat 5 Ziffern: 123!";

    printf("Im Text \n%s\n", Text);
    printf("sind %i Ziffern", ZaehleZiffern(Text));
    printf(" enthalten. \n");


int a = -1;

    printf("%cei", F3(F1('A', &a)));

    printf("%i",a);
    
    printf("%cp", F3(F3('q')));
    
    printf("%ce", F3(F1('g', &a)));
    printf("%i",a);
    
    printf("%ck", F1(F3('i'), &a));
    printf("%i",a);
    
    printf("%ca", 'k' * F3(F2('B')));
    
    printf("%cs", F3(F1('q', &a)));
    printf("%i",a);
    
    printf("%cr", F3(F1('p', &a)));
    printf("%i",a);
    

    int d = (1 ==3) + (5 == 5 );
    printf("%i\n", d);
    int b = 0, c = 15;
    char *Fehler = "Dies ist falsch!";
    
    for (b ; b<c ; b++)
    {
        printf("%s" , Fehler);
        printf("%i\n", GetMax(b, c)); 
    }
    printf("Fertig!  ");*/
    return 0;
}

int Strlen(char *text)
{
int len = 0;

while(*(text++) != '\0')
    {   
        len++;
    }
return len;
}

/*
int ZaehleZiffern(char *text)
{
int i = 0;
int Anzahl = 0;

for (i=0; i <= Strlen(text); i++)
    {
        if (*(text + i) >= '0' && *(text + i) <= '9')    
        {
            Anzahl++;
        }
    
    }
return Anzahl;
}

int F1(char Zeichen, int *Zahl)
{
    *Zahl += 1;
    return (Zeichen + *Zahl);
}

int F2 (char Zeichen)
{
--Zeichen;
return (Zeichen - 'A');
}

char F3(int Zahl)
{
return(Zahl += 1);
}

int Print(char *Text)
{
    return printf(Text);
}

int GetMax(int i, int j)
{
    return((i>j) ? j : i );
}
*/
