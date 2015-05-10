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

	//Instance
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

	//Initialise la population temporaire
	temp = nouvelle_pop(taches);
	//Initialise la population présente
	jobs = nouvelle_pop(taches);
	//Initialise la nouvelle génération
	next_gen = nouvelle_pop(taches);


	//Lancement de AG
	algo_genetique();
	//Affichage de la somme de Ci de la meilleure solution trouvé par l'AG
	printf("\nAlgo génétique\n");
	printf("Somme : %d\n",calcul_obj(0));
	affichage_machine_ASCII(0);
	//Tri croissant
	trouve_solution_croissante(0);
	printf("\nTri croissant\n");
	printf("Somme : %d\n",calcul_obj(0));
	affichage_machine_ASCII(0);
	//Tri décroissant
	trouve_solution_decroissante(0);
	printf("\nTri décroissant\n");
	printf("Somme : %d\n",calcul_obj(0));
	affichage_machine_ASCII(0);
	//Met la tache avec la plus grosse durée du job auquel il reste le plus de durée non placée
	heuristique_bizarre(0);
	printf("\n3eme heuristique\n");
	printf("Somme : %d\n",calcul_obj(0));
	affichage_machine_ASCII(0);


//croisement(taches,jobs[0],jobs[1]);
//mutation(taches, jobs[0]);
    return 0;

}
