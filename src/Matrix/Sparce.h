#ifndef SLAE_SPARCE_H
#define SLAE_SPARCE_H

#include <vector>
#include <map>
#include <iostream>

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

    std::vector<T> operator*(const std::vector<T> &mult_) {
        std::vector<T> result_;
        result_.reserve(h_);
        for (int i = 0; i < h_; i++) {
            T sum = 0;
            for (int j = 0; j < row_[i + 1] - row_[i]; j++) sum += value_[row_[i] + j] * mult_[col_[row_[i] + j]];
            result_.push_back(sum);
        }
        return result_;
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

    friend std::ostream &operator<<(std::ostream &out, const CSR<T> &matrix) {
        for (int i = 0; i < matrix.h_; i++) {
            for (int j = 0; j < matrix.w_; j++) out << matrix(i, j) << " ";
            out << "\n";
        }
        return out;
    }
};

#endif //SLAE_SPARCE_H
