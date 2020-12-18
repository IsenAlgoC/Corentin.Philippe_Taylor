#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "liste.h"

// #define VERSION 3.0
// #define SQUELET


// crée une nouvelle liste chainée unilataire vide et renvoie un pointeur sur cette liste
LinkedList *NewLinkedList() {
	LinkedList *tmp;			// on crée un pointeur d'élément de type LinkedList
	tmp = (LinkedList*)malloc(sizeof(LinkedList)); // on alloue la mémoire nécessaire à la création d'une liste chaînée
	if (tmp != NULL) {			// si l'allocation a réussi 
		tmp->head = NULL;		// on fait pointer la tête et la queue de notre liste à l'adresse NULL
		tmp->tail = NULL;
		tmp->size = 0;			// la taille de la liste est égale à 0
	}
	return tmp;
}
// crée un nouveau maillon qui contient la personne passée en paramètre
SingleLinkedListElem  *NewLinkedListElement(Enregistrement pers) {
	SingleLinkedListElem *tmp;	// on crée un pointeur d'élément de type SingleLinkedListElem
	tmp = (SingleLinkedListElem *)malloc(sizeof(SingleLinkedListElem)); // on alloue la mémoire nécessaire à la création d'un nouveau maillon dans la chaîne
	if (tmp != NULL) {			// si l'allocation a réussi 
	tmp->pers = pers;			// notre nouveau maillon prend comme valeur l'élément en argument de la fonction
	tmp->next = NULL;			// notre nouveau maillon pointe vers l'adresse NULL
	}
	return(tmp);
}
// renvoie un pointeur sur l'élément en ième position dans la liste
SingleLinkedListElem *GetElementAt(LinkedList *Liste, int i) {
	int CurrentIndex = 0;
	SingleLinkedListElem *Element;	// on crée un pointeur d'élément de type SingleLinkedListElem
	if ((Liste == NULL) || (i < 0) || (i > Liste->size)) return(NULL); // si la liste est vide ou que l'indice en argument est inférieur à 0 ou que l'indice est supérieur à la taille de la liste on revoie 0
	if (i == 0) return(Liste->head);	// si l'indice est égal à 0 on revoie la tête de la liste
	if (i == Liste->size - 1) return(Liste->tail);		// s'il est égale à la taille de la liste - 1 on revoie la queue de la liste
	Element = Liste->head;		// autrement notre élément prend la valeur de la tête de liste
	while (CurrentIndex != i  && Element != NULL) { 	// tout le temps que CurrentIndex est différence de l'indice en argument et que Element ne pointe pas vers l'adresse NULL
		Element = Element->next; 	// Element devient l'élément vers lequel il pointe
		CurrentIndex++;
	}
	return(Element);
}

// Ajoute une nouvelle personne dans la liste chaînée en ième position
// Cette fonction fait appel à la fonction NewLinkedListElement(Enregistrement pers) pour créé
// FONCTION A COMPLETER AUX ENDROITS INDIQUES

int InsertElementAt(LinkedList *Liste, int i, Enregistrement pers) {
	SingleLinkedListElem *CurrentElement, *NewElement;
	if (Liste == NULL) return(0);
	// recherche de l'élément qui se trouve déjà en position i
	CurrentElement = GetElementAt(Liste, i);
	// s'il y en a un
	if (CurrentElement != NULL) {
		// on insère un nouvel élément
		NewElement = NewLinkedListElement(pers);
		// son suivant est alors l'élément courant
		NewElement->next = CurrentElement;

		if (i == 0) {
			// si l'insertion est en tête
			// le nouvel élément devient la tête
			Liste->head = NewElement;
		}
		else {
			// sinon il faut rétablir le chainage depuis l'élément précédent
			CurrentElement = GetElementAt(Liste, i - 1);
			// le successeur du précédent devient le nouvel élément
			CurrentElement->next = NewElement;
		}
		Liste->size++;
		return(1);
	}
	else {
		if (Liste->size == 0) { // si la taille de la liste est nulle
			NewElement = NewLinkedListElement(pers);  // on insère un nouvel élément
			if (NewElement != NULL) { 		// si l'allocation dans la fonction NewLinkedListElement a fonctionné
				Liste->head = NewElement;	// alors la tête est la queue de la liste deviennent le même élément
				Liste->tail = NewElement;
				Liste->size++;
				return(1);
			}
			else {
				return(0);
			}
		}
		if (Liste->size <= i) { // si la taille de liste est inférieure à l'indice en argument
			NewElement = NewLinkedListElement(pers);	// on insère un nouvel élément
			if (NewElement != NULL) {		// si l'allocation dans la fonction NewLinkedListElement a fonctionné
				Liste->tail->next = NewElement;		// alors la queue actuelle de la liste pointe vers le nouvel élément
				Liste->tail = NewElement;			// la queue prend la valeur du nouvel élément
				Liste->size++;
				return(1);
			}
			else {
				return(0);
			}
		}
	}
	return(0);
}
//
// Suppression d'un élément de la liste chaînée
//
int DeleteLinkedListElem(LinkedList *list, SingleLinkedListElem * item) {
	if (list == NULL) return(0); // La liste n'existe pas
	if ((list->head == NULL) || (list->tail == NULL)) return(0); // liste vide ou anomalie
	if ((list->head == list->tail) && (list->size != 1)) return(0); // anomalie
	if ((list->size == 0) || (item == NULL)) return(0); // pas d'élément dans la liste ou item invalide

	SingleLinkedListElem *ActualElement;
	if (item == list->head){  // si l'élément a suprimmer est la tête de liste
		list->head = item->next;	// alors la tête prend la valeur de l'élément vers lequel notre élément en argument pointe
		free(item);		// on libère l'espace en mémoire utlisée par l'élément à supprimer
		list->size--;	// la taille de la liste est réduite
		return(1);
	}
	else {
		ActualElement = list->head;  
		while (ActualElement->next != item) {    // on parcourt les maillons de la liste jusqu'à trouver celui qui nous intéresse
			ActualElement = ActualElement->next;
		}
		ActualElement->next = ActualElement->next->next;   // une fois le bon maillon trouvé il pointe à l'adresse à laquelle l'adresse où il pointe pointe
		free(item);     // on libère l'espace en mémoire utlisée par l'élément à supprimer
		list->size--;	// la taille de la liste est réduite
		return(1);
	}
	return(0);  // pas trouvé
}

