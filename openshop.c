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

void affiche(int indice){
    	int i,j;
    	for (i=0;i<nb_jobs;i++) {
        	printf("Job n°%d\n",i+1);
        	for (j=0;j<3;j++)
			if (jobs[indice][i]->taches[j].job!=-1)
		        	printf("Machine: %d, debut: %d, duree: %d\n",jobs[indice][i]->taches[j].machine,jobs[indice][i]->taches[j].debut,jobs[indice][i]->taches[j].duree);
    	}
}

void affiche_machine(int indice){
	int i,j;
	for (i=0;i<3;i++){
		printf("Machine n°%d\n",i+1);
		for (j=0;j<nb_jobs;j++)
			if (jobs[indice][j]->taches[i].job!=-1)
				printf("Job: %d, debut: %d, duree: %d\n",jobs[indice][j]->taches[i].job,jobs[indice][j]->taches[i].debut,jobs[indice][j]->taches[i].duree);
	}
}

void affichage_machine_ASCII(int indice){
	int i,j,current,k;
	for (i=0;i<3;i++){
		printf("Machine n°%d\t",i+1);
		for (j=0;j<date_fin(indice);j++){
			current=0;
			for (k=0;k<nb_jobs;k++)
				if (jobs[indice][k]->taches[i].debut!=-1 && jobs[indice][k]->taches[i].debut<=j && jobs[indice][k]->taches[i].debut+jobs[indice][k]->taches[i].duree>j){
					current=jobs[indice][k]->taches[i].job;
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

void affiche_next(int indice){
    	int i,j;
    	for (i=0;i<nb_jobs;i++) {
        	printf("Job n°%d\n",i+1);
        	for (j=0;j<3;j++)
			if (next_gen[indice][i]->taches[j].job!=-1)
		        	printf("Machine: %d, debut: %d, duree: %d\n",next_gen[indice][i]->taches[j].machine,next_gen[indice][i]->taches[j].debut,next_gen[indice][i]->taches[j].duree);
    	}
}

void affiche_machine_next(int indice){
	int i,j;
	for (i=0;i<3;i++){
		printf("Machine n°%d\n",i+1);
		for (j=0;j<nb_jobs;j++)
			if (next_gen[indice][j]->taches[i].job!=-1)
				printf("Job: %d, debut: %d, duree: %d\n",next_gen[indice][j]->taches[i].job,next_gen[indice][j]->taches[i].debut,next_gen[indice][j]->taches[i].duree);
	}
}

void affichage_machine_ASCII_next(int indice){
	int i,j,current,k;
	for (i=0;i<3;i++){
		printf("Machine n°%d\t",i+1);
		for (j=0;j<date_fin(indice);j++){
			current=0;
			for (k=0;k<nb_jobs;k++)
				if (next_gen[indice][k]->taches[i].debut!=-1 && next_gen[indice][k]->taches[i].debut<=j && next_gen[indice][k]->taches[i].debut+next_gen[indice][k]->taches[i].duree>j){
					current=next_gen[indice][k]->taches[i].job;
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

void affichage_solution_ASCII(Job** jobs){
	int i,j,current,k;
	for (i=0;i<3;i++){
		printf("Machine n°%d\t",i+1);
		for (j=0;j<50;j++){
			current=0;
			for (k=0;k<nb_jobs;k++)
				if (jobs[k]->taches[i].debut!=-1 && jobs[k]->taches[i].debut<=j && jobs[k]->taches[i].debut+jobs[k]->taches[i].duree>j){
					current=jobs[k]->taches[i].job;
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

Tache* tri_croissant(int indice){

    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[indice][k]->taches[j].job != -1){
                taches[pos] = jobs[indice][k]->taches[j];
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

Tache* tri_decroissant(int indice){
    int i = nb_taches,j,k,pos;
    Tache *taches = malloc(nb_taches*sizeof(Tache));
    pos = 0;
    for (k = 0 ; k < nb_jobs ; k++)
        for (j = 0 ; j < 3 ; j++)
            if (jobs[indice][k]->taches[j].job != -1){
                taches[pos] = jobs[indice][k]->taches[j];
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

void raz_debut_jobs(int indice){
	int i,j;
    	for (i=0;i<nb_jobs;i++)
        	for (j=0;j<3;j++)
			jobs[indice][i]->taches[j].debut=-1;
}

void raz_debut_next(int indice){
	int i,j;
    	for (i=0;i<nb_jobs;i++)
        	for (j=0;j<3;j++)
			next_gen[indice][i]->taches[j].debut=-1;
}

void trouve_solution_croissante(int indice){
    	Tache *t = tri_croissant(indice);
	raz_debut_jobs(indice);
    	int i;

    	for (i=0; i < nb_taches; i++)
		put_tache(t[i],indice);
}

void trouve_solution_decroissante(int indice){
    	Tache *t = tri_decroissant(indice);
    	int i;
	raz_debut_jobs(indice);
    	for (i=0; i < nb_taches; i++)
		put_tache(t[i],indice);
    	
}

void put_tache(Tache t, int indice){
	int i;
	int j=0;
	int bornes [nb_jobs+1][2];
	int start = 0;
	int fin = start+t.duree;
	int boolean=1;

	//Récupère les bornes pour le même job
	for (i=0;i<3;i++)
		if (i!=t.machine-1){
			if (jobs[indice][t.job-1]->taches[i].debut!=-1){
				bornes[j][0]=jobs[indice][t.job-1]->taches[i].debut;
				bornes[j][1]=jobs[indice][t.job-1]->taches[i].debut+jobs[indice][t.job-1]->taches[i].duree;
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
			if (jobs[indice][i]->taches[t.machine-1].debut!=-1){
				bornes[j][0]=jobs[indice][i]->taches[t.machine-1].debut;
				bornes[j][1]=jobs[indice][i]->taches[t.machine-1].debut+jobs[indice][i]->taches[t.machine-1].duree;
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
	
	jobs[indice][t.job-1]->taches[t.machine-1].debut=start;

}

void put_tache_next(Tache t, int indice){
	int i;
	int j=0;
	int bornes [nb_jobs+1][2];
	int start = 0;
	int fin = start+t.duree;
	int boolean=1;

	//Récupère les bornes pour le même job
	for (i=0;i<3;i++)
		if (i!=t.machine-1){
			if (next_gen[indice][t.job-1]->taches[i].debut!=-1){
				bornes[j][0]=next_gen[indice][t.job-1]->taches[i].debut;
				bornes[j][1]=next_gen[indice][t.job-1]->taches[i].debut+next_gen[indice][t.job-1]->taches[i].duree;
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
			if (next_gen[indice][i]->taches[t.machine-1].debut!=-1){
				bornes[j][0]=next_gen[indice][i]->taches[t.machine-1].debut;
				bornes[j][1]=next_gen[indice][i]->taches[t.machine-1].debut+next_gen[indice][i]->taches[t.machine-1].duree;
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
	
	next_gen[indice][t.job-1]->taches[t.machine-1].debut=start;

}

void heuristique_bizarre(int indice){
	Tache *t = tri_bizarre(indice);
    	int i;
	raz_debut_jobs(indice);
	
	for (i=0;i<nb_taches;i++)
		put_tache(t[i],indice);
		
}


void aleatoire(int indice){
	Tache *t = tri_croissant(indice);
	int i;
	int alea;
	int test[nb_taches];
	raz_debut_jobs(indice);		
	for (i=0;i<nb_taches;i++)
		test[i]=0;
	i=0;

	while (i!=nb_taches){
		alea = rand() % nb_taches;
		if (test[alea]==0){
			test[alea]++;
			put_tache(t[alea],indice);
			i++;
		}
	}
	

}

int tache_max(int job, int place, int indice){
	int classement[3];
	
	if (jobs[indice][job]->taches[0].duree>jobs[indice][job]->taches[1].duree)
		if (jobs[indice][job]->taches[0].duree>jobs[indice][job]->taches[2].duree){
			classement[0]=0;
			if (jobs[indice][job]->taches[1].duree>jobs[indice][job]->taches[2].duree){
				classement[1]=1;
				classement[2]=2;
			}
			else{
				classement[1]=2;
				classement[2]=1;
			}
		}
		else {
			classement[0]=2;
			classement[1]=0;
			classement[2]=1;
		}
	else if (jobs[indice][job]->taches[0].duree>jobs[indice][job]->taches[2].duree){
		classement[0]=1;
		classement[1]=0;
		classement[2]=2;
	}
	else if (jobs[indice][job]->taches[1].duree>jobs[indice][job]->taches[2].duree){
		classement[0]=1;
		classement[1]=2;
		classement[2]=0;
	}
	else {
		classement[0]=2;
		classement[1]=1;
		classement[2]=0;
	}

	return classement[place];

}

Tache * tri_bizarre(int indice){
	Tache *taches = malloc(nb_taches*sizeof(Tache));
	int duree_jobs[nb_jobs];
	int i,j;
	int current_job,current_machine;	
	int cpt_jobs[nb_jobs];

	for (i=0;i<nb_jobs;i++){
		duree_jobs[i]=0;
		for (j=0;j<3;j++)
			if (jobs[indice][i]->taches[j].duree!=-1)
				duree_jobs[i]+=jobs[indice][i]->taches[j].duree;
	}

	for (i=0;i<nb_jobs;i++)
		cpt_jobs[i]=0;

	for (i=0;i<nb_taches;i++){
		current_job=0;
		for (j=1;j<nb_jobs;j++)
			if (duree_jobs[current_job]<duree_jobs[j])
				current_job=j;	
		current_machine=tache_max(current_job,cpt_jobs[current_job],indice);
		cpt_jobs[current_job]++;
		duree_jobs[current_job]-=jobs[indice][current_job]->taches[current_machine].duree;
		taches[i]=jobs[indice][current_job]->taches[current_machine];
	}

	return taches;
		

}

int date_fin(int indice){
	int i,j,maxc=0;
	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			maxc = max(maxc,jobs[indice][i]->taches[j].debut+jobs[indice][i]->taches[j].duree);

	return maxc;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}

/*Job** croisement(Tache *taches, Job** j1, Job** j2){ //Ne test pas la validité de la solution !!
	int fils = rand()%2; //parent sur lequel on coupe
	int m = rand()%3; //machine sur lequel on fait le croisement
	int ptCoupe = 0;
	int i,j;
	Job **res = nouveaux_jobs(taches);
	Job **s1;
	Job **s2;
	
	if (fils == 0){
		s1 = j1;
		s2 = j2;
	}
	else{
		s1 = j2;
		s2 = j1;
	}
	
	for (i = 0 ; i < nb_jobs ; i++)
		if (s1[i]->taches[m].debut + s1[i]->taches[m].duree > ptCoupe)
			ptCoupe = s1[i]->taches[m].debut + s1[i]->taches[m].duree;
		
	//On recopie et complete
	for(i = 0 ; i < nb_jobs ; i++){
		for (j = 0 ; j < 3 ; j++){
			if (j != m){				
				res[i]->taches[j].debut = s1[i]->taches[j].debut;
			}
			else
			{				
				if (s1[i]->taches[m].debut + s1[i]->taches[m].duree <= ptCoupe)
					res[i]->taches[j].debut = s1[i]->taches[j].debut;
				else
					res[i]->taches[j].debut = s2[i]->taches[j].debut;	
			}
		}
	}
	
	printf("Test croisement\n");
	printf("fils %d, machine %d, ptCoupe %d\n",fils,m,ptCoupe);
	affichage_solution_ASCII(j1);
	affichage_solution_ASCII(j2);
	affichage_solution_ASCII(res);
	return res;
}*/


void croisement (int p1, int p2, int enf){
	int parent = rand()%2; 	//parent sur lequel on coupe
	if (parent==1){
		parent=p1;
		p1=p2;
		p2=parent;
	}
	int m = rand()%3;	//machine sur laquelle on coupe
	int ptCoupe = rand()%nb_jobs;
	ptCoupe=jobs[p1][ptCoupe]->taches[m].debut+jobs[p1][ptCoupe]->taches[m].duree;
	Tache *t = malloc(nb_jobs*sizeof(Tache));
	int i,j,k=0;	

	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			if (j!=m)
				next_gen[enf][i]->taches[j]=jobs[p1][i]->taches[j];
			else
				if (jobs[p1][i]->taches[j].debut+jobs[p1][i]->taches[j].duree<=ptCoupe)
					next_gen[enf][i]->taches[j]=jobs[p1][i]->taches[j];
				else{
					t[k]=jobs[p2][i]->taches[j];
					k++;
				}

	


	int echange = 1;
	Tache tmp;
	i = k;
	while ((i>0) && (echange)){
		echange = 0;
		for (j = 0 ; j < i-1 ; j++){
			if (t[j].debut > t[j+1].debut){
		        	tmp = t[j];
		        	t[j] = t[j+1];
		        	t[j+1] = tmp;
		        	echange = 1;
		    	}
		}
		i--;
    	}
	

	for (i=0;i<k;i++)
		put_tache_next(t[i],enf);
			

}

void mutation(int p, int enf){
	int m = rand()%3;	//machine sur laquelle on coupe
	int i,j;

	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			if (j!=m)
				next_gen[enf][i]->taches[j]=jobs[p][i]->taches[j];

	j=rand()%nb_jobs;

	for (i=0;i<nb_jobs;i++){
		if (jobs[p][j]->taches[m].duree!=-1)
			put_tache_next(jobs[p][j]->taches[m],enf);
		j=(j+1)%nb_jobs;
	}				
				


}

int calcul_obj(int indice){
	int i,j,maxc,somme=0;

	for (i=0;i<nb_jobs;i++){
		maxc=0;
		for (j=0;j<3;j++)
			maxc = max(maxc,jobs[indice][i]->taches[j].debut+jobs[indice][i]->taches[j].duree);
		somme +=  maxc;
	}

	return somme;
		

}

void tri_pop(){
	int i,j,tmp;
	int indice[nb_pop];
	int somme[nb_pop];
	
	for (i=0;i<nb_pop;i++){
		somme[i]=calcul_obj(i);
		indice[i]=i;
		temp[i]=jobs[i];
	}
	int echange=1;
	i=nb_pop;
	while ((i>0) && (echange)){
		echange = 0;
		for (j = 0 ; j < i-1 ; j++){
			if (somme[j] > somme[j+1]){
		        	tmp = somme[j];
		        	somme[j] = somme[j+1];
		        	somme[j+1] = tmp;
				tmp = indice[j];
				indice[j] = indice[j+1];
				indice[j+1] = tmp;
				echange = 1;
		    	}
		}
		i--;
    	}

	for (i=0;i<nb_pop;i++)
		jobs[i]=temp[indice[i]];

}

void algo_genetique(){
	int i,alea,p1,p2,j=0;

	//Création de la population de base
	for (i=0;i<nb_pop;i++){
		raz_debut_jobs(i);		
		raz_debut_next(i);
		aleatoire(i);
	}
	
	while(j!=nb_time){
		//Tri de la population
		tri_pop();
		
		//affichage_machine_ASCII(0);
		for (i=0;i<nb_pop;i++)
			if (i<nb_pop_keep)
				next_gen[i]=jobs[i];
			else{	
				alea=rand()%100;
				if (alea<80){
					p1=rand()%100;
					if (p1<50)
						p1=rand()%(int)(0.2*nb_pop);
					else if (p1>80)
						p1=rand()%(int)(0.3*nb_pop)+0.7*nb_pop;
					else
						p1=rand()%(int)(0.5*nb_pop)+0.2*nb_pop;
					p2=rand()%100;
					if (p2<50)
						p2=rand()%(int)(0.2*nb_pop);
					else if (p2>80)
						p2=rand()%(int)(0.3*nb_pop)+0.7*nb_pop;
					else
						p2=rand()%(int)(0.5*nb_pop)+0.2*nb_pop;
					croisement(p1,p2,i);
					
				}
				else if (alea>95){
					next_gen[i]=jobs[i];
				}
				else{
					p1=rand()%100;
					if (p1<50)
						p1=rand()%(int)(0.5*nb_pop);
					else if (p1>80)
						p1=rand()%(int)(0.3*nb_pop)+0.7*nb_pop;
					else
						p1=rand()%(int)(0.2*nb_pop)+0.2*nb_pop;
					mutation(p1,i);
				}

			}
		for (i=0;i<nb_pop;i++)
			jobs[i]=next_gen[i];
		
		j++;
	}
	tri_pop();
	
			

}

/*Job** mutation(Tache* taches, Job** jobs){
	printf("mutation\n");
	affichage_solution_ASCII(jobs);
	
	Job **res = nouveaux_jobs(taches);
	int m, sens, num_j;
	int date_prem = INT_MAX, prem, date_der = INT_MIN, der;
	int i, j;
	int swap, delta;
	int bon_param = 0;
	
	while (!bon_param){ //test si la tache n'est pas toute seul sur la machine
		m = rand() %  3 ;  //choisir sur quelle machine faire la mutation (m1, m2 ou m3)
		sens = rand() % 2 ; // 0 on echange avec celle d'avant, 1 après (sauf si c'est la premiere ou la derniere sinn on mutera quasi jamais)
		num_j = rand() % nb_jobs; //num du job a echanger
		bon_param = 1;
		for (i = 0 ; i < nb_jobs ; i++)
			if (jobs[i]->taches[m].debut >= 0 && i != num_j)
				bon_param = 1; 
		if (jobs[num_j]->taches[m].debut < 0)
			bon_param = 0;
	}
	
	for (i = 0 ; i < nb_jobs ; i++){
		if (jobs[i]->taches[m].debut < date_prem && jobs[i]->taches[m].debut >= 0){
			date_prem = jobs[i]->taches[m].debut;
			prem = i;
		}
		if (jobs[i]->taches[m].debut > date_der && jobs[i]->taches[m].debut >= 0){
			date_der = jobs[i]->taches[m].debut;
			der = i;
		}
	}	
	if (num_j == prem)
		sens = 1;
	else if (num_j == der)
		sens = 0;
	
	//recopie des deux autres machines
	for (i = 0 ; i < nb_jobs ; i++)
		for (j = 0 ; j < 3 ; j++)
			if (j!=m)
				res[i]->taches[j].debut = jobs[i]->taches[j].debut;

	if (sens==0){
		//recherche du numero de tache juste avant
		date_prem = INT_MIN; 
		for (j = 0 ; j < nb_jobs ; j++)
			if (jobs[j]->taches[m].debut > date_prem && jobs[j]->taches[m].debut < jobs[num_j]->taches[m].debut && jobs[j]->taches[m].debut >= 0)
			{
				date_prem = jobs[j]->taches[m].debut;
				swap = j;
			}

		//on echange les taches et decales les taches d'ap si necessaire
		delta = jobs[num_j]->taches[m].duree - jobs[swap]->taches[m].duree;
		if (delta > 0) //on decales les taches d'ap
			for (j = 0 ; j < nb_jobs ; j++)
				if (jobs[j]->taches[m].debut > jobs[num_j]->taches[m].debut)
					jobs[j]->taches[m].debut += delta;
					

		//echange
		i = jobs[num_j]->taches[m].debut;
		jobs[num_j]->taches[m].debut = jobs[swap]->taches[m].debut;
		jobs[swap]->taches[m].debut = i;
	}
	else{
		date_der = INT_MAX;
		for (j = 0 ; j < nb_jobs ; j++)
			if (jobs[j]->taches[m].debut < date_der && jobs[j]->taches[m].debut > jobs[num_j]->taches[m].debut && jobs[j]->taches[m].debut >= 0)
			{
				date_der = jobs[j]->taches[m].debut;
				swap = j;
			}
		
		delta = jobs[num_j]->taches[m].duree - jobs[swap]->taches[m].duree; 
		
		if (delta > 0)
			for (j = 0 ; j < nb_jobs ; j++)
				if (jobs[j]->taches[m].debut > jobs[num_j]->taches[m].debut)
					jobs[j]->taches[m].debut += delta;
		
		i = jobs[num_j]->taches[m].debut;
		jobs[num_j]->taches[m].debut = jobs[swap]->taches[m].debut;
		jobs[swap]->taches[m].debut = i;
	}
	for (i = 0 ; i < nb_jobs ; i++)
		res[i]->taches[m].debut = jobs[i]->taches[m].debut;
	
	printf("ap mut\n");
	affichage_solution_ASCII(res);
	return res;
}*/
