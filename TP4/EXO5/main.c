#include <stdlib.h>
#include <stdio.h>
#define SIZE 1024


int main()
{
	char tab[SIZE];
	int letters = 0;
	int nb_words = 0;
	int i = 0;
	float long_moyenne = 0;

	printf("Ecrivez une phrase : "); // on récupère la phrase à etudier
	gets(tab); 
	
	while (tab[i] != '\0') { // tout le temps qu'on ne se trouve au dernier élément de la liste
	
		if ((tab[i] == ' ') || ((tab[i] == 39) && (tab[i + 1] != ' '))) {	// dès qu'on trouce un espace ou un apostrophe alors on compte un mot suplémentaire
			nb_words+=1;
			}

		else if ((tab[i] < 'A') || ((tab[i] > 'Z') && (tab[i] < 'a')) || (tab[i] > 'z')) {	// autrement s'il y a un caractère différent d'une lettre on ne fait rien
			}

		else {		// autrement si le caractère est une lettre on compte une lettre supplémentaire
			letters+=1;
			}
		i+=1;
	}
	
	nb_words+=1;
	long_moyenne = ((float)letters) / ((float)nb_words); // on calcule la longeuer moyenne d'un mot
	printf("\nIl y a %d mots et la longueur moyenne des mots est de %.2f caracteres.\n", nb_words, long_moyenne);
	printf("%s",tab);
	return 0;
}