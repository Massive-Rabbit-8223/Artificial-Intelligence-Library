#include <iostream>
#include "../../Libs/eigen-3.3.7/Eigen/Dense"
#include "Perceptron.hpp"
 
using namespace Eigen;
using namespace std;
 
int main()
{
  std::vector<Data> fakeData;

  Data fakePoint1;
  fakePoint1.features = {2, 1, 5};
  fakePoint1.assignedClass = 1;

  Data fakePoint2;
  fakePoint2.features = {3, 7, 4};
  fakePoint2.assignedClass = 2;

  fakeData.push_back(fakePoint1);
  fakeData.push_back(fakePoint2);

  std::vector<int> neuronsPerLayer = {3, 3, 2, 1};

  Perceptron model(neuronsPerLayer, 10);
  model.setTrainingsData(fakeData);
  model.train();
}