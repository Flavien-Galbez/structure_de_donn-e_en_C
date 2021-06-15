#ifndef MENU_ARBRE_H
#define MENU_ARBRE_H

#include <arbre_des_trajets_6.h>

//Initialise les données des fichier et demande à l'utilisateur s'il veut voir l'ensemble des villes 
Ville* intitialiser_donnees(int* nb_de_villes);

//Permet de demander à l'utilisateur de saisir une ville et de la convertir en index
int saisir_ville (Ville* villes, int nb_de_villes);

//Demandes à l'utilisateur la ville de départ et d'arrivée puis crée l'arbre correspondant 
Noeud* saisie_arbre (Ville* tableau_villes,int nb_de_villes);

//Permet de demander à l'utilisateur s'il veut continuer et s'il veut changer la ville de départ et d'arrivée
void choix_suivant (int* choix,Ville* tableau_villes, int nb_de_villes, Noeud** racine);

//Affiche le menu et appelle la fonction correspondante selon la demande de l'utilisateur
void menu(Ville* tableau_villes, int nb_de_villes, Noeud* racine);

//Permet d'afficher le premier trajet trouvé en recursif
void afficher_un_trajet_rec (Ville* tableau_ville, int nb_ville_totale,int position_prefixe, char* prefixe,int duree, int distance, Noeud* noeud_v,bool* trouve);

//Permet d'afficher le premier trajet trouvé en appelant afficher_un_trajet_rec avec les bons paramètres
void afficher_un_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v);

//Permet d'afficher tous les trajets trouvés en recursif
void afficher_tout_trajet_rec (Ville* tableau_ville, int nb_ville_totale,int position_prefixe, char* prefixe,int duree, int distance, Noeud* noeud_v);

//Permet d'afficher tous les trajets trouvés en appelant afficher_un_trajet_rec avec les bons paramètres
void afficher_tout_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v);

//Permet de trouver la valeur (distance ou durée) la plus faible possible en recursif
void trouver_plus_efficace_trajet_rec (Ville* tableau_ville,bool test_distance, int nb_ville_totale, int duree, int distance, int* valeur_record, Noeud* noeud_v);

//Permet d'afficher le trajet trouvé le plus court (ou le plus rapide) (ou les trajets trouvés les plus courts (ou les plus rapide) en cas d'égalité) en recursif
void afficher_plus_efficace_trajet_rec (Ville* tableau_ville,bool test_distance, int nb_ville_totale,int position_prefixe, char* prefixe, int duree, int distance, int valeur_record, Noeud* noeud_v);

//Permet d'afficher le trajet trouvé le plus court (ou les trajets trouvés les plus courts en cas d'égalité) en appelant trouver_plus_efficace_rec et afficher_plus_efficace_trajet_rec avec les bons paramètres
void afficher_plus_court_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v);

//Permet d'afficher le trajet trouvé le plus rapide (ou les trajets trouvés les plus rapides en cas d'égalité) en appelant trouver_plus_efficace_rec et afficher_plus_efficace_trajet_rec avec les bons paramètres
void afficher_plus_rapide_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v);

//Permet d'afficher l'arbre des trajets en recursif
void afficher_arbre_rec (Ville* tableau_ville, int nb_ville_totale,int hauteur,int duree, int distance, Noeud* noeud_v);

//Permet d'afficher l'arbre des trajets en appelant afficher_arbre_rec avec les bons paramètres
void afficher_arbre (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v);

#endif