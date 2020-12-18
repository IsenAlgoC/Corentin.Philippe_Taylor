#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caractères */
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"
#include <errno.h>
#define VERSION 3.0
#define SQUELET
#define _countof(a) (sizeof(a)/sizeof(*(a)))
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : Philippe-Taylor                  Prénom : Corentin             */
/**************************************************************************/

// Je travaille sur mac d'où l'absence de sécurisation à l'aide de _s pour les fonctions utilisées

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	int idx;

	if (rep->nb_elts < MAX_ENREG)			// on vérifie qu'il n'y a pas délà trop de contact ajoutés dans le répertoire
	{
		*(rep->tab + rep->nb_elts) = enr; 	// on ajoute le nouvrau contact à la fin de notre tableau
		rep->nb_elts += 1;					// le nombre de contacts augmente donc de 1
		modif = true; 						// une modification a été efféctué 
	}
	else {
		return(ERROR);						// si trop de contact dans notre répertoire on retourne ERROR
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;				
	if (rep->nb_elts == 0) {				// si la liste chaînée est vide
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) { 	// et que la fonction qui insert un nouvel élément dans liste chaînée ne revoit pas 0
			rep->nb_elts += 1; 				// le nombre d'éléments augmente de 1
			modif = true;					// une modification a été efféctue
			rep->est_trie = true;			// la liste est triée car il n'y a qu'un seul élément dans la liste
			return(OK);
		}

	}
	else {
		int k = 0;
		while (k < rep->nb_elts){			// on compare notre nouvel élément à tous les éléments déjà présent dans la liste
			if (est_sup(enr, ((GetElementAt(rep->liste, k)->pers))) == false) {		// si le nouvel élément se trouve avant dans l'odre alaphabétique que l'élément avec lequel on le compare
				InsertElementAt(rep->liste, k, enr); 	// on insère donc l'élément à cet emplacement dans la liste chaînée
				rep->nb_elts++;                     	// le nombre d'éléments augmente de 1
		 		modif = true;                      		// une modification a été effectué
				rep->est_trie = true;                   // la liste est triée
				return(OK);
				}
			k++;
			}
		}

#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramêtre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {
	int i;
	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		// on vérifie qu'il y a au moins un élément dans le répertoire
	{					
		if (rep->nb_elts <= indice <= 0) {					// on vérifie que l'indice est positif est pas supérieur au nombre d'éléments du répertoire 
			for (i = indice ; i < rep->nb_elts ; i++){		// on parcourt toutes les éléments après l'éléments que nous voulons supprimer
				*(rep->tab + i) = *(rep->tab + i+1); 		// et on décale chaque élément de 1 vers la gauche 
			}
			rep->nb_elts -= 1; // un élément a été supprimé du tableau
			modif = true;	   // une modification a été effectué
		}	
		else {
			return ; 
		}	
		
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem); // on appelle la fonction DeleteLinkedListElem pour supprimer un élément dans la liste chaînée
	if (ret == 1) { 		// si la fonction revoie 1
		rep->nb_elts--;		// alors la suppression a focnitonné donc le nombre d'éléments est réduit de 1
		modif = true; 		// une modification a été effectué
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s %s %s", enr.nom, enr.prenom, enr.tel);		// on affcihe sur un même ligne le nom, le prénom et la numéro de téléphone d'un contact lorsque la fonction est appelée

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	int i;
	printf("| %-30s | %-30s | %-20s \n", enr.nom, enr.prenom, enr.tel);		// on affcihe sur un même ligne et en les alignant le nom, le prénom et la numéro de téléphone d'un contact lorsque la fonction est appelée
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	int i = 0, lon_max;
	if (strlen(enr1.nom) > strlen(enr2.nom)){  // pour nous éviter des problèmes de dépassement de "range" 
		lon_max = strlen(enr2.nom);			   // on fixe la longueur max de nos deux liste à comparer à la valeur de la plus petite des deux
	}										 
	else {
		lon_max = strlen(enr1.nom);
	}
	while (i <= lon_max){				   	   // on parcourt tous les caractères jusqu'au dernier caractère de la plus petite liste
		if (enr1.nom[i] == enr2.nom[i]) {	   // si les deux lettres compararées sont les mêmes on passe aux lettres suivantes
			i++;
		}
		else if (enr1.nom[i] < enr2.nom[i]){   // si la lettre de la première liste est avant la lettre de la deuxième dans l'ordre alphabétique
			return(false); 					   // on retourne false
		}
		else if (enr1.nom[i] > enr2.nom[i]){   // si la lettre de la première liste est après la lettre de la deuxième dans l'ordre alphabétique
			return(true);					   // on revoie true 
		}
	}
	return(true);
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	int i, j;
	Enregistrement permut;
	if (rep->nb_elts > 1){  			// on vérifie qu'il y a plus qu'un contact dans le répertoire 
		for (j = 0 ; j < rep->nb_elts ; ++j){ 		// à l'aide d'un trie à bulle
			for (i = 0; i < rep->nb_elts - 1 ; i++){ 		// c'est à dire deux boucles qui permettent de comparer tous les contacts entre eux 
				if (est_sup(rep->tab[i],rep->tab[i+1]) == true){ 		// si la fonction est_sup revoie true
					permut = *(rep->tab + i);		// on échange de place les deux contatcs comparés
					*(rep->tab + i) = *(rep->tab + (i+1));
					*(rep->tab + (i+1)) = permut;
				}
			}
		}
	}

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		
	strncpy(tmp_nom, nom, (_countof(tmp_nom)-1));

	ind_fin = rep->nb_elts; // l'indice de fin le nombre d'élément dans le répertoire comme valeur

#ifdef IMPL_TAB
	while ((i <= ind_fin) && (!trouve))		// tout le temps que i est inférieur au nombre d'élément et que le nom cherché n'est pas trouvé 
	{
		strncpy(tmp_nom2, rep->tab[i].nom, (_countof(tmp_nom2)-1));		// la liste tmp_nom2 prend le nom se trouvant à l'indice i
		if (strcmp(tmp_nom, tmp_nom2) == 0)		// on compare cette liste avec notre liste en argument de la focntion
			trouve = true;		// si elles sont exactement pareil alors on passe l'élément "trouve" à true pour sortir de la boucle
		else
			i++;
	}
	
#else
#ifdef IMPL_LIST
	while ((i <= ind_fin) && (!trouve))		// même principe qu'en travaillant avec des tableaux 
	{										
		strncpy(tmp_nom2, GetElementAt(rep->liste, i)->pers.nom, (_countof(tmp_nom2)-1)); 
		if (strcmp(tmp_nom, tmp_nom2) == 0)
			trouve = true;
		else
			i++;
	}
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	int i;
	int j = 0;
	int code_ascii;
	char chaine_compact[MAX_TEL];
	for (i = 0 ; i < MAX_TEL ; i++){ 		// pour chaque caractères de notre liste
		code_ascii = s[i]; 					// on passe le caractère en code ASCII
		if (48 <= code_ascii && code_ascii <= 57){ 		// si ce caractère est un chiffre
			chaine_compact[j] = s[i]; 		// alors on l'insère dans la liste s
			j++;
		}
	}
	strcpy(s, chaine_compact); 		
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	int err = 0;
#ifdef IMPL_TAB
	char buffer[sizeof(Enregistrement) +2]; 
	fic_rep = fopen(nom_fichier, "w");
	if ((err == 0) && (fic_rep != NULL)) {
		for(int i = 0 ; i < rep->nb_elts ; i++){
			sprintf(buffer, "%s;%s;%s\n", ((rep->tab) + i)->nom, ((rep->tab) + i)->prenom, ((rep->tab) + i)->tel);
			fputs(buffer,fic_rep);
		}
	}
	else {
		printf("L'ouverture du fichier a échoué");
		return(ERROR);
	}
#else
#ifdef IMPL_LIST
	fic_rep = fopen(nom_fichier, "w"); 	// on utlise la même méthode que pour les tableaux 
    if (err == 0 && fic_rep != NULL) {
   	 char buffer[MAX_NOM + MAX_NOM + MAX_TEL + 2];	// sauf pour définir la taille du buffer
  	  for (int i = 0; i < rep->nb_elts; i++) {
   	     sprintf(buffer, "%s%c%s%c%s\n", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.tel);
		 // et pour récupérer les noms, prénoms et numéros de téléphone des contatcs qui est fait grâce à la fonction GetElementAt
   	     fputs(buffer, fic_rep);
			}
		}
	else {
		printf("L'ouverture du fichier a échoué");
		return(ERROR);
	}
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					
	int num_rec = 0;						 
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;

	fic_rep = fopen(nom_fichier,"r");
	if (fic_rep == NULL)  // si le fichier est vide on renvoie 0
	{
		return(0);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))  // tout le temps qu'on ne se trouve pas à la fin du fichier et que le nombre de contacts est inférieur au nombre max
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				// mémorisation de l'enregistrement lu dans le tableau 
				buffer[long_max_rec] = 0;			// en principe il y a deja un fin_de_chaine, cf fgets 

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			// suppression du fin_de_ligne eventuel 

				idx = 0;								// analyse depuis le debut de la ligne 
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							// on saute le separateur 
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		// élément à priori correct, on le comptabilise 
					}
				}
#else
#ifdef IMPL_LIST
				Enregistrement tmp; // on crée une variable temporaire de type enregistrement
				if (lire_champ_suivant(buffer, &idx, tmp.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							// on saute le séparateur
					if (lire_champ_suivant(buffer, &idx, tmp.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, tmp.tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		// élément à priori correct, on le comptabilise
					}
				}
				InsertElementAt(rep->liste, rep->liste->size, tmp);	// une fois qu'on a fini de charger l'element, on l'ajoute à la liste chaînée
#endif
#endif
			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} // fin charger 


