#include <stdio.h>
#include <stdlib.h>
#define TAILLEINITIALE 20

/* Creation du type tableau */
typedef struct Tableau
{
	int* elt;// le tableau d'entiers
	int size;// la taille de ce tableau d'entiers
	int eltsCount;// le nombre d'éléments dans le tableau
}TABLEAU;

/* Initialisation des fonctions*/
TABLEAU NewArray();
int IncrementArraySize(TABLEAU* tab, int IncrementValue);
int SetElement(TABLEAU* tab, int pos, int Element);
int DisplayElements(TABLEAU* tab, int StartPos, int EndPos);
int DeleteElements(TABLEAU* tab, int StartPos, int EndPos);

/* Fonction creation de tableau */
TABLEAU NewArray() {
	TABLEAU tableau;
	tableau.elt = malloc(TAILLEINITIALE * sizeof(int));			// on alloue de la mémoire pour notre tableau
	if (tableau.elt != NULL) {									// on vérifie que l'allocation a bien fonctionnée avant de continuer
		tableau.size = TAILLEINITIALE;
		tableau.eltsCount = 0;
		return tableau;
	}
	else {
		printf("Mémoire insuffisante\n");
		return tableau;
	}
}

/* Fonction qui augmente la taille d un tableau */
int IncrementArraySize(TABLEAU* tab, int IncrementValue) {
	int* tab2 = realloc(tab->elt, (tab->size + IncrementValue) * sizeof(int));  // on réalloue de la mémoire à hauteur de l'ancienne place + la place qu'on veut rajouter
	if (tab2 == NULL) { 
		return(-1); 
		}                                                  // si la réallocation echoue on renvoit 0
	tab->elt = tab2;                                       // sinon on affecte le nouvel emplacement mémoire
	tab->size += IncrementValue;                           // on met à jour la nouvelle taille du tableau
	return (tab->size);									   // on renvoie la taille du tableau 
}

/* Fonction qui insere une element a une pos donne */
int SetElement(TABLEAU* tab, int pos, int Element) {
	if (pos < tab->eltsCount) {                             		  // si la position est déjà dans le tableau on remplace juste l'ancien élément par le nouveau
		*(tab->elt + pos) = Element;
		return pos;
	}
	int* tab2 = (int*)realloc(tab->elt, (pos + 1) * sizeof(int));     // sinon on réalloue de la mémoire pour pouvoir le placer
	if (tab2 == NULL) { return(0); }
	tab->elt = tab2;
	for (int i = tab->eltsCount; i <= pos - 1; i++) {                 // on remplace tous les emplacements entre l'ancienne fin du tableau et la position par 0
		*(tab->elt + i) = 0;
	}
	*(tab->elt + pos) = Element;                                      
	tab->size = pos + 1;                                              // on met à jour la taille et le nombre d'elements du tableau
	tab->eltsCount = pos + 1;
	return pos;
}

/* Fonction qui affiche une partie du tableau en fonction d une position de debut et de fin */
int DisplayElements(TABLEAU* tab, int StartPos, int EndPos) {
	if ((StartPos >= 0) && (EndPos < tab->size) && (EndPos >= StartPos)) {   // on vérifie la validité des paramètres en entrée
		for (int i = StartPos; i <= EndPos; i++) {                           // on affiche les elements du tableau entre StartPos et EndPos
			printf("%d ", *(tab->elt + i));
		}
		printf("\n");
		return 0;
	}
	return -1;
}

/* Fonction qui suprime un element et met a jour la taille du tableau */
int DeleteElements(TABLEAU* tab, int StartPos, int EndPos) {
	int j = 0; 																		// initialisation de l'indice de la liste raccourcie
	int* tab2 = (int*)malloc((tab->size - (EndPos - StartPos) - 1) * sizeof(int));  // on réalloue la memoire necessaire au traitement
	if (tab2 == NULL) { return(-1); }
	for (int i = 0; i <= tab->size - 1; i++) {
		if ((i < StartPos) || (i > EndPos)) {
			*(tab2 + j) = *(tab->elt + i);                                          //on copie chaque element du tableau dans la copie lorsque son indice correspond aux paramètres d'entrée
			j+=1;                                                                   //quand on rajoute un element on incremente l'indice de la copie pour la remplir au fur et à mesure
		}
	}
	tab->size -= (EndPos - StartPos) + 1;
	tab->eltsCount -= (EndPos - StartPos) + 1;
	tab->elt = tab2;
	return(tab->size);
}

/* Appel des fonctions dans le main */
int main() {
	TABLEAU tableau = NewArray();
	for (int i = 1; i <= tableau.size ; i++) {         //initialisation du tableau avec pour valeur l'indice (afin de bien voir les modifications)
		*(tableau.elt + i) = i;
	}
	tableau.eltsCount = TAILLEINITIALE;
	SetElement(&tableau, 11, 20);        			   // on remplace un élément de la liste
	SetElement(&tableau, 29, 20);                      // on rajoute un élément en dehors de la liste
	DisplayElements(&tableau, 0, tableau.size - 1);    // on affiche le tableau pour vérifier que la fonction SetElements fonctionne bien
	DeleteElements(&tableau, 10, 25);	               // on supprime une partie du tableau
	DisplayElements(&tableau, 0, tableau.size - 1);    // n affiche le tableau pour vérifier que la fonction DeleteElements fonctionne bien
	printf("%d\n", tableau.size);                      // taille avant réalloc
	int a = IncrementArraySize(&tableau, 10);		   // on augmente le nombre d'octets de notre tableau
	printf("%d\n", a);                                 // taille après réalloc correcte
	free(tableau.elt);								   // on libère l'espace utilisé par notre tableau 
}