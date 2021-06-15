
#ifndef ARBRE_DES_TRAJETS_6_H
#define ARBRE_DES_TRAJETS_6_H

#include <stdbool.h>

#define PROFONDEUR_MAX 8
#define LONGUEUR_VILLE_MAX 45

struct _Destinations
{
	int index_ville;
	int duree;
	int distance;
	struct _Destinations* suivant;
};

typedef struct _Destinations Destinations;

typedef struct
{
	char* nom_ville;
	int nb_destinations;
	Destinations * destinations;
} Ville;


struct _Noeud
{
	int index_ville;
	int nb_fils;
	bool valide;
	struct _Noeud** liste_fils;
};

typedef struct _Noeud Noeud;


// Permet d'extraire les données des villes du fichier donnée en paramètres
int creation_liste_trajet(char* nom_fichier,Ville* villes, int nb_de_villes);

//Permet d'extraire les données de connexions du fichier entée en paramètre et de le placer dans les placer dans le tableau de ville
Ville* creation_liste_ville(char* nom_fichier, int nb_de_villes);

//Permet de compter le nombre de ville présente dans le fichier
int nb_villes(char* nom_fichier);

//Convertit le nom d'une ville à l'index correspondant dans le tableau de ville
int convertir_nom_ville_en_index (Ville* villes, int nb_de_villes, char* nom_ville);

//Permet d'ajouter une destination à la liste chaîné du tableau de ville
int ajouter_destination (Ville* villes, int nb_de_villes,char* nom_depart, char* nom_destination, int duree, int distance);

// Crée le maillon correspondant à la ville de destination la duree et la distance
Destinations * creation_maillon (int index_ville, int duree, int distance);

//Permet de placer un maillon en tête de la liste chaînée
void ajouter_maillon (Destinations** liste, Destinations* maillon_ajout);

//Permet de crée un noeud
Noeud* creer_noeud (int index_ville,Ville* tableau_ville,int* ville_visite, int nb_ville_visite);

//Permet de créer l'arbre en récursif
Noeud* creation_arbre_rec (int index_depart, int index_arrivee, bool* validite, Ville* tableau_ville, int* ville_visite, int nb_ville_visite, int hauteur_noeud,bool* erreur);

//Permet de créer l'arbre en appelant creation_arbre_rec avec les bons parametres
Noeud* creation_arbre (int index_depart, int index_arrivee, Ville* tableau_ville, int nb_ville_totale);

//permet de libérer l'espace mémoire de la liste chaîné des destinations
void liberation_destinations (Destinations * dest);

//permet de libérer l'espace mémoire d'un tableau de ville
void liberation_ville (Ville * villes,int nb_de_ville);

//permet de libérer l'espace mémoire d'un arbre
void liberation_noeud (Noeud* noeud_v);

#endif