#include <iostream>
#include <time.h>
#include <fstream>
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
    i.execute();
    cout << i.result();//result()

  }
  else if(choixSaisie==2){
    string strInstance;
    cout << "Veuillez saisir l'instance au clavier:"<<endl;
    cin >> strInstance;
    i.createFromString(strInstance);
    i.execute();
    cout << i.result();//result()
  }
  else{
    //Initialisation
    int m, n, k, min, max;
    string filename;
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
    cout << "Veuillez entrez le nom du fichier de sortie:"<<endl;
    cin >> filename;

    for(int i=0;i<k;i++) {
      Instance ins;
      ins.createRandom(m,n,min,max);
      instances.push_back(ins);
    }

    //résolution et affichage
    string res = "";
    float sum_ri_LPT, sum_ri_LSA, sum_ri_Perso;
    for(int i=0;i<instances.size();i++) {
      float mi;
      float ri_LPT, ri_LSA, ri_Perso;
      instances[i].execute();

      mi = std::max((float) instances[i].getBorneInfMax(), instances[i].getBoneInfMoy());
      ri_LPT = instances[i].getResLPT() / mi;
      sum_ri_LPT += ri_LPT;
      ri_LSA = instances[i].getResLSA() / mi;
      sum_ri_LSA += ri_LSA;
      ri_Perso = instances[i].getResPerso() / mi;
      sum_ri_Perso += ri_Perso;
      res += "================================\n";
      res += instances[i].result();
    }

    res += "================================\n";
    res += "ratio d'approximation moyen LSA : " + to_string(sum_ri_LSA/k) + "\n";
    res += "ratio d'approximation moyen LPT : " + to_string(sum_ri_LPT/k) + "\n";
    res += "ratio d'approximation moyen Perso : " + to_string(sum_ri_Perso/k) + "\n";
    cout << res << endl;
    ofstream write(filename.c_str());
    write << res;
    write.close();
  }

  return 0;
}
