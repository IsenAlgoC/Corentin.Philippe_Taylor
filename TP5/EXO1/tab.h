#include <stdio.h>
#include <stdlib.h>
#define TAB2SIZE 20
#define TAILLEAJOUT 50
#define TAILLETABLEAU 10
#define NBAAFFICHER 7

/* Fonction qui assigne 0 à chaque variable pointée par les adresses du tableau 1 */
int initTab1(int* tab, int size) {
	if (tab == NULL && size <=0) {	 // on vérifie que le tableau n'est pas nul sinon on retourne -1
		return -1;
	}
	for (int i = 0; i < size; i++) {
		*(tab + i) = 0;              // on affecte 0 à la variable pointée par chaque adresse du tableau
	}
	return size;					 // on retourne la taille du tableau 
}

/* Fonction qui affiche le tableau 1 */
int afficheTab1(int* tab, int size, int nbElts) {
	if (tab == NULL && size <=0 && nbElts<=0) {		// on vérifie que le tableau n'est pas nul sinon on retourne -1
		return -1;
	}
	printf("le tableau est: ");
	for (int i = 0; i < nbElts; i++) {				// on affiche les valeurs du tableau sur une même ligne
		printf("%d ", *(tab + i));
	}
	printf("\n");
	return 0;
}

/* Fonction qui assigne une valeur différente à chaque variable pointée par les adresses du tableau 1 */
int initTab2(int* tab, int size) {   
	if (tab == NULL) {					// on vérifie que le tableau n'est pas nul sinon on retourne 0
		return 0;
	}
	for (int i = 0; i < size; i++) {		// on affecte des nombres croissant de 1 en 1 jusqu'à 20 à la variable pointée par chaque adresse du tableau
		*(tab + i) = i+1;
	}
    
	return size;						// on retourne la taille du tableau 
}

/* Fonction qui affiche le tableau 2 */
int afficheTab2(int* tab, int NbElts) {
	if (tab == NULL) {					// on vérifie que le tableau n'est pas nul sinon on retourne 0
		return 0;		
	}
	printf("le tableau est: ");
	for (int i = 0; i < NbElts; i++) {  // on affiche les valeurs du tableau sur une même ligne
		printf("%d ", *(tab + i));
	}
	printf("\n");
	return NbElts;
}

/* Fonction qui ajoute un element dans un tableau */
int ajoutElementDansTableau(int** tab, int *Size, int* NbElements, int Element) {
	if (*NbElements < *Size) {                   // si le nombre d'element est inferieur à la taille on peut juste rajouter un élement à la fin sans réallocation
		*(*tab + *NbElements) = Element;
		(*NbElements)+=1;
		return (*NbElements);
	}
	int* tab2 = (int*)realloc(*tab, (*Size + TAILLEAJOUT) * sizeof(int));   // sinon on réalloue de l'espace
	if (tab2 == NULL) { 
		return(-1); 
		}                                         // si cela échoue on renvoie-1
	*tab = tab2;
	*(*tab + *NbElements) = Element;                                      // et on ajoute l'element à la fin du tableau
	*Size += TAILLEAJOUT;                                                 // en mettant à jour la taille et le nombre d'elements
	(*NbElements)+=1;
	return (*NbElements);
}