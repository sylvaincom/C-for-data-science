#include <iostream>
#include "Kmeans.h"

int main() {

    std::ifstream input;
    input.open("C:/Users/julie/Desktop/test_data_1.dat");
    std::ostream &output_console = std::cout;
    kmeans_set kmeans_set();
    //kmeans_set km(input, ',');
    kmeans_set().compute_centroids(5);

    std::cout << "\n\nOutput in main():\n";
    kmeans_set().print_centroids(output_console, ',');
    return 0;

}
