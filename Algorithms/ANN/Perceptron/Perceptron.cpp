#include <string>
#include <vector>
#include <iostream>

#include "Perceptron.hpp"
#include "../../../ExternalLibs/eigen-3.3.7/Eigen/Dense"

using namespace Eigen;

Perceptron::Perceptron(std::vector<int> neuronsPerLayer, int numEpochs){
    //std::cout << "constructor entered" << std::endl;
    this->numEpochs_ = numEpochs;
    for (int i=0; i < neuronsPerLayer.size(); ++i){
        if (i+1 < neuronsPerLayer.size()){
            this->weights_.push_back(MatrixXd::Random(neuronsPerLayer.at(i), neuronsPerLayer.at(i+1)));     // initialize size of weight-matrices with right dimensions and random values between -1 and 1
        }
        this->layers_.push_back(MatrixXd::Random(1, neuronsPerLayer.at(i)));    // initialize amount of neurons per layer 
    }
    //std::cout << "constructor finished" << std::endl;
}

void Perceptron::setTrainingsData(std::vector<Data> trainingsData){
    //std::cout << "setTrainingsData entered" << std::endl;
    this->trainingsData_ = trainingsData;
    //std::cout << "setTrainingsData finished" << std::endl;
}

void Perceptron::train(){
    //std::cout << "train entered" << std::endl;
    for (int i=0; i < this->numEpochs_; ++i){
        for (Data &example : this->trainingsData_){
            if (example.features.size() == this->layers_.at(0).cols()){
                stdVectorToEigenMatrix(this->layers_.at(0), example.features);      // sets the matrix of the input layer to the values of the current data point
                this->propagateForward();
                this->calcErrors();
                this->propagateBackward();
                this->updateWeights();
            }
            else{
                std::cout << "data feature size does not match input size of model!" << std::endl;
            }
        }
    }
    //std::cout << "train finished" << std::endl;
}

void Perceptron::propagateForward(){
    std::vector<MatrixXd>::iterator layerIteratorOutput = this->layers_.begin()+1;
    std::vector<MatrixXd>::iterator layerIteratorInput = this->layers_.begin();

    for (std::vector<MatrixXd>::iterator weightIterator = this->weights_.begin(); weightIterator < this->weights_.end(); ++weightIterator){
        std::cout << "Matrix: " << *weightIterator << std::endl;
        std::cout << "Layer: " << *layerIteratorOutput << std::endl << std::endl;

        *layerIteratorOutput = *layerIteratorInput * *weightIterator;
        std::cout << "Updated Layer: " << *layerIteratorOutput << std::endl << std::endl; 

        ++layerIteratorInput; 
        ++layerIteratorOutput;
    }
}

void Perceptron::calcErrors(){
    // to be continued
}

void Perceptron::propagateBackward(){
    // to be continued
}

void Perceptron::updateWeights(){
    // to be continued
}

void Perceptron::stdVectorToEigenMatrix(MatrixXd &mat, const std::vector<double> &vec){
    //std::cout << "stdVectorToEigenMatrix entered" << std::endl;
    int i = 0;
    for (double value : vec){
        mat(0, i) = value;
        i++;
    }
    std::cout << "input matrix: " << mat << std::endl;
    //std::cout << "stdVectorToEigenMatrix finsihed" << std::endl;
}