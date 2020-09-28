#include <iostream>
#include <fstream>
#include "KNN.hpp"

#include <iomanip>

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#include <bits/stdc++.h> //For 2D vector and sort() function 


using namespace std;


int main(){
    /* initialize fake datapoints */
    Data point0;
    Data point1;
    Data point2;
    Data point3;
    Data point4;
    Data point5;

    /* populate fake datapoints */
    point0.features = {1.0, 1.0, 2.0};
    point0.assignedClass = 1;

    point1.features = {1.0, 1.5, 1.5};
    point1.assignedClass = 1;

    point2.features = {1.0, 0.5, 1.5};
    point2.assignedClass = 1;

    point3.features = {1.0, 6.0, 7.0};
    point3.assignedClass = 2;

    point4.features = {1.0, 5.5, 6.5};
    point4.assignedClass = 2;

    point5.features = {1.0, 6.0, 5.0};
    point5.assignedClass = 2;

    /* fill dataset with fake datapoints */
    vector<Data> dataPoints = {
        point0,
        point1,
        point2,
        point3,
        point4,
        point5
    };

    /* initialization of new unclassified datapoint */
    Data unknownPoint;
    unknownPoint.features = {5.0, 2.5, 0.0};

    int neighbours = 0; // amount of neighbours for prediction
    double x, y, z;     // coordinate variables of new datapoint

    for (int i=0; i < 3; ++i){
        cout << "How many neighbours: ";
        std::cin >> neighbours;
        cout << "New point: ";
        std::cin >> x >> y >> z;

        unknownPoint.features = {x, y, z};

        KNN model(neighbours, dataPoints, true);      // create model
        model.setUnknownPoint(unknownPoint);    // give it the new datapoint
        unknownPoint.assignedClass = model.predict();   // predict class and assign it to uknown data point

        cout << "Predicted class : " << unknownPoint.assignedClass  << endl;
    }
}
