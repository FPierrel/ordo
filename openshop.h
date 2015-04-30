#ifndef __OPEN_SHOP_H__
#define __OPEN_SHOP_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    int machine;
    int duree;
    int job;
    int debut;
}Tache;

typedef struct{
    Tache** taches;
}Machine;

typedef struct{
    Tache* taches;
}Job;

typedef struct{
    Machine* machines;
}Solution;

Tache nouvelle_tache(int machine, int job, int duree);
Machine* nouvelle_machine();
Job* nouveaux_jobs(Tache *taches);
void affiche();
Tache* tri_croissant();
Tache* tri_decroissant();
void trouve_solution_croissante();

Job *jobs;
int nb_jobs;
int nb_taches;
#endif
