#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"


 char *toFilename(char *date)
 {
    char *ch1;
    char cdate[6];
    int i = 0;
    ch1 = malloc(sizeof(char*)*11);

    if(ch1 == NULL) return NULL;

    while(i < 6)
    {
      cdate[i] = date[i+4];
      i++;
    }
    sprintf(ch1, "%s'.txt", cdate);

    return (char *)ch1;
 }


int getText(const char * Satz, const int laenge, char **Text, int leer)
{

   char *Input = calloc(laenge + 1, sizeof(char));
   char F[20];
   int Erg = 0, Len = 0, wahr = 0;

   if (Input)
   {
      printf("%s", Satz);
      sprintf(F,"%%%i[^\n]s", laenge);

      do
      {
         wahr = scanf(F, Input);
         clearBuffer();
         if ((!wahr)&&(!leer))
            printf("Bitte Irgendetwas eingeben!\n");

      } while((!wahr) && (!leer));


      Len = strlen(Input);
      if (Len > 0)
      {

         *Text = calloc(laenge + 1, sizeof(char));
         if (*Text)
         {
            strncpy(*Text, Input, laenge);
            Erg = 1;
         }
         else
            Erg = 0;
      }

      else
      {
         if (leer == 0)
         {
            Erg = 1;
            *Text = NULL;
         }
         else
            Erg = 0;
      }
   }
   else
      Erg = 0;

   free(Input);
   return Erg;
}


void clearBuffer()
{
	char trash;
	do
	{
		if(scanf("%c",&trash)  == 0)
            return;
	} while ( trash != '\n' );
}

int askYesOrNo(char *Question) {

	char input_value;
	int read = 0;


	do {
		printf("%s\n", Question);
		read = scanf("%c",&input_value);
		clearBuffer();

        switch( input_value ){
  			case 'j':
  			case 'J':   return 1;
  			case 'n':
  			case 'N':
                        return 0;
            default:
                        read = 0;
                        printf("Ungültige Eingabe!\n");
        }


  }while ( !read );

	return 0;
}

void printLine(char Icon, int Anz)
{
   int i;
   for (i = 0; i < Anz; i++)
      printf("%c", Icon);

   printf("\n");
}

void clearScreen()
{
    #ifdef __WIN32__
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

void waitForEnter() {
    printf("Bitte Eingabetaste druecken ...\n");
	clearBuffer();
}

int fakultaet(int x)
{
	if(x > 1)
		return x * fakultaet(x-1);
    else
 		return x;

}

void seekNewLineFILE(FILE * fp)
{
    char trash;
    int getOut = 0;

	do
    {
        fscanf( fp, "%c", &trash );
        if ( ( trash == '\n') || ( feof( fp ) ))
            getOut = 1;

	} while (!getOut);

}
