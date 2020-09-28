#ifndef KNN_H
#define KNN_H

#pragma once

#include <fstream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#include<bits/stdc++.h> //For 2D vector and sort() function 


#ifndef STRUCT_DATA
#define STRUCT_DATA
struct Data{
    std::vector<double> features;
    int assignedClass;
};
#endif /*STRUCT_DATA*/

class KNN{
    private:
        int neighbourCount_ = 1;
        Data unknownPoint_;
        std::vector<Data> dataPoints_;
        std::stringstream message_;
        bool debug_ = false;

    public:
        KNN();

        KNN(int neighbourCount, const std::vector<Data> &dataPoints);

        KNN(int neighbourCount, const std::vector<Data> &dataPoints, bool debug);

        void setNeighbourCount(int neighbourCount);

        int getNeighbourCount();

        void setUnknownPoint(const Data &unknownPoint);

        Data getUnknownPoint();
        /* makes a prediction which class the new data point gets */
        int predict();
        /* return info message */
        std::string getInfo();
    
    private:
        /* for printing message in terminal */
        void printToConsole_();
        /* calculates the euclidean distance between two n-dimensional points */
        std::pair<double, int> calculateDistance_(const std::vector<double> &pointOneFeatures, const std::vector<double> &pointTwoFeatures, int pointTwoClass);
        /* calculates the distance from the unknown point to all points in the dataset */
        std::vector<std::pair<double, int>> distancesAllToOne_(const Data &unknownPoint, const std::vector<Data> &dataPoints);
        /* check which class is most represented within the k-nearest-neighbours */
        int vote_(const std::vector<std::pair<double, int>> &sortedDistances, int neighbourCount);
};

#endif /*KNN_H*/
