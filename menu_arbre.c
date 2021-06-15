#include "menu_arbre.h"
#include <stdio.h>
#include <stdlib.h>

Ville* intitialiser_donnees(int* nb_de_villes)
{
	//Initialise les données des fichier et demande à l'utilisateur s'il veut voir l'ensemble des villes 
	*nb_de_villes=nb_villes("villes.csv");
	Ville* tableau_villes = creation_liste_ville("villes.csv",*nb_de_villes);
	creation_liste_trajet("connexions.csv",tableau_villes,*nb_de_villes);
	int voir_ville;
	do
	{
		printf("Voulez-vous voir l'ensemble des villes disponibles (saisir 0 ou 1)?\n");
		printf("1- OUI\n");
		printf("0- NON\n");
		scanf("%d",&voir_ville);
		printf("\n");
	}while(voir_ville!=0&&voir_ville!=1);
	if(voir_ville==1)
	{
		printf("Les villes enregistrees sont les suivantes : \n");
		for (int index_ville=0;index_ville<*nb_de_villes; index_ville++)
		{
			printf("%s\n",tableau_villes[index_ville].nom_ville);
		}
		printf("\n");
	}
	return tableau_villes;
}

int saisir_ville (Ville* villes, int nb_de_villes)
{
	//Permet de demander à l'utilisateur de saisir une ville et de la convertir en index
	int index_ville;
	char* ville_saisie = (char*)malloc((LONGUEUR_VILLE_MAX+1)*sizeof(char*));
	if (ville_saisie!=NULL)
	{
		do
		{
			scanf("%s",ville_saisie);
			index_ville=convertir_nom_ville_en_index(villes,nb_de_villes,ville_saisie);
		}while(index_ville<0); //permet de tester si la ville est dans la liste des villes proposée
		printf("\n");
	}
	free(ville_saisie); //on libère l'espace mémoire de la ville saisie
	return index_ville;
}

Noeud* saisie_arbre (Ville* tableau_villes,int nb_de_villes)
{
	//Demandes à l'utilisateur la ville de départ et d'arrivée puis crée l'arbre correspondant 
	printf("Veuillez saisir la ville de depart (parmi les villes disponibles):\n");
	int index_depart = saisir_ville (tableau_villes,nb_de_villes); //fait appel à la fonction saisir ville qui propose une saisie sécurisée de la ville et la convertit en index
	printf("Veuillez saisir la ville d'arrivee (parmi les villes disponibles):\n");
	int index_arrivee;
	do
	{
		index_arrivee = saisir_ville (tableau_villes,nb_de_villes); //fait appel à la fonction saisir ville qui propose une saisie sécurisée de la ville et a convertit en index
	} while (index_arrivee==index_depart); // on vérifie que la ville d'arrivée n'est pas la même que celle de départ
	Noeud* racine = creation_arbre(index_depart,index_arrivee,tableau_villes,nb_de_villes);
	return racine;
}

void choix_suivant (int* choix,Ville* tableau_villes, int nb_de_villes, Noeud** racine)
{
	//Permet de demander à l'utilisateur s'il veut continuer et s'il veut changer la ville de départ et d'arrivée
	printf("============================================================================\n");
	printf("\n");
	int saisie;
	do
	{
		printf("Voulez-vous continuer ? (0 ou 1):\n");
		printf(" 1 - OUI \n");
		printf(" 0 - NON \n");
		scanf("%d",&saisie);
		printf("\n");
	}
	while(saisie!=0 && saisie!=1);
	if (saisie==0)
	{
		*choix=6; // Permet de sortir du while de la fonction menu directement sans reafficher le menu
	}
	else
	{
		do
		{
			printf("Voulez-vous changer la ville de depart et la ville d'arrivee ? (0 ou 1):\n");
			printf(" 1 - OUI \n");
			printf(" 0 - NON \n");
			scanf("%d",&saisie);
			printf("\n");
		}
		while(saisie!=0 && saisie!=1);
		if(saisie==1)
		{
			liberation_noeud(*racine); //On prend soin de libérer l'ancien arbre avant d'en créer un nouveau
			*racine = saisie_arbre(tableau_villes,nb_de_villes);
		}
	}
}

void menu(Ville* tableau_villes, int nb_de_villes, Noeud* racine)
{
	//Affiche le menu et appelle la fonction correspondante selon la demande de l'utilisateur
	int choix;
	do
	{
		printf("Veuillez choisir l'affichage souhaite (1 to 6):\n");
		printf(" 1 - afficher un trajet \n");
		printf(" 2 - afficher tous les trajets \n");
		printf(" 3 - afficher le trajet le plus court \n");
		printf(" 4 - afficher le trajet le plus rapide \n");
		printf(" 5 - afficher l'arbre des trajets \n");
		printf(" 6 - quitter \n");
		scanf("%d",&choix);
		printf("\n");
		if (choix==1)
		{
			printf("Le trajet trouve est :\n");
			afficher_un_trajet(tableau_villes,nb_de_villes,racine);
			printf("\n");
			choix_suivant (&choix, tableau_villes, nb_de_villes,&racine);
		}
		if (choix==2)
		{
			printf("Les trajets trouves sont :\n");
			afficher_tout_trajet(tableau_villes,nb_de_villes,racine);
			printf("\n");
			choix_suivant (&choix, tableau_villes, nb_de_villes, &racine);
		}
		if (choix==3)
		{
			printf("Le trajet le plus court est :\n");
			afficher_plus_court_trajet(tableau_villes,nb_de_villes,racine);
			printf("\n");
			choix_suivant (&choix, tableau_villes, nb_de_villes, &racine);
		}
		if (choix==4)
		{
			printf("Le trajet le plus rapide est :\n");
			afficher_plus_rapide_trajet(tableau_villes,nb_de_villes,racine);
			printf("\n");
			choix_suivant (&choix, tableau_villes, nb_de_villes, &racine);
		}
		if (choix==5)
		{
			printf("L'arbre des trajets est :\n");
			afficher_arbre(tableau_villes,nb_de_villes,racine);
			printf("\n");
			choix_suivant (&choix, tableau_villes, nb_de_villes, &racine);
		}
	}
	while (choix!=6);
	liberation_noeud(racine); //on libère l'arbre avant de quitter
	liberation_ville(tableau_villes,nb_de_villes); // on libère les données du fichier aussi
}

void afficher_un_trajet_rec (Ville* tableau_ville, int nb_ville_totale,int position_prefixe, char* prefixe,int duree, int distance, Noeud* noeud_v,bool* trouve)
{
	//Permet d'afficher le premier trajet trouvé en recursif
	if(noeud_v!=NULL)
	{
		if (noeud_v->valide==true&&*trouve!=true) // on ignore les noeuds qui n'aboutissent pas à la destination et on s'arrete dès qu'un tel trajet a été trouvé
		{
			int position_nom_ville=0;
			while(((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville]!='\0') // on inscrit en fin du préfixe la ville du noeud
			{
				prefixe[position_prefixe + position_nom_ville] = ((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville];
				position_nom_ville++;
			}
			prefixe[position_prefixe + position_nom_ville++]=' '; // on écrit ensuite une flèche en fin du préfixe
			prefixe[position_prefixe + position_nom_ville++]='-';
			prefixe[position_prefixe + position_nom_ville++]='>';
			prefixe[position_prefixe + position_nom_ville++]=' ';
			prefixe[position_prefixe + position_nom_ville]='\0';
			position_prefixe+=position_nom_ville;
			if (noeud_v->nb_fils==0)
			{
				*trouve=true; //permet d'arréter la recherche dès qu'on a un trajet
				printf("%s%dh %dmin / %dkm\n",prefixe,duree/60,duree%60,distance);
			}
			else
			{
				for (int index_fils=0; index_fils<noeud_v->nb_fils;index_fils++) //On rappelle la fonction pour chacun des fils du noeud
				{
					for (Destinations* dest=tableau_ville[noeud_v->index_ville].destinations; dest!=NULL; dest = dest ->suivant) //On retrouve la destination correspondantes dans la liste chaînée des destinations pour avoir la durée et la distance du trajet
					{
						if (((noeud_v->liste_fils)[index_fils])->index_ville == dest->index_ville)
						{
							afficher_un_trajet_rec(tableau_ville,nb_ville_totale,position_prefixe,prefixe,duree+(dest->duree),distance+(dest->distance),noeud_v->liste_fils[index_fils],trouve);
						}
					}
				}
			}
		}
	}
	else
	{
		printf("\n");
	}
}

void afficher_un_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v)
{
	//Permet d'afficher le premier trajet trouvé en appelant afficher_un_trajet_rec avec les bons paramètres 
	char* prefixe = (char*)malloc((PROFONDEUR_MAX*(LONGUEUR_VILLE_MAX+5)+1)*sizeof(char));
	bool trouve =false;
	if (prefixe!=NULL)
	{
		afficher_un_trajet_rec(tableau_ville,nb_ville_totale,0,prefixe,0,0,noeud_v, &trouve);
		free(prefixe); // on libère le préfixe
	}
}

void afficher_tout_trajet_rec (Ville* tableau_ville, int nb_ville_totale,int position_prefixe, char* prefixe,int duree, int distance, Noeud* noeud_v)
{
	//Permet d'afficher tous les trajets trouvés en recursif
	if(noeud_v!=NULL)
	{
		if (noeud_v->valide==true) // on ignore les noeuds qui n'aboutissent pas à la destination
		{
			int position_nom_ville=0;
			while(((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville]!='\0') // on inscrit en fin du préfixe la ville du noeud
			{
				prefixe[position_prefixe + position_nom_ville] = ((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville];
				position_nom_ville++;
			}
			prefixe[position_prefixe + position_nom_ville++]=' ';  // on écrit ensuite une flèche en fin du préfixe
			prefixe[position_prefixe + position_nom_ville++]='-';
			prefixe[position_prefixe + position_nom_ville++]='>';
			prefixe[position_prefixe + position_nom_ville++]=' ';
			prefixe[position_prefixe + position_nom_ville]='\0';
			position_prefixe+=position_nom_ville;
			if (noeud_v->nb_fils==0)
			{
				printf("%s%dh %dmin / %dkm\n",prefixe,duree/60,duree%60,distance);
			}
			else
			{
				for (int index_fils=0; index_fils<noeud_v->nb_fils;index_fils++) //On rappelle la fonction pour chacun des fils du noeud
				{
					for (Destinations* d=tableau_ville[noeud_v->index_ville].destinations; d!=NULL; d = d ->suivant) //On retrouve la destination correspondantes dans la liste chaînée des destinations pour avoir la durée et la distance du trajet
					{
						if (((noeud_v->liste_fils)[index_fils])->index_ville == d->index_ville)
						{
							afficher_tout_trajet_rec(tableau_ville,nb_ville_totale,position_prefixe,prefixe,duree+(d->duree),distance+(d->distance),noeud_v->liste_fils[index_fils]);
						}
					}
				}
			}
		}
	}
	else
	{
		printf("\n");
	}
}

void afficher_tout_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v)
{
	//Permet d'afficher tous les trajets trouvés en appelant afficher_un_trajet_rec avec les bons paramètres 
	char* prefixe = (char*)malloc((PROFONDEUR_MAX*(LONGUEUR_VILLE_MAX+5)+1)*sizeof(char));
	if (prefixe!=NULL)
	{
		afficher_tout_trajet_rec(tableau_ville,nb_ville_totale,0,prefixe,0,0,noeud_v);
		free(prefixe); // on libère le préfixe
	}
}

void trouver_plus_efficace_trajet_rec (Ville* tableau_ville,bool test_distance, int nb_ville_totale, int duree, int distance, int* valeur_record, Noeud* noeud_v)
{
	//Permet de trouver la valeur (distance ou durée) la plus faible possible en recursif
	if(noeud_v!=NULL)
	{
		if (noeud_v->valide==true) // on ignore les noeuds qui n'aboutissent pas à la destination
		{
			if (noeud_v->nb_fils==0)
			{
				if((*valeur_record>distance||*valeur_record==-1)&&test_distance==true) //car la valeur record est initialisée à -1
				{
					*valeur_record=distance;
				}
				if((*valeur_record>duree||*valeur_record==-1)&&test_distance==false) //car la valeur record est initialisée à -1
				{
					*valeur_record=duree;;
				}
			}
			else
			{
				for (int index_fils=0; index_fils<noeud_v->nb_fils;index_fils++) //On rappelle la fonction pour chacun des fils du noeud
				{
					for (Destinations* dest =tableau_ville[noeud_v->index_ville].destinations; dest!=NULL; dest = dest ->suivant) //On retrouve la destination correspondantes dans la liste chaînée des destinations pour avoir la durée et la distance du trajet
					{
						if (((noeud_v->liste_fils)[index_fils])->index_ville == dest->index_ville)
						{
							trouver_plus_efficace_trajet_rec(tableau_ville,test_distance,nb_ville_totale,duree+(dest->duree),distance+(dest->distance),valeur_record,noeud_v->liste_fils[index_fils]);
						}
					}
				}
			}
		}
	}
}

void afficher_plus_efficace_trajet_rec (Ville* tableau_ville,bool test_distance, int nb_ville_totale,int position_prefixe, char* prefixe, int duree, int distance, int valeur_record, Noeud* noeud_v)
{
	//Permet d'afficher le trajet trouvé le plus court (ou le plus rapide) (ou les trajets trouvés les plus courts (ou les plus rapide) en cas d'égalité) en recursif
	if(noeud_v!=NULL)
	{
		if (noeud_v->valide==true) // on ignore les noeuds qui n'aboutissent pas à la destination
		{
			int position_nom_ville=0;
			while(((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville]!='\0') // on inscrit en fin du préfixe la ville du noeud
			{
				prefixe[position_prefixe + position_nom_ville] = ((tableau_ville[noeud_v->index_ville]).nom_ville)[position_nom_ville];
				position_nom_ville++;
			}
			prefixe[position_prefixe + position_nom_ville++]=' '; // on écrit ensuite une flèche en fin du préfixe
			prefixe[position_prefixe + position_nom_ville++]='-';
			prefixe[position_prefixe + position_nom_ville++]='>';
			prefixe[position_prefixe + position_nom_ville++]=' ';
			prefixe[position_prefixe + position_nom_ville]='\0';
			position_prefixe+=position_nom_ville;
			if (noeud_v->nb_fils==0)
			{
				if((valeur_record==distance && test_distance==true)||(valeur_record==duree && test_distance==false))
				{
					printf("%s%dh %dmin / %dkm\n",prefixe,duree/60,duree%60,distance);
				}
			}
			else
			{
				for (int index_fils=0; index_fils<noeud_v->nb_fils;index_fils++) //On rappelle la fonction pour chacun des fils du noeud
				{
					for (Destinations* dest=tableau_ville[noeud_v->index_ville].destinations; dest!=NULL; dest = dest ->suivant) //On retrouve la destination correspondantes dans la liste chaînée des destinations pour avoir la durée et la distance du trajet
					{
						if (((noeud_v->liste_fils)[index_fils])->index_ville == dest->index_ville)
						{
							afficher_plus_efficace_trajet_rec(tableau_ville,test_distance,nb_ville_totale,position_prefixe,prefixe,duree+(dest->duree),distance+(dest->distance), valeur_record, noeud_v->liste_fils[index_fils]);
						}
					}
				}
			}
		}
	}
}

void afficher_plus_court_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v)
{
	//Permet d'afficher le trajet trouvé le plus court (ou les trajets trouvés les plus courts en cas d'égalité) en appelant trouver_plus_efficace_rec et afficher_plus_efficace_trajet_rec avec les bons palle_totale,0,0,&distance_record,noeud_v); //on trouve la plus petite distance en mettant true
	char* prefixe = (char*)malloc((PROFONDEUR_MAX*(LONGUEUR_VILLE_MAX+5)+1)*sizeof(char));
	int distance_record = -1;
	if (prefixe!=NULL)
	{
		trouver_plus_efficace_trajet_rec(tableau_ville,true,nb_ville_totale,0,0,&distance_record,noeud_v); //on trouve la plus petite distance en mettant true
		afficher_plus_efficace_trajet_rec(tableau_ville,true,nb_ville_totale,0,prefixe,0,0, distance_record, noeud_v); //on affiche tout les chemin correspondant à cette distance
		free(prefixe);
	}
}

void afficher_plus_rapide_trajet (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v)
{
	//Permet d'afficher le trajet trouvé le plus rapide (ou les trajets trouvés les plus rapides en cas d'égalité) en appelant trouver_plus_efficace_rec et afficher_plus_efficace_trajet_rec avec les bons paramètres 
	char* prefixe = (char*)malloc((PROFONDEUR_MAX*(LONGUEUR_VILLE_MAX+5)+1)*sizeof(char));
	int duree_record = -1;
	if (prefixe!=NULL)
	{
		trouver_plus_efficace_trajet_rec(tableau_ville,false,nb_ville_totale,0,0,&duree_record,noeud_v); //on trouve la plus petite durée en mettant false
		afficher_plus_efficace_trajet_rec(tableau_ville,false,nb_ville_totale,0,prefixe,0,0,duree_record,noeud_v); //on affiche tout les chemin correspondant à cette durée
		free(prefixe); // on libère le préfixe
	}
}


void afficher_arbre_rec (Ville* tableau_ville, int nb_ville_totale,int hauteur,int duree, int distance, Noeud* noeud_v)
{
	//Permet d'afficher l'arbre des trajets en recursif
	if(noeud_v!=NULL)
	{
		if (noeud_v->valide==true) // on ignore les noeuds qui n'aboutissent pas à la destination
		{
			for(int i =0; i<hauteur-1;i++)
			{
				printf("|   ");
			}
			if(hauteur>0)
			{
				printf("|-> ");
			}
			printf("%s",(tableau_ville[noeud_v->index_ville]).nom_ville);
			if (noeud_v->nb_fils==0)
			{
				printf(" (%dh %dmin / %dkm)\n",duree/60,duree%60,distance);
			}
			else
			{
				printf("\n");
				for (int index_fils=0; index_fils<noeud_v->nb_fils;index_fils++) //On rappelle la fonction pour chacun des fils du noeud
				{
					for (Destinations* dest=tableau_ville[noeud_v->index_ville].destinations; dest!=NULL; dest = dest->suivant) //On retrouve la destination correspondantes dans la liste chaînée des destinations pour avoir la durée et la distance du trajet
					{
						if (((noeud_v->liste_fils)[index_fils])->index_ville == dest->index_ville)
						{
							afficher_arbre_rec(tableau_ville,nb_ville_totale,hauteur+1,duree+(dest->duree),distance+(dest->distance),noeud_v->liste_fils[index_fils]);
						}
					}
				}
			}
		}
	}
	else
	{
		printf("\n");
	}
}

void afficher_arbre (Ville* tableau_ville, int nb_ville_totale, Noeud* noeud_v)
{
	//Permet d'afficher l'arbre des trajets en appelant afficher_arbre_rec avec les bons paramètres
	return afficher_arbre_rec(tableau_ville,nb_ville_totale,0,0,0,noeud_v);
}
