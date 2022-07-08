#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "StekkeDruart02.h"


//Fonction Uniquement appelée depuis notre propre fichier fonction
void courseChallenge(FILE *, joggeur *, int nbJoggeur);
void coursePatronne(FILE *, joggeur *, int nbJoggeur);
int calculPoint(int , course *, int);
int conversionSecondes(int, int ,int);
int scoreTotal(joggeur *, joggeur *);
int classementGlobal(joggeur *, int, joggeur *);
void triParScore(joggeur **, int);

//Attribution de la catégorie au joggeur
const char* setCategorie(int age, char sexe){
	if(sexe == 'F'){
		if(age >= 10 && age <= 19){
			return "ED";
		}
		else if(age >=20 && age <= 39){
			return "DA";
		}
		else if(age >=40 && age <= 49){
			return "A1";
		}
		else if(age >=50 && age <= 59){
			return "A2";
		}
		else if(age >=60 && age <= 69){
			return "A3";
		}
		else if(age >= 70){
			return "A4";
		}
		else
		{
			return "ER";
		}
	}
	else if(sexe == 'M'){
		if(age >= 10 && age <= 19){
			return "EH";
		}
		else if(age >=20 && age <= 39){
			return "SE";
		}
		else if(age >=40 && age <= 49){
			return "V1";
		}
		else if(age >=50 && age <= 59){
			return "V2";
		}
		else if(age >=60 && age <= 69){
			return "V3";
		}
		else if(age >= 70){
			return "V4";
		}
		else
		{
			return "ER";
		}
	}
}


//Calcule de l'age d'un joggeur 
int calculerAge(joggeur *Jogg)
{
	//Variable
	int jour, mois, an, jourjog, moisjog, anjog, age;
	time_t now;
  	
	// Calcule de la date du jour
	time(&now);
	struct tm *local = localtime(&now);      
	jour = local->tm_mday;          
	mois = local->tm_mon + 1;     
	an = local->tm_year + 1900;  
	// Afficher la date courante
	//printf("La date : %02d/%02d/%d\n", jour, mois, an);
	
	//Récupération de la date de naissance du joggeur
	jourjog = Jogg->datenjour;
	moisjog = Jogg->datenmois;
	anjog = Jogg->datenannee;
	//Calcule de l'age du joggeur
	age = an - anjog;
	if(moisjog == mois && jourjog > jour){
		age--;
	}
	else if(moisjog > mois){
		age--;
	}
	return age;
}


//Fonction faites majoritèrement pour le debuging elle affiche toutes les informations des joggeurs
void affichageJoggeur(joggeur *debJ,int nbJoggeur)
{
	int i, age;
	char sexejog;
	const char* categorie;
	joggeur *jEnCours, *jSuivant;
		
	
	jEnCours=debJ;
	
	printf("L'ensemble des joggeurs et toutes les infos les concernants\n");
	printf("-----Nom--------Prenom-------Club--------DateNais----Dossart---Sexe-NbCourse--ScoreTotal--Age-Categorie\n");
	for(i=1;i<=nbJoggeur;i++)
	{
		age = calculerAge(jEnCours);
		categorie = setCategorie(age, jEnCours->sexe);
		printf("%3d %-12s %-12s %-12s %02d/%02d/%4d   %07d    %c     %02d       %06d     %02d      %-2s\n",i, jEnCours->nom, jEnCours->prenom, jEnCours->club, jEnCours->datenjour, jEnCours->datenmois, jEnCours->datenannee, jEnCours->dossart, jEnCours->sexe, jEnCours->nbCourses, jEnCours->scoreTotal, age, categorie);
		jEnCours=jEnCours->suivant;
	}
}


//Demande le fichier qui doit être lu, regarde le type de course et appelle la fonctione de traitement concerant le bon type de course
void enregistrementCourse(joggeur *debJ, int nbJoggeur)
{
	FILE *fECRITURE;
	joggeur *jEnCours;
	int i, j;
	char nomFichier[50];
	char typeCourse[50];                                                      

	printf("Quel est le nom du fichier que vous voulez enregister ? (N'oubliez pas d'inclure l'extension du fichier)\n");
	scanf("%50s", &nomFichier);
	
	FILE *fCourse;
	fCourse = fopen(nomFichier, "r");
	
	fscanf(fCourse, "%*[^\n]\n");
	fscanf(fCourse,"%25s",&typeCourse);
	
	if(strcmp(typeCourse,"challenge")==0 || strcmp(typeCourse,"patronne")==0)	
	{
		//attend avoir d'ouvrir le fichier d'écritue pour savoir si le fichier est valide
		fECRITURE = fopen("StekkeDruart01.dat", "w"); 
		system("cls");
		if(strcmp(typeCourse,"challenge")==0)courseChallenge(fCourse, debJ, nbJoggeur);
		if(strcmp(typeCourse,"patronne")==0)coursePatronne(fCourse, debJ, nbJoggeur);
		
		
		//Pour chaque joueur calcule le score total à partir du nombres de courses patronnés et le score des différents challenges
		jEnCours=debJ;
		for(i=1;jEnCours!=NULL;i++)
		{
			jEnCours->scoreTotal=scoreTotal(debJ,jEnCours);	
			jEnCours=jEnCours->suivant;
		}
		
	
		//Pour chaque course enregistrée, enregistre les différentes informations concernant les joggeurs dans le fichier informations joggeur
		jEnCours=debJ;
		printf("Ecriture dans le fichier reussi\n");
		for(i=1; jEnCours!=NULL ; i++)
		{
			fprintf(fECRITURE, "%-12s %-12s %-12s %02d/%02d/%4d %07d %c %02d %02d %04d", jEnCours->nom, jEnCours->prenom, jEnCours->club, jEnCours->datenjour, jEnCours->datenmois, jEnCours->datenannee, jEnCours->dossart, jEnCours->sexe, jEnCours->nbCoursesPatronnes, jEnCours->nbCoursesChallenges, jEnCours->scoreTotal);
			
			for(j=1;j<=jEnCours->nbCoursesChallenges;j++)fprintf(fECRITURE," %d",jEnCours->scoreChallenge[j]);
			
			fprintf(fECRITURE,"\n");
			
			jEnCours=jEnCours->suivant;
		}
		
		//Ferme le fichier d'écriture pour enregistrer les informations
		fclose(fECRITURE);
	}	
}

//Dans le cadre des courses  challenges
void courseChallenge(FILE *fCourse,joggeur *debJ, int nbJoggeur)
{
	float nbKilometre;
	fscanf(fCourse,"%4f km",&nbKilometre);
	
	int i,j, k , nbParticipant=1, vitessemin;
	float vitesse=0, vitessesec;	
	char sexejog;
	const char* categorie;
	
	joggeur *jEnCours;
	course *debC, *cEnCours, *cSuivant, *boucle;
	

	//Lecture course
	debC=malloc(sizeof(course));
	cEnCours=debC;

	fscanf(fCourse,"%7d",&cEnCours->dossartC);
	
	while(!feof(fCourse))
	{
		//Lecture du dossart et du temps 
		fscanf(fCourse,"%dh%dm%ds",&cEnCours->heures,&cEnCours->minutes,&cEnCours->secondes);
		cEnCours->place=1;
		cEnCours->totalSecondes = conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes);
				
		cSuivant=malloc(sizeof(course));
		cEnCours->suivant=cSuivant;
		cEnCours=cSuivant;
		nbParticipant++;
		fscanf(fCourse,"%7d",&cEnCours->dossartC);
	}
	nbParticipant--;
	//----------------


	cEnCours=debC;
	printf("Resultat de la course challenge:\n");
	printf("Place  Dossart     Nom       Prenom        Club         Temps    Vitesse    Score\n");
	//Pour chaque participant à la course, regarde la liste des joggeurs et leurs donnes un score et une participation supplémentaire
	for(j=1;j<=nbParticipant;j++)
	{
		//Calcul de la vitesse
		//vitesse=nbKilometre*1000/conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes)*3.6;
		//Calcule du temps au km
		vitessemin = (conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes)/nbKilometre)/60;
		vitessesec = (int)(conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes)/nbKilometre)%60;
		jEnCours=debJ;
		for(i=1;i<=nbJoggeur;i++)
		{
			//Si c'est le bon joggeur
			if(jEnCours->dossart==cEnCours->dossartC)
			{
				//Calcul de la place
				boucle=debC;
				for(k=1;k<=nbParticipant;k++)
				{
					if(cEnCours->totalSecondes>boucle->totalSecondes)
					{
						cEnCours->place+=1;
					}
					boucle=boucle->suivant;
				}
				//---

				jEnCours->nbCourses+=1;
				jEnCours->nbCoursesChallenges+=1;
				printf("%d %d",jEnCours->nbCoursesChallenges,calculPoint(nbParticipant,cEnCours,nbKilometre));
				jEnCours->scoreChallenge[jEnCours->nbCoursesChallenges]=calculPoint(nbParticipant,cEnCours,nbKilometre);
				
				printf("   %2d  %07d    %-11s%-11s   %-11s %01dh%02dm%02ds  %02d\'%02.0f/km   %07d\n",cEnCours->place , jEnCours->dossart, jEnCours->nom, jEnCours->prenom, jEnCours->club, cEnCours->heures, cEnCours->minutes, cEnCours->secondes, vitessemin, vitessesec, jEnCours->scoreChallenge[jEnCours->nbCoursesChallenges]);
				
				break;
			}
			jEnCours=jEnCours->suivant;
		}	
		cEnCours=cEnCours->suivant;
	}

	fclose(fCourse);
}


int calculPoint(int nbParticipant, course *cEnCours, int distanceKm)
{
	//(NP - P) / NP x 4000 + (D x 1000) / TS x 1000 + (D x D) x 10 / 4
	//NP = nombre de participants
	//P = place obtenue
	//D x 1000 = distance exprimée en mètres
	//TS = temps réalisé exprimé en secondes
	//D = distance (en kilomètre).
	//Source : http://acrho.org/web/reglement/1011306039/list1187970089/web/reglement/1011306039/list1187970089/f1.html
	int tempsSeconde=conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes);
	float temporaire=(((float)nbParticipant-cEnCours->place)/ nbParticipant*4000 )+(((float)distanceKm*1000)/ tempsSeconde * 1000 )+(((float)distanceKm*distanceKm)* 10/4);
	return (int)temporaire;
}

int conversionSecondes(int heures, int minutes, int secondes)
{
	return heures*3600+minutes*60+secondes;
}


void coursePatronne(FILE *fCourse,joggeur *debJ, int nbJoggeur)
{
	float nbKilometre;
	fscanf(fCourse,"%4f km",&nbKilometre);
	
	int i,j, k , nbParticipant=1;
	float vitesse=0;	
	char sexejog;
	const char* categorie;
	
	joggeur *jEnCours;
	course *debC, *cEnCours, *cSuivant, *boucle;
	

	//Lecture course
	debC=malloc(sizeof(course));
	cEnCours=debC;

	fscanf(fCourse,"%7d",&cEnCours->dossartC);
	
	while(!feof(fCourse))
	{
		//Lecture du dossart et du temps 
		fscanf(fCourse,"%dh%dm%ds",&cEnCours->heures,&cEnCours->minutes,&cEnCours->secondes);
		cEnCours->place=1;
		cEnCours->totalSecondes = conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes);
				
		cSuivant=malloc(sizeof(course));
		cEnCours->suivant=cSuivant;
		cEnCours=cSuivant;
		nbParticipant++;
		fscanf(fCourse,"%7d",&cEnCours->dossartC);
	}
	nbParticipant--;
	//----------------


	cEnCours=debC;
	printf("Resultat de la course patronnee:\n");
	printf("Place  Dossart     Nom       Prenom        Club         Temps    Vitesse    Score\n");
	for(j=1;j<=nbParticipant;j++)
	{
		//Calcul de la vitesse
		vitesse=nbKilometre*1000/conversionSecondes(cEnCours->heures,cEnCours->minutes,cEnCours->secondes)*3.6;
		jEnCours=debJ;
		for(i=1;i<=nbJoggeur;i++)
		{
			//Si c'est le bon joggeur
			if(jEnCours->dossart==cEnCours->dossartC)
			{
				//Calcul de la place
				boucle=debC;
				for(k=1;k<=nbParticipant;k++)
				{
					if(cEnCours->totalSecondes>boucle->totalSecondes)
					{
						cEnCours->place+=1;
					}
					boucle=boucle->suivant;
				}
				//---

				jEnCours->nbCoursesPatronnes+=1;
				jEnCours->nbCourses+=1;
				
				printf("   %2d  %07d    %-11s%-11s   %-11s %01dh%02dm%02ds  %5.2fkm/h   %07d\n",cEnCours->place , jEnCours->dossart, jEnCours->nom, jEnCours->prenom, jEnCours->club, cEnCours->heures, cEnCours->minutes, cEnCours->secondes, vitesse, jEnCours->scoreChallenge[jEnCours->nbCoursesChallenges]);
				
				break;
			}
			jEnCours=jEnCours->suivant;
		}	
		cEnCours=cEnCours->suivant;
	}

	fclose(fCourse);
}


void nbCoursesPatronnesReset(joggeur *debJ,int nbJoggeur)
{
	int i;
	joggeur *jEnCours;
	
	jEnCours=debJ;
	
	for(i=1;i<=nbJoggeur;i++)
	{
		jEnCours->nbCoursesPatronnes=0;
		jEnCours=jEnCours->suivant;
	}
}

joggeur * classement(joggeur *debJ,int nbJoggeur)
{
	int menu=9, i, nbClassementGlobal, nbAfficher, place;
	joggeur *jEnCours, *debJIndice, *jPrece;
	
	//Menu de sélection du type de classement
	while(menu != 0){
		printf("Selection du classement\n");
		printf("1 : Classement globale\n");
		printf("2 : Classement provisoire\n");
		printf("3 : Classement par cat%cgorie\n",130);
		printf("0 : Quitter\n");
		rewind(stdin);
		scanf("%1d", &menu);
		system("cls");
		place = 1;
		nbAfficher=0;
		
		if(menu == 0)
		{
			return debJ;
		}
		
		//Tri le scores des joggeurs pour n'importe quel classement
		triParScore(&debJ, nbJoggeur);

		if(menu == 1)
		{
			printf("Classement globale des joggeurs:\n");
			printf("|-----------------------------------------------------------------------|\n");
			printf("|  Place  |    Nom          |       Prenom        |     ScoreTotal      |\n");
			printf("|---------|-----------------|---------------------|---------------------|\n");
			

			//Pour tout les coureurs avec au moins dix courses
			jEnCours=debJ;
			
			for(i=1;jEnCours!=NULL;i++)
			{
				if(jEnCours->nbCourses>=10)
				{
					if(jPrece->scoreTotal > jEnCours->scoreTotal && i != 1){
						place = i;
					}
					nbAfficher++;
					printf("|  %02d     |  %-15s|      %-15s|     %7d         |\n", place-1,jEnCours->nom,jEnCours->prenom,jEnCours->scoreTotal);
				}
				if(nbAfficher>=10)break;
				jPrece = jEnCours;
				jEnCours=jEnCours->suivant;
			}
			
			printf("|-----------------------------------------------------------------------|\n");
			printf("\n\n");
		}
		
		if(menu == 2)
		{
			printf("Classement globale provisoire:\n");
		//	printf("|------------------------------------------------------------------|\n");
		//	printf("|         Nom          |       Prenom        |     ScoreTotal      |\n");
		//	printf("|----------------------|---------------------|---------------------|\n");
			printf("|-----------------------------------------------------------------------|\n");
			printf("|  Place  |    Nom          |       Prenom        |     ScoreTotal      |\n");
			printf("|---------|-----------------|---------------------|---------------------|\n");
		
			//Pour tout les coureurs avec au moins dix courses
			jEnCours=debJ;
			for(i=1;jEnCours!=NULL;i++)
			{ 
				if(jEnCours->nbCourses>=1)
				{
					if(jPrece->scoreTotal > jEnCours->scoreTotal && i != 1){
						place = i;
					}
					nbAfficher++;
					printf("|  %02d     |  %-15s|      %-15s|     %7d         |\n", place,jEnCours->nom,jEnCours->prenom,jEnCours->scoreTotal);
				}				
				if(nbAfficher>=10)break;
				jPrece = jEnCours;
				jEnCours=jEnCours->suivant;
			}	
			
			printf("|-----------------------------------------------------------------------|\n");
			printf("\n\n");
		}
		
		if(menu == 3)
		{
			const char* categorie;
			char categorieCoureur[2];
			int age;
			
			printf("Voici les différentes catégories disponibles:\n");
			printf(" Age    Homme Femme\n");
			printf("10-19    EH    ED\n");	
			printf("20-39    SE    DA\n");
			printf("40-59    V1    A1\n");
			printf("60-69    V2    A2\n");
			printf(" 70      V3    A3\n");		
			scanf("%s",categorieCoureur);
			
			system("cls");
			printf("Classement par cat%cgorie:\n",130);
			printf("|-----------------------------------------------------------------------|\n");
			printf("|  Place  |    Nom          |       Prenom        |     ScoreTotal      |\n");
			printf("|---------|-----------------|---------------------|---------------------|\n");
		
			jEnCours=debJ;
			for(i=1;jEnCours!=NULL;i++)
			{ 
				age = calculerAge(jEnCours);
				categorie = setCategorie(age, jEnCours->sexe);
				if(jEnCours->nbCourses>=1 && strcmp(categorieCoureur,categorie)==0)
				{
					if(jPrece->scoreTotal > jEnCours->scoreTotal && i != 1){
						place++;
					}
					nbAfficher++;
					printf("|  %02d     |  %-15s|      %-15s|     %7d         |\n", place-1,jEnCours->nom,jEnCours->prenom,jEnCours->scoreTotal);
				}
				if(nbAfficher>=10)break;
				jPrece = jEnCours;
				jEnCours=jEnCours->suivant;
			}
		
			printf("|-----------------------------------------------------------------------|\n");
			printf("\n\n");
		}
	
	}
}

int scoreTotal(joggeur *debJ,joggeur *jEnCours)
{
	int i,j,tmp;
	
	//Tri les challenges pour avoir les dix meilleurs
	for(i=1;i<jEnCours->nbCoursesChallenges;i++)
	{
		for(j=i+1;j<=jEnCours->nbCoursesChallenges;j++)	
		{
			if(jEnCours->scoreChallenge[i]<jEnCours->scoreChallenge[j])
			{
				tmp=jEnCours->scoreChallenge[i];
				jEnCours->scoreChallenge[i]=jEnCours->scoreChallenge[j];
				jEnCours->scoreChallenge[j]=tmp;
			}
		}
	}
	
	jEnCours->scoreTotal=0;
	
	//Enregistre comme le scoreTotal, les dix premiers et donc meilleurs scores du joggeur
	for(i=1;i<=jEnCours->nbCoursesChallenges;i++)
	{
		if(i<=10)
		{
			jEnCours->scoreTotal+=jEnCours->scoreChallenge[i];
		}	
	}
	
	for(i=1;i<=jEnCours->nbCoursesPatronnes;i++)
	{
		//Pour chaque course patronne donne 500 points sauf si la personne à fait plus de 10 courses patronnées
		if(jEnCours->nbCoursesPatronnes<=10)
		{
			jEnCours->scoreTotal+=500;
		}
	}
	
	return jEnCours->scoreTotal;
}


void triParScore(joggeur **debJ, int nbJoggeur)
{		
	int i,j;
	joggeur *jEnCours, *boucle, *precedente, *precedentI;
	
	jEnCours=*debJ;
	for(i=1;jEnCours!=NULL;i++)
	{
		boucle=*debJ;
		precedente=boucle;
		for(j=1;boucle!=NULL;j++)
		{	
			if(jEnCours->dossart == boucle->dossart)
			{
				break;
			}
			if(jEnCours->scoreTotal > boucle->scoreTotal)
			{
				if(j==1)
				{
					precedentI->suivant=jEnCours->suivant;
					jEnCours->suivant=*debJ;
					*debJ=jEnCours;
				}
				else 
				{
					precedentI->suivant=jEnCours->suivant;
					jEnCours->suivant=boucle;
					precedente->suivant=jEnCours;					
				}
				break;
			}

			precedente=boucle;
			boucle= boucle->suivant;
		}
		precedentI=jEnCours;
		jEnCours=jEnCours->suivant;
	}
	
}
