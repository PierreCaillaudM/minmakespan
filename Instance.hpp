#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>
#include <fstream>

class Instance{
    int _nbM;
    std::vector<int> _m;
    int _n;
    std::vector<int> _d;

    int borne_inf_max;
    float borne_inf_moy;
    float res_LSA;
    float res_LPT;
    float res_Perso;

    public:
        Instance();
        void createFromFile(std::string path);
        void createFromString(std::string str);
        void execute();
        void executeLSA();

        int premiereMachineDispo();
        void print();
        void printMachines();
    private:
        std::vector<int> explode(std::string const & s, char delim);
};

#endif
