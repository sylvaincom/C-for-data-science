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
    //Nombre de points
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

    kmeans_set(std::ifstream &, char);                // Import points from file with specified delimiter
    kmeans_set(std::list<std::vector<double>> &);   // Import points from vector on construction

    void compute_centroids(int);
    void print_centroids(std::ostream &, char);       // output stream, centroid delimiter
    void print_clusters(std::ostream &, char, char);  // output stream, point delimiter, centroid designator
};


#endif //TEST_ALGO_MACHINELEARNING_KMEANS_H


