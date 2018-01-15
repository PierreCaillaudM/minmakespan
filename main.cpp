#include <iostream>
#include "Instance.hpp"

using namespace std;

int main (int argc, char *argv[]) {
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

    return 0;
}
