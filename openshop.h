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
Job*** nouvelle_pop(Tache *taches);
void affiche(int indice);
void affiche_machine(int indice);
void affichage_machine_ASCII(int indice);
Tache* tri_croissant();
Tache* tri_decroissant();
void raz_debut_jobs(int indice);
void trouve_solution_croissante(int indice);
void trouve_solution_decroissante(int indice);
void put_tache(Tache t,int indice);
void heuristique_bizarre(int indice);
int date_fin(int indice);
int max(int a, int b);
int min(int a, int b);

Job ***jobs;
int nb_jobs;
int nb_taches;
int nb_pop;
#endif
