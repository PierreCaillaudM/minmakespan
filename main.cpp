#include <iostream>
#include <time.h>
#include "Instance.hpp"

using namespace std;

int main (int argc, char *argv[]) {
   srand(time(NULL));
    int choixSaisie = 0;

    cout << "Mode de saisie ?" << endl << "  1.Fichier" << endl << "  2.Clavier" << endl << "  3.Generation aleatoire" << endl << "Reponse:";
    cin >> choixSaisie;

    Instance i;

    if(choixSaisie==1){
        string strPath;
        cout << "Veuillez saisir le chemin vers le fichier:"<<endl;
        cin >> strPath;
        i.createFromFile(strPath);

        i.print();

        i.execute();

        i.printMachines();
        
    }
    else if(choixSaisie==2){
        string strInstance;
        cout << "Veuillez saisir l'instance au clavier:"<<endl;
        cin >> strInstance;
        i.createFromString(strInstance);

        i.print();
    }
    else{
      //Initialisation
      int m, n, k, min, max;
      vector<Instance> instances = vector<Instance>();
      cout << "Veuillez saisir le nombre de machines:"<<endl;
      cin >> m;
      cout << "Veuillez saisir le nombre de taches:"<<endl;
      cin >> n;
      cout << "Veuillez saisir le nombre d'instances:"<<endl;
      cin >> k;
      cout << "Veuillez saisir le minimum pour les taches:"<<endl;
      cin >> min;
      cout << "Veuillez saisir le maximum pour les taches:"<<endl;
      cin >> max;
      for(int i=0;i<k;i++) {
         Instance ins;
         ins.createRandom(m,n,min,max);
         instances.push_back(ins);
      }

      //résolution et affichage
      for(int i=0;i<instances.size();i++) {
         instances[i].print();
         instances[i].execute();
         instances[i].printMachines();
      }

   }

    return 0;
}
