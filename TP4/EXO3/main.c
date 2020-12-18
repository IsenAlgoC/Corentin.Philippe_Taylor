#include <stdio.h>

int main ()
{
	char nom[20];
	char prenom[20];
	char sexe;

	puts ("\nVotre sexe : (H)omme ou (F)emme");
	sexe=getchar();		// on récupère la sexe de la personne à l'aide d'un getchar
	printf("Votre nom : ");
	scanf("%s", nom);
	printf("Votre prénom : ");
	scanf("%s", prenom);	// on récupère son nom et prénom à l'aide de scanf

	if (sexe == 'H') {
		printf("\nMonsieur %s %s\n", nom, prenom);
	}
	else if (sexe == 'F') {
		printf("\nMadame %s %s\n", nom, prenom); 	// on écrit dans la console en fonction du sexe de la personne 
	}
	else {
		printf("\nERROR\n");
	}
	return 0;
}