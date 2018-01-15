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
    vector<int> rep = explode(str, ':');
    _nbM = rep[0];
    _n = rep[1];
    _d = std::vector<int>(_n);
    for(int i=0;i<_n;i++){
        _d[i] = rep[i+2];
    }
}

void Instance::createRandom(int m, int n, int min, int max){
   _nbM = m;
   _n = n;
   _d = std::vector<int>(_n);
   for(int i=0;i<_n;i++){
      _d[i] = min + (rand() % static_cast<int>(max - min + 1));
   }
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

void Instance::print(){
    cout <<"m: "<<_nbM<<endl<<"n: "<<_n<<endl;
    for(int i=0;i<_n;i++){
        cout<<"d"<<i+1<<"["<<_d[i]<<"]";
    }
    cout<<endl;
}
void Instance::printMachines(){
    for(int i=0;i<_nbM;i++){
        cout<<"m"<<i+1<<"["<<_m[i]<<"]";
    }
    cout<<endl;
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
