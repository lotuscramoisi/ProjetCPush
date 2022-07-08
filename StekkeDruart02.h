#include <stdio.h>

typedef struct joggeur
{
	char nom[12];
	char prenom[12];
	char club[12];
	int dossart;
	int datenjour;
	int datenmois;
	int datenannee;
	char sexe;
	int scoreTotal;
	int nbCourses;
	int nbCoursesPatronnes;
	int nbCoursesChallenges;
	int scoreChallenge[30];
	struct joggeur *suivant;
}joggeur;


typedef struct course
{
	int dossartC;
	int heures;
	int minutes;
	int secondes;
	int place;
	int totalSecondes;
	struct course *suivant;
}course;
