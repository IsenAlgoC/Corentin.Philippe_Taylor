#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 255

int main()
{
	char tab[SIZE];
	char tab2[SIZE];
	int sizetab;
	int k = 0;

	printf("Test palindrome : ");
	scanf("%s", tab);		// on récupère le mot à tester
	sizetab = strlen(tab);	// la variable sizetab prend la taille de la liste rentrée dans la console

	for (int i = 0; i < sizetab; ++i)	// on passe tous les caractères en majuscule
	{
		tab2[i] = toupper(tab[i]);
	}

	while (k <= (sizetab - 1 - k))		
	{
		if (tab2[k] != tab2[sizetab - 1 - k]) // on compare les caractères de notre liste de façon symétrique
		{
			printf("\n%s n'est pas un palindrome.\n", tab); // si les caractères sont différents alors en écrit dans la console que le mot n'est pas un palindrome
			return 1;
		}
		k += 1;
	}
	printf("\n%s est un palindrome.\n", tab); 
	return 0;
}