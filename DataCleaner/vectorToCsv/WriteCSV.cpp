#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "WriteCSV.hpp"


WriteCSV::WriteCSV(std::string path, std::vector<std::vector<double>> data){
    this->path_ = path;
    this->data_ = data;
}

void WriteCSV::write(std::string mode){
    if (mode == "append"){
        this->file_.open(this->path_, std::ios::app);
    }
    else if (mode == "write"){
        this->file_.open(this->path_, std::ios::out);
    }
    file_ << this->vectorToString();
    this->file_.close();
}

std::string WriteCSV::vectorToString(){
    std::ostringstream messageStream;

    for (const std::vector<double> &row : this->data_){
        std::copy(row.begin(), row.end()-1, std::ostream_iterator<double>(messageStream, ","));
        messageStream << row.back() << std::endl;
    }

    std::string messageString = messageStream.str();
    messageStream.str(std::string());

    return messageString;
}