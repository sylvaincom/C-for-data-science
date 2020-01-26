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

void kmeans_set::print_centroids(std::ostream & output, char delimiter) {
    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        if (i != clusters.begin()) {
            output << "\n";
        }
        print_point(output, i->centroid, delimiter);
    }
}

void kmeans_set::import_points(std::list<std::vector<double>> & list_point) {
    for (auto j = list_point.begin(); j != list_point.end(); j++) {
        point_features new_point;
        new_point.point = *j;
        if (dataset.empty()) {
            dataset.push_back(new_point);
        }
        //On trie les points lors de l'insertion, pour que les centroides soient équirépartis par la suite
        else if (dataset.front().point.size() == j->size()) {
            auto i = dataset.begin();
            while(i != dataset.end() && (i-> point < *j)) {
                i++;
            }
            dataset.insert(i,new_point);
        }
    }
}

//Pour un fichier importé
/*kmeans_set::kmeans_set(std::ifstream & input_file, char delimiter):
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
}*/

//Réaffectation des centroides et calcul du mouvement maximal parmi les centroides
double kmeans_set::recompute_centroids() {

    std::list<std::vector<double>> old_centroids;
    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        old_centroids.push_back(i->centroid);
    }

    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        std::fill(i->centroid.begin(), i->centroid.end(), 0);
    }

    //Si il n'y a pas eu de mouvement, on laisse le centroide tel qu'il est
    auto j_old = old_centroids.begin();
    for (auto i = clusters.begin(); i != clusters.end(); i++, j_old++) {
        if (!(i->move_flag)) {
            i->centroid = *j_old;
        }
    }

    //On actualise la position des centroides
    for (auto data = dataset.begin(); data != dataset.end(); data++) {
        if (data->centroid_pointer->move_flag) {
            auto centroid_pointer_centroid_iter = data->centroid_pointer->centroid.begin();
            for (auto coord = data->point.begin(); coord != data->point.end(); coord++, centroid_pointer_centroid_iter++) {
                //On actualise le centroide en l'affectant à la moyenne des autres points
                *centroid_pointer_centroid_iter += *coord / data->centroid_pointer->count;
            }
        }
    }

    // Calcul du delta maximal
    double delta = 0;
    auto old_centroids_iter = old_centroids.begin();
    for (auto i = clusters.begin(); i != clusters.end(); i++) {
        double test_delta = distance(*old_centroids_iter, i->centroid);
        if (delta < test_delta) {delta = test_delta; }
    }
    return delta;
}


//Distribution des centroides
void kmeans_set::algo_kmeans(int k) {
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
            std::cout << "\n\nIteration " << iteration_index++ << "   Nombre de clusters: " << clusters.size();
            unsigned int cluster_number = 0;
            for (auto cluster_iter = clusters.begin(); cluster_iter != clusters.end(); ++cluster_iter) {
                std::cout << "\n"  << "Cluster stable: " << ((cluster_iter->move_flag)?("Non    "):("  Oui    ")) << cluster_number << ": ";
                print_point(std::cout, cluster_iter->centroid, ',');
                std::cout << "   Nombre de points: " << cluster_iter->count;
            }
        }
    }
}
