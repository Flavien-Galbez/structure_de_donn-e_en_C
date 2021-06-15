#include "arbre_des_trajets_6.h"
#include <stdio.h>
#include <stdlib.h>

int nb_villes(char* nom_fichier)
{
	//"villes.csv"
	//permet de compter le nombre de ville présente dans le fichier
	FILE * fichier = fopen (nom_fichier,"r");
	int resultat=0;
	if( fichier != NULL )
	{
		char c = fgetc (fichier);
		while ( c != EOF ) //tant qu'on n'a pas atteind la fin du fichier
		{
			if (c==10)
			{
				resultat++;
			}
			c = fgetc (fichier);
		}
		fclose(fichier);
	}
	else
	{
		//Le fichier n'a pas été trouver
		printf (" Probleme lors de l'ouverture du fichier %s\n", nom_fichier );
	}
	return (resultat);
}

Ville* creation_liste_ville(char* nom_fichier, int nb_de_villes)
{
//"villes.csv"
// permet d'extraire les données des villes du fichier donnée en paramètres
	Ville* villes = (Ville*)malloc(nb_de_villes*sizeof(Ville));
	if (villes==NULL)
	{
		return NULL;
	}
	FILE * fichier = fopen (nom_fichier,"r"); //ouvre le premier fichier en mode lecture
	if( fichier != NULL )
	{
		char c = fgetc (fichier);
		while ( c != EOF && c!=10 ) //On retire la première ligne
		{
			c = fgetc ( fichier );
		}
		int index_ville_courante;
		int j=0;
		if ( c != EOF ) //tant qu'on n'a pas atteind la fin du fichier
		{
			for(index_ville_courante=0;index_ville_courante<nb_de_villes;index_ville_courante++)
			{
				c = fgetc (fichier);
				villes[index_ville_courante].nom_ville = (char*)malloc((LONGUEUR_VILLE_MAX+1)*sizeof(char)); // On rajoute +1 pour le caractère '/0'
				if (villes[index_ville_courante].nom_ville!=NULL)
				{
					for(j=0;c!=10&&c!=EOF;j++)
					{
						(villes[index_ville_courante].nom_ville)[j]=c;
						c = fgetc ( fichier );
					}
					(villes[index_ville_courante].nom_ville)[j]='\0';
					villes[index_ville_courante].nb_destinations=0;
					villes[index_ville_courante].destinations=NULL;
				}
				else
				{
					return NULL;
				}
			}
		}
		fclose ( fichier );
	}
	else
	{
		//Le fichier n'a pas été trouver
		printf (" Probleme lors de l'ouverture du fichier %s\n", nom_fichier );
	}
	return villes;
}

int creation_liste_trajet(char* nom_fichier,Ville* villes, int nb_de_villes)
{
	//"connexion.csv"
	//Permet d'extraire les données de connexions du fichier entée en paramètre et de le placer dans les placer dans le tableau de ville
	FILE * fichier = fopen (nom_fichier,"r"); //ouvre le premier fichier en mode lecture
	if( fichier != NULL )
	{
		char nom_depart[LONGUEUR_VILLE_MAX+1]={'\0'};    // max 45 + \0 (le nom de ville le plus long en France possède 45 carractères)
		char nom_arrivee[LONGUEUR_VILLE_MAX+1]={'\0'};    // max 45 + \0
		int distance;    
		int heure;
		int minute; 
		int succes; //permet de tester si ajouter_destination a échoué
		char c ;
		fscanf(fichier,"ville1,ville2,distance,duree");
		while((c = fgetc(fichier))!=EOF)
		{
			fscanf(fichier,"%45[^,],%45[^,],%d,%d:%d",nom_depart,nom_arrivee,&distance,&heure,&minute); //lit l'intégralité d'une ligne
			succes = ajouter_destination(villes,nb_de_villes,nom_depart,nom_arrivee,60*heure+minute,distance); // on rajoute les connexions à la liste des villes
			if (succes<0)
			{
				fclose(fichier);
				return succes;
			}
			for(int i = 0; i < LONGUEUR_VILLE_MAX+1; i++)
			{
				nom_depart[i] = '\0';
				nom_arrivee[i] = '\0';
			}
		}
		fclose(fichier);
		return 0;
	}
	else
	{
		return -1;
	}
}

int convertir_nom_ville_en_index (Ville* villes, int nb_de_villes, char* nom_ville)
{
	//convertit le nom d'une ville à l'index correspondant dans le tableau de ville 
	int index_ville_resultat = -1;
	for (int index_ville=0;index_ville<nb_de_villes && index_ville_resultat==-1;index_ville++)
	{
		bool meme_ville = true;
		int i=0;
		do
		{
			if ((villes[index_ville]).nom_ville[i]!=nom_ville[i])
			{
				meme_ville = false;
			}
			i++;
		}
		while ((villes[index_ville]).nom_ville[i]!='\0'&&nom_ville[i]!='\0' && meme_ville==true);
		if (meme_ville==true)
		{
			index_ville_resultat = index_ville;
		}
	}
	return index_ville_resultat;
}

int ajouter_destination (Ville* villes, int nb_de_villes,char* nom_depart, char* nom_destination, int duree, int distance)
{
	//permet d'ajouter une destination à la liste chaîné du tableau de ville
	int index_depart = convertir_nom_ville_en_index(villes, nb_de_villes, nom_depart);
	int index_destination = convertir_nom_ville_en_index(villes, nb_de_villes, nom_destination);
	if(index_depart==-1||index_destination==-1)
	{
		return -1; //erreur dans la lecteur des noms
	}
	Destinations* nouvelle_destination = creation_maillon (index_destination,duree, distance);
	if (nouvelle_destination==NULL)
	{
		return -2; //erreur dans l'allocation mémoire'de la variable nouvelle_destination
	}
	villes[index_depart].nb_destinations++;
	ajouter_maillon(&(villes[index_depart].destinations),nouvelle_destination);
	return 0; //La fonction a bien marché
}

Destinations * creation_maillon (int index_ville, int duree, int distance)
{
	// Crée le maillon correspondant à la ville de destination la duree et la distance
	Destinations* dest = (Destinations*)malloc(sizeof(Destinations));
	if (dest != NULL)
	{
		dest->duree=duree;
		dest->distance = distance;
		dest->index_ville=index_ville;
		dest->suivant=NULL;
	}
	return dest;
}


void ajouter_maillon (Destinations** liste, Destinations* maillon_ajout)
{
	//permet de placer un maillon en tête de la liste chaînée
	if (*liste==NULL)
	{
		*liste = maillon_ajout;
	}
	else
	{
		maillon_ajout->suivant = *liste;
		*liste = maillon_ajout;
	}
}

Noeud* creer_noeud (int index_ville,Ville* tableau_ville,int* ville_visite, int nb_ville_visite)
{
	//permet de crée un noeud
	Noeud* noeud_v = (Noeud*)malloc(sizeof(Noeud));
	if (noeud_v !=NULL)
	{
		noeud_v->index_ville=index_ville;
		noeud_v->nb_fils=tableau_ville[index_ville].nb_destinations; // On prends le nombre de destinations total
		for (int i=0;i<nb_ville_visite;i++)							// au quel on retire le nombre des fils déjà visité afin d'obtenir le nombre de fils
		{
			for (Destinations* dest = tableau_ville[index_ville].destinations; dest!=NULL; dest=dest->suivant)
			{
				if (ville_visite[i] == dest->index_ville)
				{
					noeud_v->nb_fils -- ;
				}
			}
		}
		noeud_v->valide=false; //le noeud n'appartient pas sur un chemin valide de base
		if (noeud_v->nb_fils>0)
		{
			noeud_v->liste_fils=(Noeud**)malloc(noeud_v->nb_fils*sizeof(Noeud*));
			if (noeud_v->liste_fils!=NULL)
			{
				for(int i=0; i<noeud_v->nb_fils;i++)
				{
					noeud_v->liste_fils[i]=NULL;
				}
			}
			else //En cas d'échec de malloc
			{
				free(noeud_v);
				noeud_v = NULL;
			}
		}
		else
		{
			noeud_v->liste_fils=NULL;
		}
	}
	return noeud_v;
}

Noeud* creation_arbre_rec (int index_depart, int index_arrivee, bool* validite, Ville* tableau_ville, int* ville_visite, int nb_ville_visite, int hauteur_noeud,bool* erreur)
{
	//Permet de créer l'arbre en récursif
	if (hauteur_noeud>=PROFONDEUR_MAX +1) //On atteind la profondeur max
	{
		Noeud *new_feuille = malloc(sizeof(Noeud));
		if(new_feuille == NULL)
		{
			*erreur = true; //permet de savoir s'il y a eu un problème dans la création de l'arbre
			return NULL;
		}
		
		new_feuille->index_ville = index_depart;
		new_feuille->nb_fils = 0;
		new_feuille->liste_fils = NULL;
		new_feuille->valide = false;
		
		return new_feuille;
	}
	if (index_depart==index_arrivee) //on atteind l'arrivee
	{
		Noeud *new_feuille = malloc(sizeof(Noeud));
		if(new_feuille == NULL)
		{
			*erreur = true;//permet de savoir s'il y a eu un problème dans la création de l'arbre
			return NULL;
		}
		new_feuille->index_ville = index_depart;
		new_feuille->nb_fils = 0;
		new_feuille->liste_fils = NULL;
		new_feuille->valide = true;

		if (validite!=NULL)
		{
			*validite = true; //permet de savoir si le chemin a bien finit à la bonne destination
		}
		return new_feuille;
	}
	Noeud* new_noeud = creer_noeud(index_depart,tableau_ville,ville_visite,nb_ville_visite);
	if (new_noeud==NULL) // en cas de pb de creation du noeud
	{
		*erreur=true;
		return NULL; 
	}

	ville_visite[nb_ville_visite]=index_depart;
	nb_ville_visite++;
	int index_fils = 0;
	for (Destinations* dest=tableau_ville[index_depart].destinations ; dest != NULL ; dest = dest->suivant) //on parcours chacune des destinations suivante (qui est enregistrée sous forme de liste chaînée)
	{
		bool est_present =false;
		for (int i =0; i<nb_ville_visite; i++) //on test si la ville de la destination a déjà été visité
		{
			if (dest->index_ville==ville_visite[i])
			{
				est_present=true;
			}
		}
		if (!est_present) //si elle n'a pas été visité alors on crée un nouveau fils pour elle
		{
			Noeud* fils = creation_arbre_rec (dest->index_ville,index_arrivee, &(new_noeud->valide),tableau_ville,ville_visite,nb_ville_visite,hauteur_noeud+1,erreur);
			if (*erreur==true)
			{
				return NULL;
			}

			//On propage la validité jusqu'au père grâce à l'appel recursif
			if (new_noeud->valide && validite!=NULL)
			{
				*validite = true;
			}
			
			//On attribue ce fils crée au tableau des fils du noeud courant
			if(index_fils<new_noeud->nb_fils)
			{
				new_noeud->liste_fils[index_fils]=fils;
				index_fils++;
			}
		}
	}
	return new_noeud;
}

Noeud* creation_arbre (int index_depart, int index_arrivee, Ville* tableau_ville, int nb_ville_totale)
{
	//Permet de créer l'arbre en appelant creation_arbre_rec avec les bons parametres
	int* ville_visite = (int*)malloc(nb_ville_totale*sizeof(int));
	bool erreur =false; //permet de savoir s'il y a eu une erreur dans la création
	if (ville_visite==NULL)
	{
		return NULL;
	}
	Noeud* new_noeud = creation_arbre_rec (index_depart,index_arrivee, NULL,tableau_ville,ville_visite,0,0,&erreur);
	if (erreur==true)
	{
		liberation_noeud(new_noeud);
		new_noeud=NULL;
	}
	return new_noeud;
}

void liberation_destinations (Destinations * dest)
{
	//permet de libérer la liste chaîné des destinations
	if (dest!= NULL)
	{
		liberation_destinations(dest->suivant);
		free(dest);
	}
}

void liberation_ville (Ville * villes,int nb_de_ville)
{
	//permet de libérer l'espace mémoire d'un tableau de ville
	for(int i=0;i<nb_de_ville;i++)
	{
		liberation_destinations(villes[i].destinations);
		free(villes[i].nom_ville);
	}
	free(villes);
}

void liberation_noeud (Noeud* noeud_v)
{
	//permet de libérer l'espace mémoire d'un arbre
	if (noeud_v!=NULL)
	{
		for (int i=0; i<noeud_v->nb_fils;i++)
		{
			liberation_noeud(noeud_v->liste_fils[i]);
		}
		free(noeud_v->liste_fils);
		free(noeud_v);
	}
}