#ifndef READCSV_H
#define READCSV_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#pragma once

#ifndef STRUCT_DATA
#define STRUCT_DATA
struct Data{
    std::vector<double> features;
    int assignedClass;
};
#endif /*STRUCT_DATA*/

class ReadCSV{
    private:
        std::ifstream file_;
        std::string filePath_;
        std::stringstream message_;
        bool debug_ = false;     // when set to true additional information gets displayed to the console
        std::string delimiter_ = ",";

    public:
        ReadCSV(std::string filePath);

        ReadCSV(std::string filePath, std::string delimiter);

        ReadCSV(std::string filePath, std::string delimiter, bool debug);
        
        std::vector<Data> readForAlgorithm();        // reading the csv file and convert it to Data-object holding double values

        std::vector<std::vector<double>> readForManipulator();        // reading the csv file and convert it to Data-object holding double values

        std::string getInfo();      // returns collected info which has been collected during the conversion process
};

#endif /*READCSV_H*/
