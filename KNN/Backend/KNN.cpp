#include "KNN.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>  // for setprecision()
#include <sstream>

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#include<bits/stdc++.h> //For 2D vector and sort() function 

//using namespace std;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;
using std::sort;
using std::stringstream;



KNN::KNN(int neighbourCount, const vector<Data> &dataPoints){
    this->neighbourCount_ = neighbourCount;
    this->dataPoints_ = dataPoints;
}

KNN::KNN(int neighbourCount, const vector<Data> &dataPoints, bool debug){
    this->neighbourCount_ = neighbourCount;
    this->dataPoints_ = dataPoints;
    this->debug_ = debug;
}

void KNN::setNeighbourCount(int neighbourCount){
    this->neighbourCount_ = neighbourCount;
}

int KNN::getNeighbourCount(){
    return this->neighbourCount_;
}

void KNN::setUnknownPoint(const Data &unknownPoint){
    this->unknownPoint_ = unknownPoint;
}

Data KNN::getUnknownPoint(){
    return this->unknownPoint_;
}
/* makes a prediction which class the new data point gets */
int KNN::predict(){
    vector<pair<double, int>> allDistances = distancesAllToOne_(this->unknownPoint_, this->dataPoints_);
    sort(allDistances.begin(), allDistances.end());         // sort all distances from shortest to longest ascending

    /* For creation of the info message */
    for (const pair<double, int> &distance : allDistances){
        this->message_ << "Distance from { ";
        int counter = 1;

        for (double feature : unknownPoint_.features){
            this->message_ << std::fixed << std::setprecision(2) << feature;

            if (counter < unknownPoint_.features.size()){
                this->message_ << " | ";
                counter++;
            }
        }
        this->message_ << " }: " << distance.first << " --> class: " << distance.second << endl; 
    }  
    
    return vote_(allDistances, this->neighbourCount_);
}
/* return message string for printing it to the UI */
string KNN::getInfo(){
    std::string info = this->message_.str();
    this->message_.str(std::string());      // clearing the string stream
    return info;
}
/* for printing message in terminal */
void KNN::printToConsole_(){
    std::string info = this->message_.str();
    this->message_.str(std::string());      // clearing the string stream
    cout << info << endl;
}
/* calculates the euclidean distance between two n-dimensional points */
pair<double, int> KNN::calculateDistance_(const vector<double> &pointOneFeatures, const vector<double> &pointTwoFeatures, int pointTwoClass){
    vector<double> coordinateDifferences;     // stores the differences between the coordinates of the two points
    for (int i=0; i < pointTwoFeatures.size(); ++i){
        coordinateDifferences.push_back(pointTwoFeatures.at(i) - pointOneFeatures.at(i));     // calculate distance and add to vector
    }

    double summedSquaredDistances = 0.0;    // stores the summation of the squared distances
    for (double difference : coordinateDifferences){
        summedSquaredDistances += pow(difference, 2);
    }
    /* return a vector with the first value as the distance between point one and point two and the second value as the class of the second point */
    return {sqrt(summedSquaredDistances), pointTwoClass};     
}
/* calculates the distance from the unknown point to all points in the dataset */
vector<pair<double, int>> KNN::distancesAllToOne_(const Data &unknownPoint, const vector<Data> &dataPoints){
    vector<pair<double, int>> distances;

    for (const Data &point : dataPoints){
        distances.push_back(calculateDistance_(unknownPoint.features, point.features, point.assignedClass));
    }

    return distances;
}
/* check which class is most represented within the k-nearest-neighbours */
int KNN::vote_(const vector<pair<double, int>> &sortedDistances, int neighbourCount){
    std::map<int, vector<int>> classVotes;

    /* go over the first k sorted distances to retrieve its class and expand a vector whose length determines the appearence of the class */
    for (int i=0; i < neighbourCount; ++i){
        /* map = {class (int) : appearance (vector)} -> length of the vector determines how often this class appeared */
        classVotes[sortedDistances.at(i).second].push_back(1);    // expand appearence-vector of found class by one 
    }

    int vote = 0;
    int greatestSize = 0;

    for (auto const &x : classVotes){
        this->message_ << x.first << ':' << x.second.size() << endl;
        if (x.second.size() > greatestSize){        // compare the sizes of the appearence-vectors
            vote = x.first;     // the vote variable is set to the class of the longest appearence-vector
            greatestSize = x.second.size();
        }
    }

    if(this->debug_ == true){
        printToConsole_();       // display message to the console
    }

    return vote;
}