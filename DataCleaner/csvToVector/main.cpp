#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>  // for setprecision()

#include "ReadCSV.hpp"

int main(){

    ReadCSV reader("/home/patrick/Downloads/breast-cancer-wisconsin.data", ",", false);
    std::vector<Data> myData = reader.readForAlgorithm();
    std::cout << reader.getInfo() << std::endl;

    int i = 0;

    std::cout << "Datapoints: ";
    for (double dataPoint : myData.at(i).features){
        std::cout << std::fixed << std::setprecision(2) << dataPoint << ", ";
    }
    std::cout << std::endl;
    std::cout << "Class: " << myData.at(i).assignedClass << std::endl;


    std::cout << std::endl << std::endl;


    std::vector<std::vector<double>> myData1 = reader.readForManipulator();
    std::cout << reader.getInfo() << std::endl;

    std::cout << "Datapoints: ";
    for (double dataPoint : myData1.at(i)){
        std::cout << std::fixed << std::setprecision(2) << dataPoint << ", ";
    }
    std::cout << std::endl;

}