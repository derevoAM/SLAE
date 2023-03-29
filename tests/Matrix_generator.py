import numpy as np

mat_ = np.random.random((20, 20))

with open('mat_20.txt', 'w') as file:
    for i in range(20):
        for j in range(20):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_[i, j]))

b_ = np.random.random(20)

with open('b_20.txt', 'w') as file:
    for i in range(20):
        file.write('{:.2f}\n'.format(b_[i] * 10))




mat_5 = np.random.random((5, 5))

with open('mat_5.txt', 'w') as file:
    for i in range(5):
        for j in range(5):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_[i, j] * 10))


b_5 = np.random.random(5)

with open('b_5.txt', 'w') as file:
    for i in range(5):
        file.write('{:.2f}\n'.format(b_[i] * 10))


mat_diag_pos_20 = np.random.random((20, 20))

with open('mat_diag_pos_20.txt', 'w') as file:
    for i in range(20):
        sum = 0
        # for j in range(i + 1):
        #     sum += mat_diag_pos_20[i, j]


        for j in range(i + 1, 20):
            mat_diag_pos_20[i, j] = 0

    mat_diag_pos_20 = np.matmul(mat_diag_pos_20, np.transpose(mat_diag_pos_20))


    for i in range(20):
        sum = 0

        for j in range(20):
            sum += mat_diag_pos_20[i, j]

        mat_diag_pos_20[i, i] = sum
        for j in range(20):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_diag_pos_20[i, j] * 10))
