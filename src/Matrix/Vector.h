#ifndef SLAE_VECTOR_H
#define SLAE_VECTOR_H

#include <iostream>
#include <vector>
#include <cmath>


template<typename T>
std::vector<T> operator+(const std::vector<T> &vec_1_, const std::vector<T> &vec_2_) {
    std::vector<T> res_;
    res_.reserve(vec_1_.size());
    for (int i = 0; i < vec_1_.size(); i++) res_.push_back(vec_1_[i] + vec_2_[i]);
    return res_;
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &vec_1_, T mult_) {
    std::vector<T> res_;
    res_.reserve(vec_1_.size());
    for (int i = 0; i < vec_1_.size(); i++) res_.push_back(vec_1_[i] * mult_);
    return res_;
}

template<typename T>
T scalar(const std::vector<T> &mult_1, const std::vector<T> &mult_2)
{
    T sum = 0;
    for(int i = 0; i < mult_1.size(); i ++) sum += mult_1[i] * mult_2[i];
    return sum;
}

template<typename T>
std::vector<T> operator-(const std::vector<T> &vec_1_, const std::vector<T> &vec_2_) {
    std::vector<T> res_;
    res_.reserve(vec_1_.size());
    for (int i = 0; i < vec_1_.size(); i++) res_.push_back(vec_1_[i] - vec_2_[i]);
    return res_;
}

template<typename T>
T norm(const std::vector<T> &vec_) {
    T res_ = 0;
    for (int i = 0; i < vec_.size(); i++) res_ += vec_[i] * vec_[i];
    return res_;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &matrix) {

    for (int j = 0; j < matrix.size(); j++) out << matrix[j] << " ";
    //out << "\n";
    return out;
}


#endif //SLAE_VECTOR_H
