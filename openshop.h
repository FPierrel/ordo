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
//void affichage_solution_ASCII(Job** jobs);
Tache* tri_croissant();
Tache* tri_decroissant();
void raz_debut_jobs(int indice);
void raz_debut_next(int indice);
void trouve_solution_croissante(int indice);
void trouve_solution_decroissante(int indice);
void put_tache(Tache t,int indice);
void put_tache_next(Tache t, int indice);
void heuristique_bizarre(int indice);
void aleatoire(int indice);
int tache_max(int job, int place, int indice);
Tache * tri_bizarre(int indice);
int date_fin(int indice);
int max(int a, int b);
int min(int a, int b);
//Job** croisement(Tache *taches,Job** j1, Job** j2);
//Job** mutation(Tache* taches, Job** jobs);
void croisement (int p1, int p2, int enf);
void mutation(int p, int enf);
int calcul_obj(int indice);
void tri_pop();
void algo_genetique();

Job ***jobs;
Job ***next_gen;
Job ***temp;
int nb_jobs;
int nb_taches;
int nb_pop;
int nb_pop_keep;
int nb_time;
#endif
