#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 100

int afficherTab(int tab[], int tabSize, int nbVal)
{
	int k = 0;
	if ((tabSize >= nbVal) && ((tabSize < SIZE) || (tabSize > 0)) && (nbVal > 0))
	{
		for (int l = 0; l < 10; l++) // on écrit notre en 10 lignes et 10 colonnes dans le tableau
		{
			for (int m = 0; m < 10; m++)
			{
				if (tab[k] < 10)
				{
					printf(" %d ", tab[k]); // on écrit la valeur du tableau dans la console avec un espace en plus si il s'agit d'un chiffre et nom d'un nombre
				}
				else
				{
					printf("%d ", tab[k]);
				}
				k++;
			}
			printf("\n");  // tous les 10 éléments on passe à la ligne suivante
		} 
		return nbVal;
	}
	else
	{
		return -1;
	}
}

int main()
{

	int tab[SIZE],mem[SIZE], val, cmpt = 0;		
	char curseur = tab[0];

	srand(time(NULL));	
	for (int i = 0; i < SIZE; ++i)
	{
		tab[i] = rand() % 20 + 1;	// remplis le tableau de valeurs aleatoires à l'aide de la valeur de la date à laquelle on lance le programme
	}
	afficherTab(tab, SIZE, SIZE);
	printf("\n");
	printf("Entrez la valeur recherchee : ");
	scanf("%d", &val);		
	for (int j = 0; j < SIZE; ++j)	// parcourt toutes les valeurs du tableau
	{
		curseur = tab[j];
		if (curseur == val)		// si la valeur est la même que celle recherchée alors on ajoute 1 à notre compteur ainsi que la position de la valeur à la liste mem
		{
			mem[cmpt] = j;
			++cmpt;
		}
		++curseur;
	}
	if (cmpt == 0)
	{
		printf("\n%d n'apparait pas dans la liste.\n", val);  // si le compteur est nul alors la valeur n'apparaît dans le tableau
	}
	else
	{
		printf("La valeur %d a ete trouvee en %d", val, mem[0] + 1);	// autrement on affiche le nombre de fois où il apparaît et à quelle position
		for (int k = 1; k < cmpt; ++k)
		{
			printf(" puis en %d", mem[k]);
		}
		printf(".\n");
	}
	return 0;
}