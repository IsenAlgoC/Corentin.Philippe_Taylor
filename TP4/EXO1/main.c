#include <stdlib.h>
#include <stdio.h>
#include "tp4.h"

int main()
{
	HEURE HeureDebut, HeureFin, Duree;
	HeureDebut.heure = 12; HeureDebut.minute = 30; // on definit l'heure et minute de la variable HeureDebut
	HeureFin.heure = 00; HeureFin.minute = 00;     // on definit l'heure et minute de la variable HeureFin
	Duree.heure = 00; Duree.minute = 45;           // on definit l'heure et minute de la variable Duree
	HeureFin.heure = (HeureDebut.heure + Duree.heure + ((int)(HeureDebut.minute + Duree.minute) / 60)) % 24;  // on calcule les heures de l'heure de fin par rapport à l'heure de début et à la durée
	HeureFin.minute = (HeureDebut.minute + Duree.minute) % 60; 	 // on calcule les minutes de l'heure de fin
	printf("HeureDebut > %d:%d\n", HeureDebut.heure, HeureDebut.minute);
	printf("Duree      > %d:%d\n", Duree.heure, Duree.minute);
	printf("HeureFin   > %d:%d\n", HeureFin.heure, HeureFin.minute);
	return 0;
}