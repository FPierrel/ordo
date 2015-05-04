#include "openshop.h"

Tache nouvelle_tache(int machine, int job, int duree){
    Tache tache;
    tache.machine = machine;
    tache.duree = duree;
    tache.debut = -1;
    tache.job = job;

    return tache;
}

/*Machine* nouvelle_machine(){
    Machine *m = malloc(sizeof(Machine));
    m->taches = malloc(nb_jobs*sizeof(Tache));
    return m;
}*/

Job* nouveau_job(){
	Job *j = malloc(sizeof(Job));
	j->taches = malloc(3*sizeof(Tache));
	return j;	
}

Job** nouveaux_jobs(Tache *taches){
    	int i,k;

    	Job **j = malloc(nb_jobs*sizeof(Job));

	for (i=0;i<nb_jobs;i++){
		j[i]=nouveau_job();
		for(k=0;k<3;k++)			
			j[i]->taches[k]=nouvelle_tache(-1,-1,-1);
	}

	for (i = 0 ; i < nb_taches ; i++)
		j[taches[i].job-1]->taches[taches[i].machine-1] = taches[i];

	return j;
}

void affiche(){
    	int i,j;
    	for (i=0;i<nb_jobs;i++) {
        	printf("Job n°%d\n",i+1);
        	for (j=0;j<3;j++)
			if (jobs[i]->taches[j].job!=-1)
		        	printf("Machine: %d, debut: %d, duree: %d\n",jobs[i]->taches[j].machine,jobs[i]->taches[j].debut,jobs[i]->taches[j].duree);
    	}
}

void affiche_machine(){
	int i,j;
	for (i=0;i<3;i++){
		printf("Machine n°%d\n",i+1);
		for (j=0;j<nb_jobs;j++)
			if (jobs[j]->taches[i].job!=-1)
				printf("Job: %d, debut: %d, duree: %d\n",jobs[j]->taches[i].job,jobs[j]->taches[i].debut,jobs[j]->taches[i].duree);
	}
}

Tache* tri_croissant(){

    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache*));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[k]->taches[j].job != -1){
                taches[pos] = jobs[k]->taches[j];
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
            if (jobs[k]->taches[j].job != -1){
                taches[pos] = jobs[k]->taches[j];
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

void raz_debut_jobs(){
	int i,j;
    	for (i=0;i<nb_jobs;i++)
        	for (j=0;j<3;j++)
			jobs[i]->taches[j].debut=-1;
}

void trouve_solution_croissante(){
    	Tache *t = tri_croissant();
	raz_debut_jobs();
    	int i,j,k,debut,num_machine,num_job;

    	for (i=0; i < nb_taches; i++){
		num_machine = t[i].machine-1;
		num_job = t[i].job-1;
		debut = 0;
        	for (j = 0 ; j < nb_jobs ; j++)
			for (k = 0 ; k < 3 ; k++)
		        	if (jobs[j]->taches[k].debut != -1 && (k == num_machine || j==num_job))
		            		debut = max(debut,jobs[j]->taches[k].debut+jobs[j]->taches[k].duree);

		jobs[num_job]->taches[num_machine].debut = debut;
    	}
}

void trouve_solution_decroissante(){
    	Tache *t = tri_decroissant();
    	int i,j,k,debut,num_machine,num_job;
	raz_debut_jobs();
    	for (i=0; i < nb_taches; i++){
		num_machine = t[i].machine-1;
		num_job = t[i].job-1;
		debut = 0;
        	for (j = 0 ; j < nb_jobs ; j++)
			for (k = 0 ; k < 3 ; k++)
		        	if (jobs[j]->taches[k].debut != -1 && (k == num_machine || j==num_job)){
		            		debut = max(debut,jobs[j]->taches[k].debut+jobs[j]->taches[k].duree);
				}

		jobs[num_job]->taches[num_machine].debut = debut;
    	}
}

int max(int a, int b){
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Machine trouve_solution_machine(Machine m, Jobs j, Solution *s){
/*	srand(time(NULL));
    int i;
    int r=rand()%m.nb_taches;
    for (i=0;i<m.nb_taches;i++){
        m.taches[r].debut
    }
    */



 /* Solution *solutions[100];

    for (i=0;i<100;i++)
        solutions[i]=nouvelle_solution(*m1,*m2,*m3);

    for (i=0;i<10;i++){
        r = (rand() % 3) + 1;
        for (j=0;j<3;j++){
            solutions[i]->machines[r] = trouve_solution_machine(s->machines[r], *job, solutions[i]);
            r = (r+1)%3;
        }
    }*/

}

Solution croisement (Solution s1, Solution s2)
{
   int fils,cut,m;
   Solution sol; // instance du résultat du croisement

   fils = rand() % 2;    // Coisir sur quel parent couper (s1 ou s2)
   m = rand() %  3 ;  //choisir sur quelle machine faire le croisement (m1, m2 ou m3)
   if ( fils == 0 )  //parent 1
   {
     if (m==0) // machine m1 du parent 1
     {
        //récupérer le fi
        ptCoupe = rand() % fi // avec fi la date de fin de toutes les tâches sur la machine choisie  (ptCoupe dépend donc de m )
        sol.m1 = //les tâches se retrouvant avant ptCoupe
        // Ajouter les tâches manquantes dans l'ordre de leur apparition sur la machine 1 dans le parent 2

     }
     else if (m==1) // machine m2 du parent 1
     {
        //récupérer le fi
        ptCoupe = rand() % fi // avec fi la date de fin de toutes les tâches sur la machine choisie  (ptCoupe dépend donc de m )
        //...pareil que m1
     }
     else if (m==2) // machine m3 du parent 1
     {
        //récupérer le fi
        ptCoupe = rand() % fi // avec fi la date de fin de toutes les tâches sur la machine choisie  (ptCoupe dépend donc de m )
        //...pareil que m1

     }
   }

   else {		//parent 2
     // même chose que pour le parent 1 (copier coller)
  }

  //Maintenant on vérifie si il n'y a pas de collisions sur les autres machines après avoir fait le croisement sur une machine précédemment
   if (fils==0)
   {
   }
   else
   {
   }

   return sol;


}

Solution mutation (Solution s)
{
    Solution sol;
    m = rand() %  3 ;  //choisir sur quelle machine faire la mutation (m1, m2 ou m3)
    suivOuPrec = rand() % 2 ; // 0 on mute la tâche courante avec la tâche suivante  ;  1 avec la précédente

    //effectuer la mutation
    return sol;
}
