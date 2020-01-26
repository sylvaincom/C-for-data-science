//
// Created by julie on 24/01/2020.
//
#ifndef TEST_ALGO_MACHINELEARNING_KMEANS_H
#define TEST_ALGO_MACHINELEARNING_KMEANS_H

#include <fstream>
#include <list>
#include <vector>


//On crée la structure d'un cluster
struct cluster{
    std::vector<double> centroid;            //Un cluster est défini par un centroide
    unsigned int count;                      //Le nombre de points qu'il contient
    bool move_flag;                          //Pour vérifier si le cluster a évolué (mouvements de points)
    cluster() : count(0), move_flag(1) {}    //Nombre de points dans le cluster et indication du mouvement
};

//Structure d'un point
struct point_features {
    std::vector<double> point;                        //Coordonnées
    cluster * centroid_pointer;                       //Centroide associé, référence à la structure cluster
    point_features() : centroid_pointer(nullptr) {}
};

class kmeans_set {
    //Nombre de points, utile pour des points générés aléatoirement
    int nb_points;

    // Limite du nombre d'itérations
    unsigned int limit;

    //Liste des points
    std::list<point_features> dataset;

    // Liste des clusters
    std::list<cluster> clusters;

    //Niveau d'erreur
    double epsilon;

    //Distance entre 2 points
    double distance(std::vector<double> &, std::vector<double> &);
    bool movement();
    void nearest_cluster();
    void import_points(std::list<std::vector<double>> &);

    //Pour affecter les points au cluster le plus proche

    double recompute_centroids();

    void print_point(std::ostream &, std::vector<double>, char);

public:
    //1er type : Avec des points tirés aléatoirement
    kmeans_set(int a):
            nb_points(30),
            epsilon(0),
            limit(1000)
    {
        std::list<std::vector<double>> point_list;
        for (auto i =0;i < nb_points;i++){
            //Points tirés aléatoirement entre 0 et a
            auto x = rand()%(a);
            auto y = rand()%(a);
            std::vector<double> temp_point;
            temp_point.push_back(x);
            temp_point.push_back(y);
            point_list.push_back(temp_point);
        }
        import_points(point_list);
    }

    //2ème type : Avec des points provenant d'un fichier externe
    /*kmeans_set(std::ifstream &, char);
    kmeans_set(std::list<std::vector<double>> &);*/

    void algo_kmeans(int);
    void print_centroids(std::ostream &, char);
};


#endif //TEST_ALGO_MACHINELEARNING_KMEANS_H
