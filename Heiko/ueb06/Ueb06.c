#include <stdio.h>
#include <math.h>
#include "escapesequenzen.h"
// aus dem Skript "Grundlagen der Informatik", Kap. 6.3
int main()
{
  char Dummy; // für Tastaturpuffer-Löschen
  int Menuewahl; // Benutzereingabe Menüauswahl
  int Eingabe; // Ergebnis von scanf
  double X; // Laufvariable
  double X_Von, X_Bis; // Ausgabegrenzen
  double X_Schrittweite; // Ausgabeschrittweite
  do
  {
    // Menue ausgeben
    CLEAR; // Bildschirm löschen
    HOME;
    printf("Sinus & Co.\n");
    printf("===========\n\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. tan(x)\n");
    printf("9. Programmende\n\n");
    // Benutzereingabe Menue
    do
    {
      POSITION(9, 1); // Eingabezeile löschen
      CLEAR_LINE;
      POSITION(9, 1);
      printf("Ihre Wahl: ");
      Eingabe = scanf("%i", &Menuewahl);
      do // Tastaturpuffer loeschen
	scanf("%c", &Dummy);
      while (Dummy != '\n');
      if (Eingabe) // wenn Zahl eingegeben
      { // dann pruefen, ob gueltig
	POSITION(11, 1);
	switch(Menuewahl)
	{
	case 1: printf("SINUS\n-----\n"); break;
	case 2: printf("COSINUS\n-------\n"); break;
	case 3: printf("TANGENS\n-------\n"); break;
	case 9: printf("PROGRAMMENDE\n\n"); break;
	default: Eingabe = 0;
	}
      }
    } while (!Eingabe); // solange bis gültiger
    // Menüpunkt gewählt wurde
    if (Menuewahl != 9) // außer bei Programmende
    {
      // Startwert erfragen
      do
      {
	POSITION(14, 1); // Eingabezeile löschen
	CLEAR_LINE;
	POSITION(14, 1);
	printf("Von x = ");
	Eingabe = scanf("%lf", &X_Von);
	Seite
	  2
	  von
	  3
	  G. Kempfer, BHT Berlin, TI-B IN1, Übungsblatt 6
	  do // Tastaturpuffer loeschen
	    scanf("%c", &Dummy);
	  while (Dummy != '\n');
      } while (!Eingabe); // solange bis gültige Eingabe
      // Endwert erfragen
      do
      {
	POSITION(15, 1); // Eingabezeile löschen
	CLEAR_LINE;
	POSITION(15, 1);
	printf("Bis x = ");
	Eingabe = scanf("%lf", &X_Bis);
	do // Tastaturpuffer loeschen
	  scanf("%c", &Dummy);
	while (Dummy != '\n');
	if (Eingabe)
	  if (X_Von > X_Bis) // Ausgabegrenzen prüfen
	    Eingabe = 0;
      } while (!Eingabe); // solange bis gültige Eingabe
      // Schrittweite erfragen
      do
      {
	POSITION(16, 1); // Eingabezeile löschen
	CLEAR_LINE;
	POSITION(16, 1);
	printf("Schrittweite = ");
	Eingabe = scanf("%lf", &X_Schrittweite);
	do // Tastaturpuffer loeschen
	  scanf("%c", &Dummy);
	while (Dummy != '\n');
      } while (!Eingabe); // solange bis gültige Eingabe
      // Werte ausgeben
      POSITION(18, 1);
      printf(" X | f(x)\n");
      printf("---------|---------\n");
      for (X = X_Von; X <= X_Bis; X += X_Schrittweite)
      {
	switch(Menuewahl)
	  {
	  case 1: printf("%f | %f\n", X, sin(X)); break;
	  case 2: printf("%f | %f\n", X, cos(X)); break;
	  case 3: printf("%f | %f\n", X, tan(X)); break;
	  }
      }
      // Eingabetaste abwarten
      printf("\nBitte Eingabetaste druecken ...");
      do
	scanf("%c", &Dummy);
      while (Dummy != '\n');
    }
  } while (Menuewahl != 9); // solange bis Programmende
  return 0;
}
