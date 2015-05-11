#include "openshop.h"

int main(){  
	srand(time(NULL));
	//Nombre de jobs
	nb_jobs = 4;
	//Nombre de taches total
	nb_taches = 9;
	//Nombre de solutions dans la population pour AG
	nb_pop=100;
	//Nombre de solution que l'on garde à chaque génération
	nb_pop_keep=0.05*nb_pop;
	//Nombre de génération
	nb_time=100;

	//Instance 1 
	Tache taches[9];
	taches[0] = nouvelle_tache(1,1,6);
	taches[1] = nouvelle_tache(3,1,2);
	taches[2] = nouvelle_tache(2,2,1);
	taches[3] = nouvelle_tache(3,2,5);
	taches[4] = nouvelle_tache(1,2,3);
	taches[5] = nouvelle_tache(1,3,4);
	taches[6] = nouvelle_tache(1,4,7);
	taches[7] = nouvelle_tache(2,4,1);
	taches[8] = nouvelle_tache(3,4,8);

	//Instances 2
	Tache t2[14];
	t2[0] = nouvelle_tache(1,1,4);
	t2[1] = nouvelle_tache(2,1,2);
	t2[2] = nouvelle_tache(3,1,7);
	t2[3] = nouvelle_tache(1,2,1);
	t2[4] = nouvelle_tache(2,2,8);
	t2[5] = nouvelle_tache(3,2,6);
	t2[6] = nouvelle_tache(1,3,12);
	t2[7] = nouvelle_tache(1,4,3);
	t2[8] = nouvelle_tache(2,4,9);
	t2[9] = nouvelle_tache(2,5,7);
	t2[10] = nouvelle_tache(3,5,3);
	t2[11] = nouvelle_tache(1,6,4);
	t2[12] = nouvelle_tache(2,6,1);
	t2[13] = nouvelle_tache(3,6,11);

	//Instances 3
	Tache t3[7];
	t3[0] = nouvelle_tache(1,1,2);
	t3[1] = nouvelle_tache(2,1,5);
	t3[2] = nouvelle_tache(3,1,4);
	t3[3] = nouvelle_tache(1,2,3);
	t3[4] = nouvelle_tache(2,2,9);
	t3[5] = nouvelle_tache(3,2,2);
	t3[6] = nouvelle_tache(1,3,10);	
	
	//Initialise la population temporaire
	//temp = nouvelle_pop(taches);

	//Initialise la population présente
	//jobs = nouvelle_pop(taches);
	
	//Initialise la nouvelle génération
	//next_gen = nouvelle_pop(taches);

	int i=1;
	int test=0;
	while(i!=0){
		test=0;
		printf("\n\n\n\n--Choisir votre instance--\n");
		printf("1. Instance 1\n");
		printf("2. Instance 2\n");
		printf("3. Instance 3\n");
		printf("0. Quitter\n");
		scanf("%d",&i);
		if (i==1) {
			test=1;
			nb_jobs = 4;
			nb_taches = 9;
			temp = nouvelle_pop(taches);
			jobs = nouvelle_pop(taches);
			next_gen = nouvelle_pop(taches);
		}
		else if (i==2){
			test=1;
			nb_jobs = 6;
			nb_taches = 14;
			temp = nouvelle_pop(t2);
			jobs = nouvelle_pop(t2);
			next_gen = nouvelle_pop(t2);
		}
		else if (i==3){
			test=1;
			nb_jobs = 3;
			nb_taches = 7;
			temp = nouvelle_pop(t3);
			jobs = nouvelle_pop(t3);
			next_gen = nouvelle_pop(t3);
		}
		else
			test=0;
		if (test==1){
			system("clear");
			printf("--Choisir l'affichage--\n");
			printf("1. Ordonnancement par tri croissant des durées des taches\n");
			printf("2. Ordonnancement par tri décroissant des durées des taches\n");
			printf("3. Ordonnancement par tri décroissant des taches qui appartiennent au job qui a la plus grosse durée restante\n");
			printf("4. Ordonnancement aléatoire\n");
			printf("5. Algo Génétique\n");
			printf("6. Tout\n");
			printf("0. Quitter\n");
			scanf("%d",&i);
			system("clear");
			if (i==5){
				algo_genetique();	
				printf("Algo génétique\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}
			else if (i==1){
				trouve_solution_croissante(0);
				printf("Tri croissant\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}
			else if (i==2){
				trouve_solution_decroissante(0);
				printf("Tri décroissant\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}
			else if (i==3){
				heuristique_bizarre(0);
				printf("3eme heuristique\n\n");
				printf("Somme des Ci: %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}
			else if (i==4){
				aleatoire(0);
				printf("Aléatoire\n\n");
				printf("Somme des Ci: %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}
			else if (i>5){
				algo_genetique();	
				printf("Algo génétique\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
				trouve_solution_croissante(0);
				printf("\n\nTri croissant\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
				trouve_solution_decroissante(0);
				printf("\n\nTri décroissant\n\n");
				printf("Somme des Ci : %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
				heuristique_bizarre(0);
				printf("\n\n3eme heuristique\n\n");
				printf("Somme des Ci: %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
				aleatoire(0);
				printf("\n\nAléatoire\n\n");
				printf("Somme des Ci: %d\n\n",calcul_obj(0));
				affichage_machine_ASCII(0);
			}

		}

		

	}

    return 0;

}
