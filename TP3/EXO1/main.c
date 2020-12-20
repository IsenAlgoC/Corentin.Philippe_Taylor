#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define CARRE(x) (x)*(x) // on définie le calcul du carré 

int main()
{
	int nb = 5; // on initialise le nombre pour lequel on veut calculer le carré
	printf("le carre de 5 est %d\n", CARRE(nb)); // on affiche le carré de nb
	printf("le carre de nb+1 est %d\n", CARRE(nb+1)); // on rajoute des parenthèses de la define pour éviter d'avoir des problèmes de prioroté de calcul
	return 0;
}
