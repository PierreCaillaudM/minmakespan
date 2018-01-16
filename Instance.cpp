#include "Instance.hpp"

using namespace std;

Instance::Instance(){

}

void Instance::createFromFile(string path){
    ifstream fichier(path.c_str(), ios::in);  // on ouvre en lecture
    string contenu;
    if(fichier)
    {
        while(getline(fichier, contenu)){
            createFromString(contenu);
        }
    }
    else{
        cerr << "Impossible d'ouvrir le fichier" << endl;
    }
    fichier.close();
}

void Instance::createFromString(string str){
    // Creation de l'instance
    vector<int> rep = explode(str, ':');
    _nbM = rep[0];
    _n = rep[1];
    _d = std::vector<int>(_n);
    for(int i=0;i<_n;i++){
        _d[i] = rep[i+2];
    }
    calculBornes();
}

void Instance::createRandom(int m, int n, int min, int max){
   _nbM = m;
   _n = n;
   _d = std::vector<int>(_n);
   for(int i=0;i<_n;i++){
      _d[i] = min + (rand() % static_cast<int>(max - min + 1));
   }
   calculBornes();
}

void Instance::calculBornes(){
  //Calcul de borne inf max
  borne_inf_max = 0;
  for(int i=0;i<_n;i++){
      if(_d[i]>borne_inf_max){
          borne_inf_max = _d[i];
      }
  }
  //Calcul de borne inf moy
  float sum = 0.0;
  for(int i=0;i<_n;i++){
      sum+=_d[i];
  }
  borne_inf_moy = sum/_nbM;
}

void Instance::execute(){
    executeLSA();
    executeLPT();
}

void Instance::executeLSA(){
    //Initialisation
    int t = 0;
    _m = std::vector<int>(_nbM);
    for(int i=0; i<_nbM;i++){_m[i]=0;}
    //Execution
    for(int i=0; i<_n;i++){
        _m[premiereMachineDispo()] += _d[i];
    }
    res_LSA = *std::max_element(_m.begin(),_m.end());
}

void Instance::executeLPT(){
   //Initialisation
   _m = std::vector<int>(_nbM);
   //Trier les tâches en ordre décroissant
   std::sort(_d.rbegin(), _d.rend());
   //Assigner les tâches
   for(int i=0; i<_n;i++){
      _m[premiereMachineDispo()] += _d[i];
   }
   res_LPT = *std::max_element(_m.begin(),_m.end());
}

void Instance::executeMyAlgo(){
      //Initialisation
      _m = std::vector<int>(_nbM);
      int moy = std::accumulate(_d.begin(),_d.end(),0) / _nbM;
}

int Instance::premiereMachineDispo(){
    int min = _m[0];
    int indice = 0;
    for(int i=1;i<_nbM;i++){
        if(_m[i]<min){
            min = _m[i];
            indice = i;
        }
    }
    return indice;
}

std::string Instance::result(){
    std::string str;
    str+="Borne inférieure max : "+ std::to_string(borne_inf_max)+"\n";
    str+="Borne inférieure moy : "+ std::to_string(borne_inf_moy)+"\n";
    str+="LSA : " + std::to_string(res_LSA) + "\n";
    str+="LPT : " + std::to_string(res_LPT) + "\n";

    return str;
}

int Instance::getBorneInfMax(){
  return borne_inf_max;
}
float Instance::getBoneInfMoy(){
  return borne_inf_moy;
}
float Instance::getResLSA(){
  return res_LSA;
}
float Instance::getResLPT(){
  return res_LPT;
}
float Instance::getResPerso(){
  return res_Perso;
}
std::vector<int> Instance::explode(std::string const & str, char delim){
    std::vector<int> result;
    string strBuff;
    for(int i=0; i<str.size(); i++){
        if(str[i]==delim){
            result.push_back(std::stoi(strBuff));
            strBuff="";
        }else{
            strBuff += str[i];
        }
    }
    result.push_back(std::stoi(strBuff));
    return result;
}
