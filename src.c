/************************************************************/
/* Hausarbeit Elektrotechnik, Labor Informatik Hr. Kandziora*/
/* Matrikelnummer: 9026481									*/    
/* Master Mind												*/
/************************************************************/
#include <stdio.h>
#include <time.h> //Bibliotheken, für den Zufallszahlengenerator
#include <stdlib.h>


/* Funktion um einen zufälligen Code in das Array Schloss zu laden*/
void zufalls_Code_Generator(int schloss[5]);

/* Funktion zum Vergleichen von "Schloss" und "Schluessel" und pruefen
 * auf RWS + speichern der Anzahl im Schlüsselbund*/
void pruefen_RWS(int z, int schloss[5], int schluesselbund[10][7]);
	
/* Funktion zum vergleichen von Schloss und Schluessel, und pruefen
 * auf RW + speichern der Anzhal im Schlüsselbund*/
void pruefen_RW(int z, int schloss[5], int schluesselbund[10][7]);

/* Funktion zum Einlesen der vom Spieler eingegebenen Schluessel in den
 * richtigen Platz im Schluesselbund + prüfen auf korrekte Eingaben*/
int einlesen(int z, int schluesselbund[10][7]);

/* Funktion zur Ausgabe der bisherigen Eingaben
 * inklusive Auswertung auf RWS und RW */
void ausgeben(int z, int schluesselbund[10][7]);

/* Funktion für eine Runde des Spiels MasterMind*/
int spiel(int z, int schloss[5], int schluesselbund[10][7]);

int main(int argc, char **argv){
/* anlegen von "schloss" und "schluesselbund", im Schloss liegt der zu
 * erratendende Code. Im Schluesselbund werden Eingaben und Auswertungen
 * gespeichert.*/
	int schloss [5] = { 0 };
	int schluesselbund [10][7] = { 0 };
	int spielrunde, status;

	zufalls_Code_Generator(schloss);		
/* Schleife um bis zu 10 Runden zu spielen */
	for (spielrunde = 0; spielrunde < 10; spielrunde++){
		
		status = spiel(spielrunde, schloss, schluesselbund);

/* Neustarten der aktuellen Runde wenn Fehlerhafte Eingabe*/
		if (status == 2){
			while( getchar() != '\n') {};//Tastaurpuffer leeren
			spielrunde --;
		}
	}
	return 0;
}

void zufalls_Code_Generator(int schloss[5]){
	srand(time(NULL));
/* speichert 5 zufaellige  Zahlen von 1-5 in "schloss"*/
	for(int s=0;s<5;s++){
		schloss[s]=rand()%5 + 1;
	}
}

void pruefen_RWS(int z, int schloss[5], int schluesselbund[10][7]){
	
	int s, rws = 0;
	
		for(s=0; s<5; s++){
			if (schloss[s]==schluesselbund[z][s])
				rws++;
		}
/*speichert die Anzahl an RWS des aktuellen Schlüssels an der Stelle 5*/	
	schluesselbund[z][5] = rws;
}

void pruefen_RW(int z, int schloss[5], int schluesselbund[10][7]){
/* genauere Erlaeuterung der pruefen RW Funktion im Word Dokument*/
	int doppel[5]={ 0 };
	int sKey, sLock, rw = 0;
	
/* äußere Schleife geht den Schlüssel durch*/
	for(sKey=0; sKey<5; sKey++){
/* innere Schleife geht das Schloss durch*/
		for(sLock=0; sLock<5; sLock++){
/* Folgende If Abfrage überprüft, ob ein RW vorliegt*/
			if (schluesselbund[z][sKey]==schloss[sLock] &&
				schluesselbund[z][sLock]!=schloss[sLock] &&
				schluesselbund[z][sKey]!=schloss[sKey] &&
				doppel[sLock]== 0)
				{
					doppel[sLock]= 1;
					rw++;
/* sobald ein RW gefunden wird, bricht die aktuelle Schleife ab und die
 * nächste variable im Schluessel wird auf RW untersucht*/
					break;
				}
		}
	}
/*speichert die Anzahl der RW in der letzten Spalte im Schluesselbund*/
	schluesselbund[z][6]= rw;
}

int einlesen(int z, int schluesselbund[10][7]){
	
	int eingabe, korrekteEingabe = 0;
	
	printf("Ihre Eingabe: ");
	for(int s=0; s<5; s++){
/*Einlesen und ueberpruefen auf korrekte Eingaben (nur Zahlen von 1-5)*/
		korrekteEingabe = scanf("%d", &eingabe);
		if (0<eingabe && eingabe<6 && korrekteEingabe == 1){
				schluesselbund[z][s] = eingabe;
		}
		else{
			printf("Ungueltige Eingabe bitte geben "
					"Sie nur Zahlen von 1 bis 5 ein!\n");
			return 2;
		}
	}
/* leert den stdin Puffer, ansonsten wuerde es zu Problemen kommen,
 * wenn mehr als 5 Zeichen eingegeben werden*/
	while( getchar() != '\n') {};
	printf("\n");
	return 0;
}

void ausgeben(int z, int schluesselbund[10][7]){
	
	for(int i=0; i<z+1; i++){
			printf("      %d.Tipp: ", i+1);
		for(int s=0; s<5; s++){
			printf("%d ", schluesselbund[i][s]);//Ausgabe des Schlüssels
		}
		printf(" - %dRWS + %dRW\n", schluesselbund[i][5], schluesselbund[i][6]);
	}
}

int spiel(int z, int schloss[5], int schluesselbund[10][7]){
	if (einlesen(z, schluesselbund) == 2){ 
		return 2;//übergeben von '2' an Main bei Fehler
	}
	pruefen_RWS(z, schloss, schluesselbund);
	pruefen_RW(z, schloss, schluesselbund);
	ausgeben(z, schluesselbund);
	
	if(schluesselbund[z][5]==5){ //wenn 5 RWS im Schlüssel sind
		printf("Glueckwunsch - Sie haben die richtige "
			   "Ziffernfolge erraten!");
		exit(1);//Beenden des Programms
		}
		
/* Beenden das Spiel wenn nicht innerhalb von 10 Runden der passende
 * Schluessel gefunden wurde + ausgeben der Lösung*/
	if(z == 9){
		printf("\nSie haben es leider nicht geschafft den "
			   "Code zu erraten\n");
		printf("Der Loesungscode ist folgender gewesen: ");
		for(int s=0; s<5; s++)
		printf("%d ", schloss[s]);
	}
	return 0;
}
