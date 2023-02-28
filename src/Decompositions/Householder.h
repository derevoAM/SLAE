#ifndef SLAE_HOUSEHOLDER_H
#define SLAE_HOUSEHOLDER_H

#include "../Matrix/Dense.h"

namespace Householder {
    template<typename T>
    std::tuple<Dense<T>, Dense<T>> QR(const Dense<T> &input_) {
        Dense<T> A = input_;
        int n = A.get_width();
        int m = A.get_height();
        std::vector<Dense<T>> normal_;
        std::vector<Dense<T>> columns_;
        columns_.reserve(n);
        for (int i = 0; i < n; i++) columns_.push_back(A.get_column(i)); // matrix representation as vector of columns
        normal_.reserve(n);
        for (int i = 0; i < n; i++) {
            normal_.push_back(columns_[i].eval_norm_vec(i)); // adding normal vector
            for (int j = i; j < n; j++) {
                columns_[j] +=
                        normal_[i] *
                        (-2 * columns_[j].scalar(normal_[i]) / (normal_[i].scalar(normal_[i])));

            }
        }

        Dense<T> Q{m, m};
        for (int i = 0; i < m; i++) Q(i, i) = 1;
        Q += normal_[0] * normal_[0].Transpose() * (-2 / normal_[0].scalar(normal_[0]));

        std::vector<Dense<T>> col_Q_;
        col_Q_.reserve(m);
        for (int i = 0; i < m; i++) col_Q_.push_back(Q.get_column(i));

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                col_Q_[j] +=
                        normal_[i] *
                        (-2 * col_Q_[j].scalar(normal_[i]) / (normal_[i].scalar(normal_[i])));
            }
        }

        // creating Q matrix
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) Q(i, j) = col_Q_[i](j, 0);
        }

        // creating R matrix
        Dense<T> R{m, n};
        for (int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j ++) R(i, j) = columns_[j](i, 0);
        }
        return {Q, R};

    }
}
#endif //SLAE_HOUSEHOLDER_H
