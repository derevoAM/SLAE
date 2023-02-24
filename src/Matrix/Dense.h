#ifndef SLAE_DENSE_H
#define SLAE_DENSE_H

#include <vector>
#include <iostream>

template<typename T>
class Dense {
private:
    std::vector<T> matrix_;
    int h_, w_;
public:
    Dense(int h_, int w_, const std::vector<T> input_) : h_(h_), w_(w_), matrix_(input_) {};

    T operator()(int i, int j) const { return matrix_[i * w_ + j]; }

    const int get_height() { return h_; }

    const int get_width() { return w_; }

    Dense<T> operator*(Dense<T> &mult_) {
        if (mult_.h_ != w_) throw std::invalid_argument("invalid arguments: cannot multiply");
        std::vector<T> result_;
        result_.reserve(h_ * mult_.w_);
        for (int i = 0; i < h_; i++) {
            for(int k = 0; k < mult_.w_; k ++)
            {
                T sum = 0;
                for (int j = 0; j < w_; j++) sum += matrix_[i * w_ + j] * mult_(j, k);
                result_.push_back(sum);
            }
        }
        return Dense<T>{h_, mult_.w_, result_};
    }

    Dense<T> operator+(Dense<T> &add_) {
        if (add_.w_ != w_ || add_.h_ != h_) throw std::invalid_argument("invalid vector: cannot sum");
        std::vector<T> result_;
        result_.reserve(w_ * h_);
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) result_.push_back(matrix_[i * w_ + j] + add_(i, j));
        }
        return Dense<T>{h_, w_, result_};
    }


    friend std::ostream &operator<<(std::ostream &out, const Dense<T> &output_) {
        for (int i = 0; i < output_.h_; i++) {
            for (int j = 0; j < output_.w_; j++) out << output_(i, j) << " ";
            out << "\n";
        }
        return out;
    }
};

#endif //SLAE_DENSE_H
