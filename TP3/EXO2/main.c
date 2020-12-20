#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


int main()
{
	unsigned int nb = 2868838400; // on initialise le nombre à tester
	int nbbit = log(nb) / log(2) + 1; // on calcule le nombre de bits nécessaires pour écrire notre nomnbre
	int i = 0; 
	int bit = 0; 

	printf("la taille d'un entier est %lu\n", sizeof(nb));
	printf("le nombre de bit est %d\n", nbbit);

	for(i=0;i<nbbit;i++) // on parcourt les bits de notre nombre
	{
		bit = nb & 1 << i; 
		if (bit != 0)
		{
			printf("bit %2d : ON\n", i); // on affiche ON si le bit est à 1
		}
		else
		{
			printf("bit %2d : OFF\n", i); // on affiche OFF si le bit est à 1
		}		
	}

	printf("Bye !"); 
	return 0;
}
