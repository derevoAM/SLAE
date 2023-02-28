#ifndef SLAE_DENSE_H
#define SLAE_DENSE_H

#include <vector>
#include <iostream>
#include <cmath>

template<typename T>
class Dense {
private:
    std::vector<T> matrix_;
    int h_, w_;
public:
    Dense(int h_, int w_, const std::vector<T> input_) : h_(h_), w_(w_), matrix_(input_) {};

    T operator()(int i, int j) const { return matrix_[i * w_ + j]; }

    T &operator()(int i, int j) { return matrix_[i * w_ + j]; }

    int get_height() const { return h_; }

    int get_width() const { return w_; }

    Dense<T> operator*(Dense<T> &mult_) {
        std::vector<T> result_;
        result_.reserve(h_ * mult_.w_);
        for (int i = 0; i < h_; i++) {
            for (int k = 0; k < mult_.w_; k++) {
                T sum = 0;
                for (int j = 0; j < w_; j++) sum += matrix_[i * w_ + j] * mult_(j, k);
                result_.push_back(sum);
            }
        }
        return Dense<T>{h_, mult_.w_, result_};
    }

    Dense<T> operator+(Dense<T> &add_) {
        std::vector<T> result_;
        result_.reserve(w_ * h_);
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) result_.push_back(matrix_[i * w_ + j] + add_(i, j));
        }
        return Dense<T>{h_, w_, result_};
    }

    void Transpose() {
        std::vector<T> trans_;
        trans_.reserve(h_ * w_);
        for (int i = 0; i < w_; i++) {
            for (int j = 0; j < h_; j++) {
                trans_.push_back(matrix_[j * w_ + i]);
            }
        }
        std::swap(h_, w_);
        matrix_ = trans_;
    }

    Dense<T> get_column(int j) {
        std::vector<T> col_;
        col_.reserve(h_);
        for (int i = 0; i < h_; i++) col_.push_back(matrix_[i * w_ + j]);
        return Dense<T>{h_, 1, col_};
    }

    double norm(Dense<T> &vec_) const // only for vectors
    {
        T sum = 0;
        for (int i = 0; i < vec_.size(); i++) sum += vec_(i, 0) * vec_(i, 0);
        return sqrt(static_cast<double>(sum));
    }

    Dense<T> &eval_norm_vec(int i) {
        if (this(i, 0) >= 0) {
            this(i, 0) += this->norm();
        } else this(i, 0) -= this(i, 0) - this->norm();
        double cur_norm = this->norm();
        for (int j = 0; j < h_; j++) this(j, 0) /= cur_norm;
        return this;
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
