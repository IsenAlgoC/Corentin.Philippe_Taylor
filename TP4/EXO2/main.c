#include <stdlib.h>
#include <stdio.h>
#define SEPARATEUR '/'
#define TAILLETAB1 20

int main()
{
	
	int MyTab1[TAILLETAB1];
	char MyPtr1 = TAILLETAB1 - 1;
	char ptr;
	int valeur;

	MyTab1[0] = 1;				// on affiche la première valeur de notre tableau
	printf("%d", MyTab1[0]);	// ces deux lignes ont été rajouté pour éviter qu'un / s'affiche après la dernière valeur du tableau 
	for (int i = 1; i < TAILLETAB1; ++i)
	{
		MyTab1[i] = i + 1;
		printf("%c%d", SEPARATEUR, MyTab1[i]);		// on affiche le reste des valeurs avec un / avant chaque valeur
	}
	printf("\n");

	ptr = MyPtr1;
	valeur = *(MyTab1 + ptr);
	MyPtr1 -= 1;
	printf("%d", valeur);			// ces quatre lignes ont été rajouté pour éviter qu'un / s'affiche après la dernière valeur du tableau 
	for (int j = 1; j < TAILLETAB1; ++j)
	{
		ptr = MyPtr1;
		valeur = *(MyTab1 + ptr);
		printf("%c%d", SEPARATEUR, valeur);
		MyPtr1 -= 1;
	}
	return 0;
} 