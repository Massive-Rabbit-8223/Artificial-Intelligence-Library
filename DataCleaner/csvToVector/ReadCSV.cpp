#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "ReadCSV.hpp"

 
ReadCSV::ReadCSV(std::string filePath){
    this->filePath_ = filePath;
}

ReadCSV::ReadCSV(std::string filePath, std::string delimiter){
    this->filePath_ = filePath;
    this->delimiter_ = delimiter;
}

ReadCSV::ReadCSV(std::string filePath, std::string delimiter, bool debug){
    this->filePath_ = filePath;
    this->delimiter_ = delimiter;
    this->debug_ = debug;
}

std::vector<Data> ReadCSV::readForAlgorithm(){
    this->file_.open(this->filePath_);

    int lineCounter = 0;        // counts the lines of reading file
    int corruptionCounter = 0;  // counts the lines that couldn't be converted

    std::string token;      // stores one seperated value at a time

    std::vector<Data> data;      // this vector later contains the then converted data

    if (this->file_.is_open()){
        while (!this->file_.eof()){
            std::string line;
            std::getline(this->file_, line);     // get current line of the file

            if (debug_ == true){
                std::cout << "data at line(" << lineCounter << "): " << line << std::endl;
            }

            size_t pos = 0;     // stores the index of the string where the delimiter has been found
            Data lineData;       // stores the converted data of a line, which gets pushed backed to the "data" vector
            bool corrupted = false;     // is set to true when a line can not be converted
            
            while ((pos = line.find(this->delimiter_)) != std::string::npos) {
                token = line.substr(0, pos);        // get the substring containing the first element of the line excluding the delimiter

                try{
                    lineData.features.push_back(stod(token));       // try to convert string to double, then push it back to the vector
                }
                catch(const std::invalid_argument &e){       // exception occurs when a string can not be converted to an int
                    corrupted = true;
                }
                
                line.erase(0, pos + this->delimiter_.length());      // delete the first element from line as well as the delimiter, so that in the next iteration the second element becomes the first one
            }

            try{
                lineData.assignedClass = stoi(line);
            }
            catch(const std::invalid_argument &e){
                corrupted = true;
            }

            if (corrupted == false){
                data.push_back(lineData);   // only if the line has been converted successfully then we add it to the "data" vector
            }
            else{
                corruptionCounter++;
            }  
                       
            lineCounter++;
        }
        this->message_ << "total lines: " << lineCounter << std::endl;
        file_.close();
    }
    else{
        this->message_ << "File not found!" << std::endl;
    }

    this->message_ << "length of data-vector: " << data.size() << std::endl;
    this->message_ << "corrupted lines: " << corruptionCounter << std::endl;

    return data;
}

std::vector<std::vector<double>> ReadCSV::readForManipulator(){
    this->file_.open(this->filePath_);

    int lineCounter = 0;        // counts the lines of reading file
    int corruptionCounter = 0;  // counts the lines that couldn't be converted

    std::string token;      // stores one seperated value at a time

    std::vector<std::vector<double>> data;      // this vector later contains the then converted data

    if (this->file_.is_open()){
        while (!this->file_.eof()){
            std::string line;
            std::getline(this->file_, line);     // get current line of the file

            if (debug_ == true){
                std::cout << "data at line(" << lineCounter << "): " << line << std::endl;
            }

            size_t pos = 0;     // stores the index of the string where the delimiter has been found
            std::vector<double> lineData;       // stores the converted data of a line, which gets pushed backed to the "data" vector
            bool corrupted = false;     // is set to true when a line can not be converted
            
            while ((pos = line.find(this->delimiter_)) != std::string::npos) {
                token = line.substr(0, pos);        // get the substring containing the first element of the line excluding the delimiter

                try{
                    lineData.push_back(stod(token));       // try to convert string to double, then push it back to the vector
                }
                catch(const std::invalid_argument &e){       // exception occurs when a string can not be converted to an int
                    corrupted = true;
                }
                
                line.erase(0, pos + this->delimiter_.length());      // delete the first element from line as well as the delimiter, so that in the next iteration the second element becomes the first one
            }

            try{
                lineData.push_back(stod(line));
            }
            catch(const std::invalid_argument &e){
                corrupted = true;
            }

            if (corrupted == false){
                data.push_back(lineData);   // only if the line has been converted successfully then we add it to the "data" vector
            }
            else{
                corruptionCounter++;
            }  
                       
            lineCounter++;
        }
        this->message_ << "total lines: " << lineCounter << std::endl;
        file_.close();
    }
    else{
        this->message_ << "File not found!" << std::endl;
    }

    this->message_ << "length of data-vector: " << data.size() << std::endl;
    this->message_ << "corrupted lines: " << corruptionCounter << std::endl;

    return data;
}

std::string ReadCSV::getInfo(){
    std::string info = this->message_.str();
    this->message_.str(std::string());      // clearing the string stream
    return info;
}

