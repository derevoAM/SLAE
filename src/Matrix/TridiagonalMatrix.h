#ifndef TRIDIAGONAL_MATRIX_TRIDIAGONALMATRIX_H
#define TRIDIAGONAL_MATRIX_TRIDIAGONALMATRIX_H

#include <vector>
#include <iostream>


template<typename T>
class TridiagonalMatrix {
private:
    int size_ = 0;
    struct Elements {
        T a;
        T b;
        T c;
    };
    std::vector<Elements> matrix_;
public:
    TridiagonalMatrix(int size_) : size_(size_) {
        matrix_.reserve(size_);
    }

    TridiagonalMatrix(std::initializer_list<T> in_list) {  // ввод элементов матрицы построчно без учета нулей
        size_ = (in_list.size() + 2) / 3;
        matrix_.reserve(size_);
        int i = 0;
        T a = 0, b, c;

        for (auto it: in_list) {
            if (i % 3 == 0) b = it;
            if (i % 3 == 1) {
                c = it;
                matrix_.push_back(Elements{a, b, c});
            }
            if (i % 3 == 2) a = it;
            i++;
        }

        matrix_.push_back(Elements{a, b, 0});
    }


    T operator()(int i, int j) const {
        if (j > i + 1 || j < i - 1) return 0;

        if (i == j) return matrix_[i].b;
        if (i == j + 1) return matrix_[i].a;
        return matrix_[i].c;
    }

    int Get_size() const { return size_; }

    friend std::ostream &operator<<(std::ostream &out, const TridiagonalMatrix<T> &matrix) {
        for (int i = 0; i < matrix.size_; i++) {
            for (int j = 0; j < matrix.size_; j++) out << matrix(i, j) << " ";
            out << "\n";
        }
        return out;
    }

};


#endif