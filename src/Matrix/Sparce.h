#ifndef SLAE_SPARCE_H
#define SLAE_SPARCE_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Vector.h"

template<typename T>
struct DOK {
    int i;
    int j;
    T value_;

    bool operator<(const DOK<T> dok_) const {
        if (i != dok_.i) return i < dok_.i;
        if (i == dok_.i) return j < dok_.j;
    }

};


template<typename T>
class CSR {
private:
    std::vector<T> value_;
    std::vector<int> col_;
    std::vector<int> row_;
    int h_; // height
    int w_; // width

public:

    CSR(std::vector<DOK<T>> &elements_, int row_num, int col_num) : h_(row_num), w_(col_num) {
        std::sort(elements_.begin(), elements_.end());
        row_.reserve(row_num + 1);
        value_.reserve(elements_.size());
        col_.reserve(elements_.size());
        row_.push_back(0);

        int count_el = 0;
        int i = 0; // row index
        for (auto it: elements_) {
            while (i < it.i) {
                row_.push_back(count_el);
                i += 1;
            }

            if (it.i == i) {
                value_.push_back(it.value_);
                col_.push_back(it.j);
                count_el++;
            }
        }
        row_.push_back(count_el);


    }

    T operator()(int i, int j) const {
        for (int k = 0; k < row_[i + 1] - row_[i]; k++) {
            if (col_[row_[i] + k] == j) return value_[row_[i] + k];
        }
        return 0;
    }


    std::vector<T> operator*(const std::vector<T> &mult_) const {
        std::vector<T> result_;
        result_.reserve(h_);
        for (int i = 0; i < h_; i++) {
            T sum = 0;
            for (int j = 0; j < row_[i + 1] - row_[i]; j++) sum += value_[row_[i] + j] * mult_[col_[row_[i] + j]];
            result_.push_back(sum);
        }
        return result_;
    }
    CSR<T> operator*(const CSR<T> &mult_) // TODO: modify
    {
        std::vector<DOK<T>> elem_;
        elem_.reserve(h_ * mult_.w_);
        for (int i = 0; i < h_; i++) {
            for (int k = 0; k < mult_.w_; k++) {
                T sum = static_cast<T>(0);
                for (int j = 0; j < w_; j++) sum += (*this)(i, j) * mult_(j, k);
                if(sum != 0) elem_.push_back({i, k, sum});
            }
        }
        return CSR<T>{elem_, h_, mult_.w_};
    }

    CSR<T> operator+(const CSR<T> &add_) {
        std::vector<DOK<T>> elem_;
        elem_.reserve(h_ * w_);
        for (int i = 0; i < h_; i++) {
            for(int j = 0; j < w_; j ++)
            {
                if((*this)(i, j) + add_(i, j) != 0) elem_.push_back({i, j, (*this)(i, j) + add_(i, j)});
            }
        }
        return CSR<T>{elem_, h_, w_};
    }

    CSR<T> operator-(const CSR<T> &add_) {
        std::vector<DOK<T>> elem_;
        elem_.reserve(h_ * w_);
        for (int i = 0; i < h_; i++) {
            for(int j = 0; j < w_; j ++)
            {
                if((*this)(i, j) - add_(i, j) != 0) elem_.push_back({i, j, (*this)(i, j) - add_(i, j)});
            }
        }
        return CSR<T>{elem_, h_, w_};
    }

    CSR<T> transpose() // TODO: modify
    {
        std::vector<DOK<T>> elem_;
        elem_.reserve(value_.size());
        for(int i = 0; i < h_; i ++)
        {
            for(int j = 0; j < w_; j ++)
            {
                if((*this)(i, j) != 0)
                {
                    elem_.push_back({j, i, (*this)(i, j)});
                }
            }
        }
        return CSR<T>{elem_, w_, h_};
    }



    T get_value(int i) const {
        return value_[i];
    }

    int get_col(int i) const {
        return col_[i];
    }

    int get_row(int i) const {
        return row_[i];
    }

    T max_eigenvalue_pow() // t - tolerance
    {
        std::vector<T> r(h_, static_cast<T>(1));
        T lambda;
        for(int i = 0; i < 100; i ++)
        {
            //lambda = scalar(r, (*this) * r) / scalar(r, r);
            //std::cout << lambda << "\n";
            r = (*this) * r * (static_cast<T>(1) / norm((*this) * r));
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const CSR<T> &matrix) {
        for (int i = 0; i < matrix.h_; i++) {
            for (int j = 0; j < matrix.w_; j++) out << matrix(i, j) << " ";
            out << "\n";
        }
        return out;
    }
};

template<typename T>
bool stop_check(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b, T tolerance) {
    std::vector<T> result_;
    result_.reserve(x.size());
    for (int i = 0; i < x.size(); i++) {
        T sum = 0;
        for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++) sum += A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
        result_.push_back(sum);
    }
    //std::cout << result_ << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n ";
    return norm(result_ - b) < tolerance;
}

#endif //SLAE_SPARCE_H
