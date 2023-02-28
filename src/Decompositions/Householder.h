#ifndef SLAE_HOUSEHOLDER_H
#define SLAE_HOUSEHOLDER_H

#include "../Matrix/Dense.h"

namespace Householder
{
    template<typename T>
    std::tuple<Dense<T>, Dense<T>> QR(const Dense<T> &A)
    {
        int n = A.get_width();
        int m = A.get_height();
        Dense<T> Q{m, m, {}};
        Dense<T> R{m, n, {}};
        std::vector<Dense<T>> normal;
        normal.reserve(n);
        for(int i = 0; i < n; i ++)
        {
            normal.push_back(A.get_column(i).eval_norm_vec(i));
        }

    }
}
#endif //SLAE_HOUSEHOLDER_H
