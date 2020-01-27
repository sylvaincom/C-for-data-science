//
// Created by julie on 24/01/2020.
//

#include "KNN.h"
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

double KNN::distance(std::vector<double> & x1, std::vector<double> & x2) {
    auto coord2 = x2.begin();
    double dist = 0;
    for (auto coord1 = x1.begin(); coord1 != x1.end(); ++coord1, ++coord2) {
        dist += (*coord1 - *coord2) * (*coord1 - *coord2);
    }
    return std::sqrt(dist);
}

//Algorithme principal
int KNN::Algo_Knearest(std::vector<double> & p,int k){

    //Création d'une liste distance_class contenant les distances au point p ainsi que les classes des points correspondants
    std::list<std::vector<double>> distance_class;
    for (auto i = dataset.begin();i != dataset.end();i++){
        std::vector<double> temp_vec;
        if (distance_class.empty()){
            temp_vec.push_back(i->dist);
            temp_vec.push_back(i->classification);
            distance_class.push_back(temp_vec);
        }
        else {
            auto j = dataset.begin();
            while(j-> dist > i->dist) {
                j++;
            }
            temp_vec.push_back(j->dist);
            temp_vec.push_back(j->classification);
            distance_class.push_back(temp_vec);
        }
    }
    int count0 = 0;
    int count1 = 0;
    int max = 0;
    //On regarde quel est le nombre de points classés 0/1 parmi les K plus proches voisins
    for (auto i = distance_class.begin(); i != distance_class.end();i++){
        std::vector<double> temp = *i;
        if (temp.back() == 0){count0++;
        }
        else {
            count1++;
        }
        max++;
        if (max == k){
            return(count0 > count1 ? 0 : 1);}
}
}

//Pour importer les points ainsi que leurs caractéristiques à partir d'une liste de points
void KNN::import_points(std::list<std::vector<double>> & list_point,std::list<int> & class_belong,std::vector<double> & p) {
    auto i = class_belong.begin();
    for (auto j = list_point.begin(); j != list_point.end(); j++,i++) {
        point_features new_point;
        new_point.point = *j;
        new_point.classification = *i;
        new_point.dist = distance(*j,p);
        dataset.push_back(new_point);
        }
}

//Constructeur à partir du fichier importé contenant les coordonnées ainsi que les classes d'appartenance
KNN::KNN(std::ifstream & input_file, char delimiter,std::vector<double> p)
{
    std::string line;
    std::list<std::vector<double>> temp_point_list;
    while (std::getline(input_file, line)) {
        while ((line.length() == 0) && !(input_file.eof())) {
            std::getline(input_file, line);
        }
        std::string parameter;
        std::stringstream ss(line);
        std::vector<double> temp_point;
        if ((line.length() != 0)) {
            while (std::getline(ss, parameter, delimiter)) {
                temp_point.push_back(atof(parameter.c_str()));
            }
            temp_point_list.push_back(temp_point);

        }
    }
    std::list<std::vector<double>> coord;
    std::list<int> classification;
    for (auto i = temp_point_list.begin();i != temp_point_list.end();i++){
        std::vector<double> content = *i;
        std::vector<double> coords_1_2;
        coords_1_2.push_back(content.at(0));
        coords_1_2.push_back(content.at(1));
        coord.push_back(coords_1_2);
        classification.push_back(content.at(2));
    }
    import_points(temp_point_list,classification,p);
}