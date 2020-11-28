#include <stdio.h>
#include <stdlib.h>
#include "tab.h"

/* Fonction main appelle toutes les fonctions */
int main(int argc, char *argv[]) {
	int MyTab1[15];											// notre premier tableau est initialisé avec 15 valeurs 
	initTab1(MyTab1, TAILLETABLEAU);						
	afficheTab1(MyTab1, TAILLETABLEAU, NBAAFFICHER);	
	int* MyTab2 = malloc(TAB2SIZE * sizeof(int));			// on alloue manuellement de la mémoire à notre tableau
	if (MyTab2 != NULL) { initTab2(MyTab2, TAB2SIZE); }		// on vérifie que l'allocation de la mémoire a bien fonctionné
	else {													// si non on renvoie le message "mémoire insuffisante"
		printf("memoire insuffisante");
		return(-1);
	}
	int taille = 100;
	int nb = TAB2SIZE;
	printf("le nombre d'éléments doit etre de 21 et est de %d\n", ajoutElementDansTableau(&MyTab2, &taille, &nb, 21)); // on ajoute 21 à notre tableau 
	afficheTab2(MyTab2, nb);
	free(MyTab2);											// on libère la mémoire demandée précédemment par la fonction malloc
}
