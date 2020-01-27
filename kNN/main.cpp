#include <iostream>
#include "KNN.h"

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


