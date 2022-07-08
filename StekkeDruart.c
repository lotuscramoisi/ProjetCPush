#include "StekkeDruart01.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


main()
{
	
//Fichier
//-------------------
	FILE *fdat, *fhappend;
	fdat = fopen("StekkeDruart01.dat", "r");
	
//Structures
//-------------------
	joggeur *debJ, *jEnCours, *jSuivant, *jTest;
	

	
//Fonction
//-------------------
	
	void affichageJoggeur(joggeur *, int);
	void enregistrementCourse(joggeur *, int);
	void nbCoursesPatronnesReset(joggeur *,int);
	joggeur * classement(joggeur *,int);
	int calculerAge(joggeur *);
	void suppressionJoggeur(joggeur *, int);
	
	
//Variables
//-------------------
	int i,j, nbJoggeur=1, menu=9, dossart, datenjour, datenmois, datenannee, valider, testsexe=1, testdossart=1, testdaten=1, testNom=1, testPrenom=1, testClub=1, menusuppr, scanjoggsuppr, testnosuppr=1;
	char sexe;
	char nom[30], prenom[30], club[30];
//Programme principal
//-------------------

	//Lecture des joggeurs on le fait au début et puis on affiche juste la liste des joggeurs. On ne peut de toute manière pas lire plusieurs fois le même ficher donc pas de sens de le mettre dans un while
	//On ne lit pas les 2 premières lignes du fichier
//	fscanf(fdat, "%*[^\n]\n");
//	fscanf(fdat, "%*[^\n]\n");
	debJ=malloc(sizeof(joggeur));
	jEnCours=debJ;
	for(i=0;i<30;i++)jEnCours->scoreChallenge[i]=0;
	fscanf(fdat,"%11s %11s %11s %2d/%2d/%4d %7d %c %2d %2d %d",jEnCours->nom,jEnCours->prenom,jEnCours->club, &jEnCours->datenjour, &jEnCours->datenmois, &jEnCours->datenannee, &jEnCours->dossart, &jEnCours->sexe, &jEnCours->nbCoursesPatronnes, &jEnCours->nbCoursesChallenges, &jEnCours->scoreTotal);	
	jEnCours->nbCourses = jEnCours->nbCoursesChallenges + jEnCours->nbCoursesPatronnes;
	for(j=1;j<=jEnCours->nbCoursesChallenges;j++)fscanf(fdat,"%d",&jEnCours->scoreChallenge[j]);	
	
	while(!feof(fdat))
	{
		jSuivant=malloc(sizeof(joggeur));
		jEnCours->suivant=jSuivant;
		jEnCours=jSuivant;
		for(i=0;i<30;i++)jEnCours->scoreChallenge[i]=0;
		fscanf(fdat,"%11s %11s %11s %2d/%2d/%4d %7d %c %2d %2d %d",jEnCours->nom,jEnCours->prenom,jEnCours->club, &jEnCours->datenjour, &jEnCours->datenmois, &jEnCours->datenannee, &jEnCours->dossart, &jEnCours->sexe, &jEnCours->nbCoursesPatronnes, &jEnCours->nbCoursesChallenges, &jEnCours->scoreTotal);	
		

		for(j=1;j<=jEnCours->nbCoursesChallenges;j++)
		{ 
			fscanf(fdat,"%d",&jEnCours->scoreChallenge[j]);
//			printf("i:%d Score:%d",j,jEnCours->scoreChallenge[j]);
		}
//		printf("\n");
		
		jEnCours->nbCourses = jEnCours->nbCoursesChallenges + jEnCours->nbCoursesPatronnes;
		nbJoggeur+=1;		
	}
	
	nbJoggeur--;
	//Retour au début de la liste chaînée des joggeurs
	jEnCours=debJ;
	//Parcours de la liste jusque la fin
	for(i=1; i<nbJoggeur; i++){
			jEnCours=jEnCours->suivant;
	}
	//Fin de la liste chaînée avec NULL
	jEnCours->suivant= NULL;
	//-------------------
	
	//Reset nbCoursesPatronnes variables valeurs absurdes
	nbCoursesPatronnesReset(debJ,nbJoggeur);
	
	fclose(fdat);

	//printf("Le nombre de joggeur : %d\n", nbJoggeur);
	while(menu != 0){
		
	
	printf("    ___     ______    ____     __  __   ____          \n");
	printf("   /   |   / ____/   / __ \\   / / / /  / __ \\       \n");
	printf("  / /| |  / /       / /_/ /  / /_/ /  / / / /        \n");
	printf(" / ___ | / /___    / _, _/  / __  /  / /_/ /     Logiciel de gestion des joggeurs et courses de  \n");
	printf("/_/  |_| \\____/   /_/ |_|  /_/ /_/   \\____/      l\'Amicale des Courses sur Route du Hainaut Occidental   \n");
                                            


                                            

		printf("____________________________________\n");
		printf("|               MENU               |\n");
		printf("|__________________________________|\n");
		printf("|1 : Ajouter un joggeur            |\n");
		printf("|2 : Afficher la liste des joggeurs|\n");
		printf("|3 : Enregistrer une course        |\n");
		printf("|4 : Afficher les classements      |\n");
		printf("|0 : Quitter                       |\n");
		printf("|__________________________________|\n");
		rewind(stdin);
		scanf("%1d", &menu);
		system("cls");
		if(menu == 1){
			fhappend = fopen("StekkeDruart01.dat", "a");
			//Ajout joggeur dans une fonction ?
			//Il faudrait aussi vérifier si les données encodées on du sens. Si on demande un chiffre vérifier que c'est un chiffre et vérifier la taille mais ce n'est pas une priorité
			printf("Inscription\n");
			printf("-----------\n");
			//Vérification du nom du joggeur
			while(testNom ==1){
				printf("Veuillez entrer le nom du joggeur (11 caracteres max)\n");
				rewind(stdin);
				scanf("%12s", &nom);
				
				if(strlen(nom)<=11)
				{
					testNom=0;
				}
				else printf("Longueur du nom invalide\n");
			}
			//Vérification du prénom du joggeur
			while(testPrenom ==1){
				printf("Veuillez entrer le prenom du joggeur (11 caracteres max)\n");
				rewind(stdin);
				scanf("%12s", &prenom);
				
				if(strlen(prenom)<=11)
				{
					testPrenom=0;
				}
				else printf("Longueur du pr%cnom invalide\n",130);
			}
			//Vérification du nom du club
			while(testClub ==1){
				printf("Veuillez entrer le club du joggeur (11 caracteres max)\n");
				rewind(stdin);
				scanf("%s", &club);
				
				if(strlen(club)<=11)testClub=0;
				
				else printf("Longueur du nom de club invalide\n",130);
				
			}
			//Vérification de la date de naissance
			while(testdaten == 1){
				printf("Veuillez entrer la date de naissance du joggeur (JJ/MM/AAAA)\n");
				rewind(stdin);
				scanf("%3d/%3d/%5d", &datenjour, &datenmois, &datenannee);
				if(datenjour > 0 && datenjour <= 31 && datenmois > 00 && datenmois <= 12 && datenannee<2012 && datenannee>1900){
					testdaten = 0;
				}
				else{
					printf("Date invalide\n");
				}
				
			}
			//Vérification du dossart
			while(testdossart == 1){
				printf("Veuillez entrer le numero de dossard du joggeur (7 chiffres)\n");
				rewind(stdin);
				scanf("%8d", &dossart);
				jTest = debJ;
				for(i=1; i<= nbJoggeur; i++){
					if(jTest->dossart == dossart){
						printf("Numero deja existant\n");
						break;
					}
					//Le test avec le dossart au dessus de 10000000 c'est pour vérifier que le numéro de dossart est valide 
					//j'ai donnée une taille de 8 alors que le dossart est de 7 pour ne pas tronquer le nombrer à 6 chiffres
					// et écrire au informations suivantes un valeur instantanément
					else if(i == nbJoggeur && dossart<10000000 && dossart>=0)
						testdossart = 0;
					jTest = jTest->suivant;
				}
			}
			//Vérification du sexe
			while(testsexe == 1){
				printf("Veuillez entrer le sexe du joggeur (M/F)\n");
				rewind(stdin);
				scanf("%s", &sexe);
				if(sexe == 'M')
					testsexe = 0;
				else if(sexe == 'F')
					testsexe = 0;
			}
			
			printf("1 : Valider\n2 : Annuler\n");
			rewind(stdin);
			scanf("%1d", &valider);
			if(valider == 1){
				if(nbJoggeur == 0){
					debJ=malloc(sizeof(joggeur));
				}
				//Retour au début de la liste chaînée des joggeurs
				jEnCours=debJ;
				if(nbJoggeur != 0){
					//Parcours de la liste jusque la fin
					for(i=1; i<nbJoggeur; i++){
						jEnCours=jEnCours->suivant;
					}	
						//attribution d'un nouvel emplacement mémoire pour le joggeur suivant
					jSuivant=malloc(sizeof(joggeur));
					jEnCours->suivant=jSuivant;
					jEnCours=jSuivant;
				}
				//Ajout des informations du nouveau Joggeur
				strcpy(jEnCours->nom, nom);
				strcpy(jEnCours->prenom, prenom);
				strcpy(jEnCours->club, club);
				jEnCours->datenjour = datenjour;
				jEnCours->datenmois = datenmois;
				jEnCours->datenannee = datenannee;
				jEnCours->dossart = dossart;
				jEnCours->sexe = sexe;
				jEnCours->scoreTotal = 0;
				jEnCours->nbCourses = 0;
				jEnCours->nbCoursesPatronnes = 0;
				jEnCours->nbCoursesChallenges = 0;
				jEnCours->suivant = NULL;
				nbJoggeur++;
				
				
				printf("\nInscription validee\n");
				fprintf(fhappend,"%-12s %-12s %-12s %02d/%02d/%4d %07d %c %02d %02d %04d\n", jEnCours->nom, jEnCours->prenom, jEnCours->club, jEnCours->datenjour, jEnCours->datenmois, jEnCours->datenannee, jEnCours->dossart, jEnCours->sexe, jEnCours->nbCoursesPatronnes, jEnCours->nbCoursesChallenges, jEnCours->scoreTotal);	
				fclose(fhappend);
				testsexe = 1;
				testdossart = 1;
			}
			else{
				testNom = 1;
				testPrenom = 1;
				testClub = 1;
				testdaten = 1;
				testdossart = 1;
				testsexe = 1;
				system("cls");
			}
			
		}
		
		if(menu == 2){
			  
			affichageJoggeur(debJ,nbJoggeur);
			printf("____________________________________\n");
			printf("|               MENU               |\n");
			printf("|__________________________________|\n");
			printf("|1 : Supprimer un joggeur          |\n");
			printf("|2 : Retourner au menu principal   |\n");
			printf("|__________________________________|\n");
			rewind(stdin);
			scanf("%1d", &menusuppr);
			if(menusuppr == 1){
				printf("Entrez le numero du joggeur a supprimer ou entrez 0 pour annuler la suppression\n");
				scanf("%4d", &scanjoggsuppr);
				while(testnosuppr== 1){
					if(scanjoggsuppr > 0 && scanjoggsuppr <= nbJoggeur){
						system("cls");
						suppressionJoggeur(debJ, scanjoggsuppr);
						printf("Suppression du joggeur numero %04d\n", scanjoggsuppr);
						nbJoggeur--;
						testnosuppr = 0;
					}
					else if(scanjoggsuppr == 0){
						system("cls");
						break;
					}
					else{
						printf("Numero incorrect, veuillez entrer un nouveau numero ou entrez 0 pour annuler la suppression\n");
						scanf("%4d", &scanjoggsuppr);
					}
				}
				testnosuppr = 1;
			}
			else{
				system("cls");
			}
		}
		
		
		if(menu == 3){
			
			enregistrementCourse(debJ,nbJoggeur);
		}
		
		if(menu ==4){
		
			debJ=classement(debJ,nbJoggeur);
		}	
	}
}


