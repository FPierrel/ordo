#include "openshop.h"

int main(){
    Tache taches[9];
    nb_jobs = 4;
    nb_taches = 9;

    taches[0] = nouvelle_tache(1,1,6);
    taches[1] = nouvelle_tache(3,1,2);
    taches[2] = nouvelle_tache(2,2,1);
    taches[3] = nouvelle_tache(3,2,5);
    taches[4] = nouvelle_tache(1,2,3);
    taches[5] = nouvelle_tache(1,3,4);
    taches[6] = nouvelle_tache(1,4,7);
    taches[7] = nouvelle_tache(2,4,1);
    taches[8] = nouvelle_tache(3,4,8);

    jobs = nouveaux_jobs(taches);

    //trouve_solution_croissante();
    

trouve_solution_croissante();
affichage_machine_ASCII();
affiche_machine();

    return 0;

}
