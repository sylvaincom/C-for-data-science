#include <iostream>
//#include "Kmeans.h"
#include "KNN.h"

/*int main() {

    std::ostream &output_console = std::cout;

    //Pour un fichier choisi
    std::ifstream input;
    input.open("C:/Users/julie/Desktop/test_points.txt");   //à adapter en fonction du répertoire
    kmeans_set km(input, ',');

    //Pour une génération de points aléatoire
    kmeans_set kmeans_set(20);

    kmeans_set.algo_kmeans(4);
    std::cout << "\n\nOutput in main():\n";
    kmeans_set.print_centroids(output_console, ',');
    return 0;

}*/

int main(){
    std::ostream &output_console = std::cout;
    std::ifstream input;
    input.open("C:/Users/julie/Desktop/Point_KNN.txt");   //à adapter en fonction du répertoire
    std::vector<double> p (2,2);
    p.push_back(7);
    KNN KNN(input, ',',p);
    std::cout << "Point appartenant à la classe ";
    std::cout<<KNN.Algo_Knearest(p,2);
    return 0;
}


