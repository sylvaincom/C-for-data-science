#include <iostream>
#include "Kmeans.h"

int main() {

    std::ostream &output_console = std::cout;

    //Pour un fichier choisi dans
    /*std::ifstream input;
    input.open("C:/Users/julie/Desktop/test_points.txt");   //à adapter en fonction du répertoire
    kmeans_set km(input, ',');*/

    //Pour une génération de points aléatoire
    kmeans_set kmeans_set(20);

    kmeans_set.algo_kmeans(4);
    std::cout << "\n\nOutput in main():\n";
    kmeans_set.print_centroids(output_console, ',');
    return 0;

}
