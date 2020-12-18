#pragma once
#define MAX_NOM 30     /* longueur maximale d'un nom */
#define MAX_TEL 20      /* longueur maximale d'un num�ro de t�l. */

/* Enregistrement : structure d'un contact dans le tableau de contacts */
/* le type enregistrement contient 3 champs :                          */
/*  - nom, prenom et tel qui sont tous les trois des cha�nes de        */
/*  caract�res (tableaux de char)                                      */
typedef struct enreg
{
	char nom[MAX_NOM];
	char prenom[MAX_NOM];
	char tel[MAX_TEL];
} Enregistrement;

