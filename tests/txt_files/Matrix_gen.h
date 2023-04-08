#ifndef SLAE_MATRIX_GEN_H
#define SLAE_MATRIX_GEN_H

#include "../../src/Matrix/Sparce.h"

template<typename T>
CSR<T> mat_diag_pos_1000()
{
    std::vector<DOK<double>> dok_;

    std::string line;
    std::string i_;
    std::string j_;
    std::string value_;

    std::ifstream file("/home/derevo/Projects/SLAE/tests/txt_files/mat_diag_pos_1000.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[1] == ' ') {
                i_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                i_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                i_.assign(line, 0, 3);
                line.erase(0, 4);
            }


            if (line[1] == ' ') {
                j_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                j_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                j_.assign(line, 0, 3);
                line.erase(0, 4);
            }

            value_ = line;
            dok_.push_back({std::stoi(i_), std::stoi(j_), std::stod(value_)});
        }
    }
    file.close();

    return CSR<double>(dok_, 1000, 1000);
}

template<typename T>
std::vector<T> b_1000()
{
    std::string line;

    std::vector<double> b;
    b.reserve(1000);

    std::ifstream file_b("/home/derevo/Projects/SLAE/tests/txt_files/b_1000.txt");
    if (file_b.is_open()) {
        while (getline(file_b, line)) {
            b.push_back(std::stod(line));
        }
    }
    file_b.close();

    return b;
}


template<typename T>
CSR<T> mat_diag_pos_100()
{
    std::vector<DOK<double>> dok_;

    std::string line;
    std::string i_;
    std::string j_;
    std::string value_;

    std::ifstream file("/home/derevo/Projects/SLAE/tests/txt_files/mat_diag_pos_100.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[1] == ' ') {
                i_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                i_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                i_.assign(line, 0, 3);
                line.erase(0, 4);
            }


            if (line[1] == ' ') {
                j_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                j_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                j_.assign(line, 0, 3);
                line.erase(0, 4);
            }

            value_ = line;
            dok_.push_back({std::stoi(i_), std::stoi(j_), std::stod(value_)});
        }
    }
    file.close();

    return CSR<double>(dok_, 100, 100);
}

template<typename T>
std::vector<T> b_100()
{
    std::string line;

    std::vector<double> b;
    b.reserve(100);

    std::ifstream file_b("/home/derevo/Projects/SLAE/tests/txt_files/b_100.txt");
    if (file_b.is_open()) {
        while (getline(file_b, line)) {
            b.push_back(std::stod(line));
        }
    }
    file_b.close();

    return b;
}


template<typename T>
CSR<T> mat_diag_pos_20()
{
    std::vector<DOK<double>> dok_;

    std::string line;
    std::string i_;
    std::string j_;
    std::string value_;

    std::ifstream file("/home/derevo/Projects/SLAE/tests/txt_files/mat_diag_pos_20.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[1] == ' ') {
                i_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                i_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                i_.assign(line, 0, 3);
                line.erase(0, 4);
            }


            if (line[1] == ' ') {
                j_.assign(line, 0, 1);
                line.erase(0, 2);
            } else if(line[2] == ' '){
                j_.assign(line, 0, 2);
                line.erase(0, 3);
            } else if(line[3] == ' '){
                j_.assign(line, 0, 3);
                line.erase(0, 4);
            }

            value_ = line;
            dok_.push_back({std::stoi(i_), std::stoi(j_), std::stod(value_)});
        }
    }
    file.close();

    return CSR<double>(dok_, 20, 20);
}

template<typename T>
std::vector<T> b_20()
{
    std::string line;

    std::vector<double> b;
    b.reserve(20);

    std::ifstream file_b("/home/derevo/Projects/SLAE/tests/txt_files/b_20.txt");
    if (file_b.is_open()) {
        while (getline(file_b, line)) {
            b.push_back(std::stod(line));
        }
    }
    file_b.close();

    return b;
}

#endif //SLAE_MATRIX_GEN_H
