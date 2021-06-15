#include <stdio.h>
#include "menu_arbre.h"

int main(int argc, char **argv)
{
	int nb_de_villes;
	Ville* tableau_villes = intitialiser_donnees(&nb_de_villes);
	Noeud* racine = saisie_arbre(tableau_villes,nb_de_villes);
	menu(tableau_villes,nb_de_villes,racine);
	return 0;
}