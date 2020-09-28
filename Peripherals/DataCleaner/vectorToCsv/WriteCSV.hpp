#ifndef WRITECSV_H
#define WRITECSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class WriteCSV{
    private:
        std::ofstream file_;
        std::vector<std::vector<double>> data_;
        std::string path_;
        std::string delimiter_;

    public:
        WriteCSV(std::string path, std::vector<std::vector<double>> data);

        void write(std::string mode);

    private:
        std::string vectorToString();
};

#endif /*WRITE_CSV*/