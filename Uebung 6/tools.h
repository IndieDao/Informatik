#ifndef TOOLS_H_INCLUDED
   #define TOOLS_H_INCLUDED
//#define MAX_APPOINTEMENTS 100
//  schreibt Teilstring (Token) bis zum Delimiter in den Zwischenstring tmp
//  und setzt die Zählvariable i auf den Wert, des nächsten Werts im Eingabestring
char *tmpToken( char *Eingabe, char Token);
//  Warteaufruf beendet durch die Eingabetaste
void waitForEnter();
//  druckt Linie aus gewünschten Zeichen, in gewünschter Länge
void printLine(char Zeichen, int Anzahl);

int askAgain(char *);
//  Zeichenpuffer loeschen
void clearBuffer();
//  loescht Text in Konsole
void clearScreen();
//  Eingabefunktion schreibt eingegebenen Text von temporärem Speicher in
//  exakt großen Speicherbereich und gibt die Adresse dieses Bereichs zurück.
int getText(char *, char **, unsigned int, int AllowEmpty); // Prompt = Eingabeaufforderung, Bool = 1 oder 0 -> Wahrheitswert
//  schreibt "falsche Eingabe" bei Aufruf
void falscheEingabe();


#endif
