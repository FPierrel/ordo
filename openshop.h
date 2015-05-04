#ifndef __OPEN_SHOP_H__
#define __OPEN_SHOP_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

typedef struct{
    int machine;
    int duree;
    int job;
    int debut;
}Tache;

typedef struct{
    Tache* taches;
}Job;

Tache nouvelle_tache(int machine, int job, int duree);
Job* nouveau_job();
Job** nouveaux_jobs(Tache *taches);
void affiche();
void affiche_machine();
void affichage_machine_ASCII();
Tache* tri_croissant();
Tache* tri_decroissant();
void raz_debut_jobs();
void trouve_solution_croissante();
void trouve_solution_decroissante();
void put_tache(Tache t);
int date_fin();
int max(int a, int b);
int min(int a, int b);

Job **jobs;
int nb_jobs;
int nb_taches;
#endif
