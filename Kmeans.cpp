//
// Created by julie on 24/01/2020.
//

#include "Kmeans.h"
#include <cstdlib>
#include <limits>
#include <sstream>
#include <cmath>
#include <iostream>

//Première fonction pour calculer la distance entre 2 points
double kmeans_set::distance(std::vector<double> & x1, std::vector<double> & x2) {
    auto coord2 = x2.begin();
    double dist = 0;
    for (auto coord1 = x1.begin(); coord1 != x1.end(); ++coord1, ++coord2) {
        dist += (*coord1 - *coord2) * (*coord1 - *coord2);
    }
    return std::sqrt(dist);
}

//Fonction pour vérifier si des points ont changé de cluster (une des conditions d'arrêt)
bool kmeans_set::movement() {
    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        //Si il y a eu du mouvement dans au moins un des clusters --> on retourne VRAI
        if (i->move_flag) {
            return true;
        }
    }
    return false;
}

void kmeans_set::nearest_cluster() {
    for (auto data = dataset.begin(); data != dataset.end(); data++) {
        for (auto cluster = clusters.begin(); cluster != clusters.end(); cluster++) {
            //Si on trouve un centroide plus proche que celui auquel le point est déjà affecté --> on déplace le point
            if (distance(data->point, cluster->centroid) < distance(data->point, data->centroid_pointer->centroid)) {

                //On retire ce point de l'ancien cluster
                --data->centroid_pointer->count;

                //Il y a un mouvement dans l'ancien cluster
                data->centroid_pointer->move_flag = true;    //

                //On affecte au point un nouveau cluster
                data->centroid_pointer = &(*cluster);
                ++data->centroid_pointer->count;

                //Il y a un mouvement dans le nouveau cluster
                data->centroid_pointer->move_flag = true;
            }
        }
    }
}

void kmeans_set::print_point(std::ostream & output, std::vector<double> vec, char delim) {
    for(auto i = vec.begin(); i != vec.end(); i++) {
        if(i != vec.begin()) { output << delim; }
        output << *i;
    }
}


void kmeans_set::import_points(std::list<std::vector<double>> & list_point) {
    for (auto j = list_point.begin(); j != list_point.end(); j++) {
        point_features new_point;
        new_point.point = *j;
        if (dataset.empty()) {
            dataset.push_back(new_point);
        }
        else if (dataset.front().point.size() == j->size()) {
            // Assures dimensional integrity
            // Sorting on intake assures well-dispursed centroid selection
            // Well-dispursed centroid selection helps mitigate centroids "fighting" over points
            auto i = dataset.begin();
            while(i != dataset.end() && (i-> point < *j)) {   // PRECEDENCE MATTERS!!
                // Sorts points on insert - this ensures evenly distributed centroid picking
                i++;
            }
            dataset.insert(i,new_point);
        }
    }
}

/*kmeans_set::kmeans_set():
nb_points(20),
epsilon(0),
hard_limit(std::numeric_limits<unsigned int>::max())
{
    std::list<std::vector<double>> point_list;
    for (auto i =0;i < nb_points;i++){
        auto x = rand()%(10);
        auto y = rand()%(10);
        std::vector<double> temp_point;
        temp_point.push_back(x);
        temp_point.push_back(y);
        point_list.push_back(temp_point);
    }
    import_points(point_list);
}*/


// Import points from file with specified delimiter into a temporary list - calls import_points()
kmeans_set::kmeans_set(std::ifstream & input_file, char delimiter):
        epsilon(0),
        limit(std::numeric_limits<unsigned int>::max()) {
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
    import_points(temp_point_list);
}


// Import points from list on construction
kmeans_set::kmeans_set(std::list<std::vector<double>> & point_list):
        epsilon(0),
        limit(std::numeric_limits<unsigned int>::max()) {
    import_points(point_list);
}

//Distribution des centroides
void kmeans_set::compute_centroids(int k) {
    //Pour avoir des centroides équirépartis
    {   unsigned int subset = dataset.size() / k;
        unsigned int rem = dataset.size() % k;
        unsigned int i = 0;
        for (auto centroid_pick_iter = dataset.begin(); centroid_pick_iter != dataset.end(); centroid_pick_iter++, i--) {
            if (i == 0) {
                cluster new_cluster;
                new_cluster.centroid = centroid_pick_iter->point;
                clusters.push_back(new_cluster);
                i = subset + (rem ? 1 : 0);
                if (rem) { rem--; }
            }
            centroid_pick_iter->centroid_pointer = & clusters.back();
            ++centroid_pick_iter->centroid_pointer->count;
        }
    }
    unsigned int max = limit;
    double delta_max_1 = std::numeric_limits<double>::max();
    double delta_max_2 = 0;

    unsigned int iteration_index = 0;
    recompute_centroids();

    //On utilise fabs car abs ne marche qu'avec les entiers
    //Tant que les 3 conditions suivantes sont remplies, on itère
    while ((fabs(delta_max_2 - delta_max_1) > fabs(epsilon)) && max && movement()) {
        max--;
        delta_max_2 = delta_max_1;

        for(auto i = clusters.begin(); i != clusters.end(); i++) {
            i->move_flag = false;
        }
        //On affecte tous les points au cluster le plus proche
        nearest_cluster();

        //Retourne le mouvement le plus important
        delta_max_1 = recompute_centroids();

        {
            std::cout << "\n\nItération " << iteration_index++ << "   Nombre de clusters: " << clusters.size();
            unsigned int ct = 0;
            for (auto cluster_iter = clusters.begin(); cluster_iter != clusters.end(); ++cluster_iter) {
                std::cout << "\n"  << "Move State: " << ((cluster_iter->move_flag)?("INVALID    "):("  valid    ")) << ++ct << ": ";
                print_point(std::cout, cluster_iter->centroid, ',');
                std::cout << "   Nombre de points: " << cluster_iter->count << "   Address: " << &(*cluster_iter);
            }
        }
    }
}



double kmeans_set::recompute_centroids() {


    std::list<std::vector<double>> old_centroids;
    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        old_centroids.push_back(i->centroid);
    }

    for (auto cluster_iter = clusters.begin(); cluster_iter != clusters.end(); cluster_iter++) {
        std::fill(cluster_iter->centroid.begin(), cluster_iter->centroid.end(), 0);
    }
    auto old_centroid_iter = old_centroids.begin();
    for (auto cluster_iter = clusters.begin(); cluster_iter != clusters.end(); ++cluster_iter, ++old_centroid_iter) {
        if (!(cluster_iter->move_flag)) {
            cluster_iter->centroid = *old_centroid_iter;
        }
    }

    //On actualise la position des centroides
    for (auto universe_iter = dataset.begin(); universe_iter != dataset.end(); universe_iter++) {
        if (universe_iter->centroid_pointer->move_flag) {
            auto centroid_pointer_centroid_iter = universe_iter->centroid_pointer->centroid.begin();
            for (auto point_iter = universe_iter->point.begin(); point_iter != universe_iter->point.end(); ++point_iter, ++centroid_pointer_centroid_iter) {
                // Division on the fly useful for accuracy super-large dimensions - doubles computation
                *centroid_pointer_centroid_iter += *point_iter / universe_iter->centroid_pointer->count;
            }
        }
    }

    // Calcul du delta maximal
    double max_delta = 0;
    auto old_centroids_iter = old_centroids.begin();
    for (auto centroids_iter = clusters.begin(); centroids_iter != clusters.end(); centroids_iter++) {
        double test_delta = distance(*old_centroids_iter, centroids_iter->centroid);
        if (max_delta < test_delta) { max_delta = test_delta; }
    }
    return max_delta;
}



void kmeans_set::print_centroids(std::ostream & output, char delimiter) {
    for(auto cluster_iter = clusters.begin(); cluster_iter != clusters.end(); cluster_iter++) {
        for (auto centroid_iter = cluster_iter->centroid.begin(); centroid_iter != cluster_iter->centroid.end(); ++centroid_iter) {
            if(cluster_iter != clusters.begin() && centroid_iter == cluster_iter->centroid.begin()) {
                output << "\n";
            } else if(centroid_iter != cluster_iter->centroid.begin()) {
                output << delimiter;
            }
            output << *centroid_iter;
        }
    }
}



