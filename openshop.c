#include "openshop.h"

Tache nouvelle_tache(int machine, int job, int duree){
    Tache tache;
    tache.machine = machine;
    tache.duree = duree;
    tache.debut = -1;
    tache.job = job;

    return tache;
}

Machine* nouvelle_machine(){
    Machine *m = malloc(sizeof(Machine));
    m->taches = malloc(nb_jobs*sizeof(Tache));
    return m;
}


Job* nouveaux_jobs(Tache *taches){
    int i,k;

    Job *j = malloc(nb_jobs*sizeof(Job));

    for (i = 0 ; i < nb_jobs ; i++){
        j[i].taches = malloc(3*sizeof(Tache));

        for (k=0;k<3;k++)
            *j[i].taches[k] = NULL;
    }
    for (i = 0 ; i < nb_taches ; i++)
        j[taches[i].job-1].taches[taches[i].machine] = taches[i];

    return j;
}

void affiche(){
    int i,j;
    for (i=0 ; i < nb_jobs ; i++)
    {
        printf("Job n°%d\n",i);
        for (j=0 ; j < 3 ;j++)
            if (jobs[i].taches[j] != NULL)
                printf("Machine: %d, debut: %d, duree: %d\n",(*jobs[i].taches[j]).machine,
                       (*jobs[i].taches[j]).debut,
                       (*jobs[i].taches[j]).duree);
    }
}



Tache* tri_croissant(){
    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache*));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[i].taches[j] != NULL)
            {
                taches[pos] = *jobs[i].taches[j];
                pos++;
            }

    int echange = 1;
    Tache tmp;
    while ((i>0) && (echange)){
        echange = 0;
        for (j = 0 ; j < i-1 ; j++){
            if (taches[j].duree > taches[j+1].duree){
                tmp = taches[j];
                taches[j] = taches[j+1];
                taches[j+1] = tmp;
                echange = 1;
            }
        }
        i--;
    }

    return taches;
}

Tache* tri_decroissant(){
    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache*));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[i].taches[j] != NULL)
            {
                taches[pos] = *jobs[i].taches[j];
                pos++;
            }

    int echange = 1;
    Tache tmp;
    while ((i>0) && (echange)){
        echange = 0;
        for (j = 0 ; j < i-1 ; j++){
            if (taches[j].duree < taches[j+1].duree){
                tmp = taches[j];
                taches[j] = taches[j+1];
                taches[j+1] = tmp;
                echange = 1;
            }
        }
        i--;
    }

    return taches;
}
void trouve_solution_croissante(){
    Tache *t = tri_croissant();
    int i,j,k,num,debut,num_machine,num_job;

    for (i=0; i < nb_taches; i++){
        num_machine = t[i].machine-1;
        num_job = t[i].job-1;
        debut = 0;
        for (j = 0 ; j < nb_jobs ; j++){
            for (k = 0 ; j < 3 ; k++){
                if (jobs[j].taches[k] != NULL)
                    if ((num_machine != (*jobs[j].taches[k]).machine && num_job == (*jobs[j].taches[k]).job)
                            || (num_machine == (*jobs[j].taches[k]).machine && num_job != (*jobs[j].taches[k]).job)
                            && (*jobs[j].taches[k]).debut != -1)
                        debut = max(debut,(*jobs[j].taches[k]).debut+(*jobs[j].taches[k]).duree);
            }
        }
        (*jobs[num_job].taches[num_machine]).debut = debut;
    }
}

int max(int a, int b){
    return a > b ? a : b;
}
