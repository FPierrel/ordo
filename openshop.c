#include "openshop.h"

Tache nouvelle_tache(int machine, int job, int duree){
    Tache tache;
    tache.machine = machine;
    tache.duree = duree;
    tache.debut = -1;
    tache.job = job;

    return tache;
}

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

Job*** nouvelle_pop(Tache *taches){
	int i;
	
	Job ***j = malloc(nb_pop*nb_jobs*sizeof(Job));

	for (i=0;i<nb_pop;i++)
		j[i]=nouveaux_jobs(taches);
	return j;
}

void affiche(){
    	int i,j;
    	for (i=0;i<nb_jobs;i++) {
        	printf("Job n°%d\n",i+1);
        	for (j=0;j<3;j++)
			if (jobs[0][i]->taches[j].job!=-1)
		        	printf("Machine: %d, debut: %d, duree: %d\n",jobs[0][i]->taches[j].machine,jobs[0][i]->taches[j].debut,jobs[0][i]->taches[j].duree);
    	}
}

void affiche_machine(){
	int i,j;
	for (i=0;i<3;i++){
		printf("Machine n°%d\n",i+1);
		for (j=0;j<nb_jobs;j++)
			if (jobs[0][j]->taches[i].job!=-1)
				printf("Job: %d, debut: %d, duree: %d\n",jobs[0][j]->taches[i].job,jobs[0][j]->taches[i].debut,jobs[0][j]->taches[i].duree);
	}
}

void affichage_machine_ASCII(){
	int i,j,current,k;
	for (i=0;i<3;i++){
		printf("Machine n°%d\t",i+1);
		for (j=0;j<date_fin();j++){
			current=0;
			for (k=0;k<nb_jobs;k++)
				if (jobs[0][k]->taches[i].debut!=-1 && jobs[0][k]->taches[i].debut<=j && jobs[0][k]->taches[i].debut+jobs[0][k]->taches[i].duree>j){
					current=jobs[0][k]->taches[i].job;
					break;
				}
			if (current==0)
				printf("-");
			else
				printf("%d",current);
		}
		printf("\n");		
	}
}

Tache* tri_croissant(){

    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache*));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[0][k]->taches[j].job != -1){
                taches[pos] = jobs[0][k]->taches[j];
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
            if (jobs[0][k]->taches[j].job != -1){
                taches[pos] = jobs[0][k]->taches[j];
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
			jobs[0][i]->taches[j].debut=-1;
}

void trouve_solution_croissante(){
    	Tache *t = tri_croissant();
	raz_debut_jobs();
    	int i;

    	for (i=0; i < nb_taches; i++)
		put_tache(t[i]);
}

void trouve_solution_decroissante(){
    	Tache *t = tri_decroissant();
    	int i;
	raz_debut_jobs();
    	for (i=0; i < nb_taches; i++)
		put_tache(t[i]);
    	
}

void put_tache(Tache t){
	int i;
	int j=0;
	int bornes [nb_jobs+1][2];
	int start = 0;
	int fin = start+t.duree;
	int boolean=1;

	//Récupère les bornes pour le même job
	for (i=0;i<3;i++)
		if (i!=t.machine-1){
			if (jobs[0][t.job-1]->taches[i].debut!=-1){
				bornes[j][0]=jobs[0][t.job-1]->taches[i].debut;
				bornes[j][1]=jobs[0][t.job-1]->taches[i].debut+jobs[0][t.job-1]->taches[i].duree;
			}
			else{
				bornes[j][0]=-1;
				bornes[j][1]=-1;
			}
			j++;
		}
	//Récupère les bornes pour la même machines
	for (i=0;i<nb_jobs;i++)	
		if (i!=t.job-1){
			if (jobs[0][i]->taches[t.machine-1].debut!=-1){
				bornes[j][0]=jobs[0][i]->taches[t.machine-1].debut;
				bornes[j][1]=jobs[0][i]->taches[t.machine-1].debut+jobs[0][i]->taches[t.machine-1].duree;
			}
			else{
				bornes[j][0]=-1;
				bornes[j][1]=-1;
			}
			j++;
		}
	//Test si possible de mettre à 0
	for (i=0;i<nb_jobs+1;i++)
		if (bornes[i][0]!=-1 && bornes[i][0]<fin){
			boolean=0;
			break;
		}

	//Si pas possible cherche le minimum où mettre
	if (boolean==0){
		start=INT_MAX;
		for (i=0;i<nb_jobs+1;i++)
			if (bornes[i][0]!=-1){
				boolean=1;
				for (j=0;j<nb_jobs+1;j++)
					if (bornes[j][0]!=-1 && bornes[j][0]<(bornes[i][1]+t.duree) && bornes[j][1]>bornes[i][1]){
						boolean=0;
						break;
					}
				if (boolean==1){
					start=min(start,bornes[i][1]);
					fin=start+t.duree;
				}
			}
	}
	
	jobs[0][t.job-1]->taches[t.machine-1].debut=start;

}

int date_fin(){
	int i,j,maxc=0;
	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			maxc = max(maxc,jobs[0][i]->taches[j].debut+jobs[0][i]->taches[j].duree);

	return maxc;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*Solution croisement (Solution s1, Solution s2)
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
}*/
