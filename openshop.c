#include "openshop.h"

//Crée une tache
Tache nouvelle_tache(int machine, int job, int duree){
    Tache tache;
    tache.machine = machine;
    tache.duree = duree;
    tache.debut = -1;
    tache.job = job;

    return tache;
}

//Crée un job
Job* nouveau_job(){
	Job *j = malloc(sizeof(Job));
	j->taches = malloc(3*sizeof(Tache));
	return j;	
}

//Crée un tableau de job (une solution)
Job** nouveaux_jobs(Tache *taches){
    	int i,k;

    	Job **j = malloc(nb_jobs*sizeof(Job));
	//Initialise tout à -1
	for (i=0;i<nb_jobs;i++){
		j[i]=nouveau_job();
		for(k=0;k<3;k++)			
			j[i]->taches[k]=nouvelle_tache(-1,-1,-1);
	}
	//Met uniquement les taches existantes
	for (i = 0 ; i < nb_taches ; i++)
		j[taches[i].job-1]->taches[taches[i].machine-1] = taches[i];

	return j;
}

//Crée un tableau de tableau de job (un tableau de solutions donc une population de solutions)
Job*** nouvelle_pop(Tache *taches){
	int i;
	
	Job ***j = malloc(nb_pop*nb_jobs*sizeof(Job));

	for (i=0;i<nb_pop;i++)
		j[i]=nouveaux_jobs(taches);
	return j;
}

//Affiche la solution indice, en fonction des jobs, de la population actuelle (jobs)
void affiche(int indice){
    	int i,j;
    	for (i=0;i<nb_jobs;i++) {
        	printf("Job n°%d\n",i+1);
        	for (j=0;j<3;j++)
			if (jobs[indice][i]->taches[j].job!=-1)
		        	printf("Machine: %d, debut: %d, duree: %d\n",jobs[indice][i]->taches[j].machine,jobs[indice][i]->taches[j].debut,jobs[indice][i]->taches[j].duree);
    	}
}

//Affiche la solution indice, en fonction des machines, de la population actuelle (jobs)
void affiche_machine(int indice){
	int i,j;
	for (i=0;i<3;i++){
		printf("Machine n°%d\n",i+1);
		for (j=0;j<nb_jobs;j++)
			if (jobs[indice][j]->taches[i].job!=-1)
				printf("Job: %d, debut: %d, duree: %d\n",jobs[indice][j]->taches[i].job,jobs[indice][j]->taches[i].debut,jobs[indice][j]->taches[i].duree);
	}
}

//Affiche la solution indice, en fonction des machines, de la population actuelle (jobs) sous format ascii
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


//Tri les taches de la solution indice et renvoie un tableau de taches triées
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

//Tri les taches de la solution indice et renvoie un tableau de taches triées
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

//Remet les debuts de toutes les taches de la solution indice, de la population actuelle (jobs), à -1
void raz_debut_jobs(int indice){
	int i,j;
    	for (i=0;i<nb_jobs;i++)
        	for (j=0;j<3;j++)
			jobs[indice][i]->taches[j].debut=-1;
}

//Remet les debuts de toutes les taches de la solution indice, de la nouvelle génération (next_gen), à -1
void raz_debut_next(int indice){
	int i,j;
    	for (i=0;i<nb_jobs;i++)
        	for (j=0;j<3;j++)
			next_gen[indice][i]->taches[j].debut=-1;
}

//Met les taches dans l'ordre croissant de leur durée dans la solution indice
void trouve_solution_croissante(int indice){
    	Tache *t = tri_croissant(indice);
	raz_debut_jobs(indice);
    	int i;

    	for (i=0; i < nb_taches; i++)
		put_tache(t[i],indice);
}

//Met les taches dans l'ordre décroissant de leur durée dans la solution indice
void trouve_solution_decroissante(int indice){
    	Tache *t = tri_decroissant(indice);
    	int i;
	raz_debut_jobs(indice);
    	for (i=0; i < nb_taches; i++)
		put_tache(t[i],indice);
    	
}

//Met une tache t le plus tôt possible dans la solution indice de la population actuelle
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
	//Met la tache
	jobs[indice][t.job-1]->taches[t.machine-1].debut=start;

}

//Met une tache t le plus tôt possible dans la solution indice de la nouvelle génération
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

/*Most Work Remaining
* Met les taches dans l'ordre suivant :
*	Choisit le job qui lui reste le plus de durée cumulé à placer
*	Choisit la tache qui a la plus grosse durée de ce job et la positionne
*	Recommence jusqu'à épuisement des taches
*/	
void most_work_remaining(int indice){
	Tache *t = tri_mwr(indice);
    	int i;
	raz_debut_jobs(indice);
	
	for (i=0;i<nb_taches;i++)
		put_tache(t[i],indice);
		
}

//Met les taches dans un ordre aléatoire
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

//Renvoie la place-ieme tache la plus grosse du job job de la solution indice
int tache_max(int job, int place, int indice){
	int classement[3];
	//Trie des taches
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

//Tri les taches dans l'ordre pour le Most Work Remaining
Tache * tri_mwr(int indice){
	Tache *taches = malloc(nb_taches*sizeof(Tache));
	int duree_jobs[nb_jobs];
	int i,j;
	int current_job,current_machine;	
	int cpt_jobs[nb_jobs];

	//Calcul la durée total de chaque job
	for (i=0;i<nb_jobs;i++){
		duree_jobs[i]=0;
		for (j=0;j<3;j++)
			if (jobs[indice][i]->taches[j].duree!=-1)
				duree_jobs[i]+=jobs[indice][i]->taches[j].duree;
	}
	//Init du compteur
	for (i=0;i<nb_jobs;i++)
		cpt_jobs[i]=0;

	//Trie les taches dans l'ordre voulu
	for (i=0;i<nb_taches;i++){
		current_job=0;
		//Cherche le job qui a la plus grosse durée restante
		for (j=1;j<nb_jobs;j++)
			if (duree_jobs[current_job]<duree_jobs[j])
				current_job=j;
		//Récupère la tache la plus grosse restante sur ce job	
		current_machine=tache_max(current_job,cpt_jobs[current_job],indice);
		//Incrémente le compteur de ce job
		cpt_jobs[current_job]++;
		//Enleve la durée à la durée totale restante de ce job
		duree_jobs[current_job]-=jobs[indice][current_job]->taches[current_machine].duree;
		//Met la tache de le tableau
		taches[i]=jobs[indice][current_job]->taches[current_machine];
	}

	return taches;
		

}

//Retourne Cmax de la solution indice
int date_fin(int indice){
	int i,j,maxc=0;
	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			maxc = max(maxc,jobs[indice][i]->taches[j].debut+jobs[indice][i]->taches[j].duree);

	return maxc;
}

//Fonction mathématique max
int max(int a, int b){
    return a > b ? a : b;
}

//Fonction mathématique min
int min(int a, int b){
    return a > b ? b : a;
}


/*Fonction de croisement pour AG
*	p1,p2 les indices des deux parents dans la population actuelle
*	enf l'indice de l'enfant dans la nouvelle génération
*
*
*
*/
void croisement (int p1, int p2, int enf){
	//Choisit un parent aléatoirement
	int parent = rand()%2;
	if (parent==1){
		parent=p1;
		p1=p2;
		p2=parent;
	}
	//Choisit une machine aléatoirement
	int m = rand()%3;
	//Choisit le point de coupe aléatoirement sur le parent séléctionné et sur la machine séléctionné
	int ptCoupe = rand()%nb_jobs;
	ptCoupe=jobs[p1][ptCoupe]->taches[m].debut+jobs[p1][ptCoupe]->taches[m].duree;

	Tache *t = malloc(nb_jobs*sizeof(Tache));
	int i,j,k=0;	

	//Recopie les deux machines non séléctionné du parent séléctionné
	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			//Si machine non séléctionnée on recopie
			if (j!=m)
				next_gen[enf][i]->taches[j]=jobs[p1][i]->taches[j];
			else
				//Sinon si avant point de coupe on recopie
				if (jobs[p1][i]->taches[j].debut+jobs[p1][i]->taches[j].duree<=ptCoupe)
					next_gen[enf][i]->taches[j]=jobs[p1][i]->taches[j];
				//Sinon on met la tache dans un tableau
				else{
					t[k]=jobs[p2][i]->taches[j];
					k++;
				}

	

	//Trie des taches pas encore mises dans l'ordre du parent non séléctionné
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
	
	//On met les taches
	for (i=0;i<k;i++)
		put_tache_next(t[i],enf);
			

}


/*Fonction de mutation de AG
*	p l'indice du parent dans la population actuelle
*	enf l'indice de l'enfant dans la nouvelle génération
*/
void mutation(int p, int enf){
	//Séléctionne une machine aléatoirement
	int m = rand()%3;

	int i,j;

	//Recopie les deux machines non séléctionnées
	for (i=0;i<nb_jobs;i++)
		for (j=0;j<3;j++)
			if (j!=m)
				next_gen[enf][i]->taches[j]=jobs[p][i]->taches[j];

	//Remplit aléatoirement la dernière machine
	j=rand()%nb_jobs;
	for (i=0;i<nb_jobs;i++){
		if (jobs[p][j]->taches[m].duree!=-1)
			put_tache_next(jobs[p][j]->taches[m],enf);
		j=(j+1)%nb_jobs;
	}				
				


}

//Calcul la somme de Ci de la solution indice de la population actuelle
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

//Tri la population par ordre croissant de l'objectif (somme des Ci)
void tri_pop(){
	int i,j,tmp;
	int indice[nb_pop];
	int somme[nb_pop];
	//Initialisation
	for (i=0;i<nb_pop;i++){
		//Calcul des objectifs
		somme[i]=calcul_obj(i);
		//Labelisation
		indice[i]=i;
		//Copie temporaire de la population actuelle
		temp[i]=jobs[i];
	}
	//Tri
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
	//Recopie dans la population actuelle
	for (i=0;i<nb_pop;i++)
		jobs[i]=temp[indice[i]];

}

//Fonction de l'algo génétique
void algo_genetique(){
	int i,alea,p1,p2,j=0;

	//Création de la population de base aléatoirement
	for (i=0;i<nb_pop;i++){
		raz_debut_jobs(i);		
		raz_debut_next(i);
		aleatoire(i);
	}
	
	//Nombre de génération
	while(j!=nb_time){
		//Tri de la population par ordre croissant de l'objectif
		tri_pop();
		
		//Pour chaque nouvel enfant
		for (i=0;i<nb_pop;i++)
			//On garde les X premiers de la population
			if (i<nb_pop_keep)
				next_gen[i]=jobs[i];
			else{	
				//80% de chance de faire un croisement
				//15% de faire une mutation
				//5% de faire un clonage
				alea=rand()%100;
				//Si croisement
				if (alea<80){
					//On chosit deux parents avec 50% de chance qu'ils soient dans les 20 premiers pourcent
					//30% qu'ils soient entre 20-70%
					//20% qu'ils soient dans les 30 derniers pourcent 
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
					//On effectue le croisement
					croisement(p1,p2,i);
					
				}
				//Si clonage
				else if (alea>95){
					next_gen[i]=jobs[i];
				}
				//Si mutation
				else{
					//On chosit un parent avec 50% de chance qu'il soit dans les 20 premiers pourcent
					//30% qu'il soit entre 20-70%
					//20% qu'il soit dans les 30 derniers pourcent 
					p1=rand()%100;
					if (p1<50)
						p1=rand()%(int)(0.5*nb_pop);
					else if (p1>80)
						p1=rand()%(int)(0.3*nb_pop)+0.7*nb_pop;
					else
						p1=rand()%(int)(0.2*nb_pop)+0.2*nb_pop;
					//On effectue la mutation
					mutation(p1,i);
				}

			}
		//On recopie la nouvelle génération dans la génération actuelle
		for (i=0;i<nb_pop;i++)
			jobs[i]=next_gen[i];
		
		j++;
	}
	//On trie une dernière fois la population actuelle
	tri_pop();
	
			

}
