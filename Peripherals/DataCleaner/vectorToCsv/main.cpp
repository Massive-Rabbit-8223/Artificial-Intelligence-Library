#include "WriteCSV.hpp"

int main(){
    std::vector<std::vector<double>> data = {
        {5.1, 3.2, 2.3, 6.3, 1.3, 4.5, 2.},
        {4, 2, 2, 1, 7, 10, 4}
    };
    WriteCSV writer("/home/patrick/Documents/projects/ML_library/DataCleaner/vectorToCsv/test1.csv", data);
    writer.write("append");
}