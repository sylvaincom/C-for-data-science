//
// Created by julie on 24/01/2020.
//

#ifndef TEST_ALGO_MACHINELEARNING_KNN_H
#define TEST_ALGO_MACHINELEARNING_KNN_H

#include <fstream>
#include <list>
#include <vector>

struct point_features {
    std::vector<double> point;  //Coordonnées
    int classification;         //Classe d'appartenance
    double dist;                //Distance au point testé
};

class KNN {
    //Liste des points
    std::list<point_features> dataset;

public:
    double distance(std::vector<double> &, std::vector<double> &);
    int Algo_Knearest(std::vector<double> &, int);
    void import_points(std::list<std::vector<double>> &, std::list<int> &,std::vector<double> &);
    KNN(std::ifstream &, char,std::vector<double>);
};


#endif //TEST_ALGO_MACHINELEARNING_KNN_H
