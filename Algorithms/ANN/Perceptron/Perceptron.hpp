#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <string>
#include <vector>
#include "../../../ExternalLibs/eigen-3.3.7/Eigen/Dense"

using namespace Eigen;

#ifndef STRUCT_DATA
#define STRUCT_DATA
struct Data{
    std::vector<double> features;
    int assignedClass;
};
#endif /*STRUCT_DATA*/

class Perceptron{
    private:
        std::string activationFunction_;
        std::vector<MatrixXd> weights_;
        std::vector<MatrixXd> layers_;
        std::vector<Data> trainingsData_;
        int numEpochs_ = 0;

    public:
        Perceptron(std::vector<int> neuronsPerLayer, int numEpochs);
        void setTrainingsData(std::vector<Data> trainingsData);
        void train();

    private:
        void propagateForward();
        void calcErrors(int assignedClass);
        void propagateBackward();
        void updateWeights();
        void stdVectorToEigenMatrix(MatrixXd &mat, const std::vector<double> &vec);
        double activationFunction();
        double activationFunctionDerivative();
        double sigmoid(double x);
        double sigmoidDerived();
};

#endif /*PERCEPTRON_H*/