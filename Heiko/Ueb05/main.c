#include <stdio.h>


int main()
{
  int  usrInputInt;
  char usrInputChar, foo;

  do
  {
   
    printf("Bitte geben Sie eine ganze Zahl ein: ");
    
    //Einlesen der Zahl
    if ((scanf("%d",&usrInputInt))!=1)
    {
      //Wenn kein Integer eingegeben wurde
      printf("Falsche Eingabe! Die Eingabe ist keine (ganze) Zahl!\n");
      //Nochmal? --> Springt zu MARK
    }
    else
    {
      printf("Sie haben die ganze Zahl %i eingegeben\n",usrInputInt);
    }
    do
    {
      scanf("%c",&foo);
    } while (foo !='\n');

    //MARK
    
    printf("Moechten Sie noch einmal (j/n)?\n");
    scanf("%c",&usrInputChar);


    while ( (usrInputChar != 'j') && (usrInputChar != 'n' ) && (usrInputChar != 'J') && (usrInputChar != 'N' ) )  //Bei Falscheingabe der yes/no-Abfrage
    {
      printf("Falsche Eingabe! Bitte 'j' oder 'n' eingeben!\n");
      foo = usrInputChar;
      while (foo != '\n')  //leeren des Puffers
      {
	scanf("%c",&foo);
      }
      scanf("%c",&usrInputChar);
    }
    foo = usrInputChar;
    while (foo != '\n')  //leeren des Puffers
    {
      scanf("%c",&foo);
    }
  } while ((usrInputChar != 'n') && (usrInputChar != 'N' ));

  printf("Programm wird beended.\n");

  return 0;
}
      
