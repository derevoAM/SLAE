import numpy as np

mat_ = np.random.random((20, 20))

with open('txt_files/mat_20.txt', 'w') as file:
    for i in range(20):
        for j in range(20):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_[i, j]))

b_ = np.random.random(20)

with open('txt_files/b_20.txt', 'w') as file:
    for i in range(20):
        file.write('{:.2f}\n'.format(b_[i] * 10))




mat_5 = np.random.random((5, 5))

with open('txt_files/mat_5.txt', 'w') as file:
    for i in range(5):
        for j in range(5):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_[i, j] * 10))


b_5 = np.random.random(5)

with open('txt_files/b_5.txt', 'w') as file:
    for i in range(5):
        file.write('{:.2f}\n'.format(b_[i] * 10))


mat_diag_pos_20 = np.random.random((20, 20))

with open('txt_files/mat_diag_pos_20.txt', 'w') as file:
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




mat_diag_pos_100 = np.random.random((100, 100))

with open('txt_files/mat_diag_pos_100.txt', 'w') as file:
    for i in range(100):
        sum = 0
        # for j in range(i + 1):
        #     sum += mat_diag_pos_20[i, j]


        for j in range(i + 1, 100):
            mat_diag_pos_100[i, j] = 0

    mat_diag_pos_100 = np.matmul(mat_diag_pos_100, np.transpose(mat_diag_pos_100))


    for i in range(100):
        sum = 0

        for j in range(100):
            sum += mat_diag_pos_100[i, j]

        mat_diag_pos_100[i, i] = sum
        for j in range(100):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_diag_pos_100[i, j] * 10))


b_100 = np.random.random(100)

with open('txt_files/b_100.txt', 'w') as file:
    for i in range(100):
        file.write('{:.2f}\n'.format(b_100[i] * 10))


mat_diag_pos_1000 = np.random.random((1000, 1000))

with open('txt_files/mat_diag_pos_1000.txt', 'w') as file:
    for i in range(1000):
        sum = 0
        # for j in range(i + 1):
        #     sum += mat_diag_pos_20[i, j]


        for j in range(i + 1, 1000):
            mat_diag_pos_1000[i, j] = 0

    mat_diag_pos_1000 = np.matmul(mat_diag_pos_1000, np.transpose(mat_diag_pos_1000))


    for i in range(1000):
        sum = 0

        for j in range(1000):
            sum += mat_diag_pos_1000[i, j]

        mat_diag_pos_1000[i, i] = sum
        for j in range(1000):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_diag_pos_1000[i, j] * 10))


b_1000 = np.random.random(1000)

with open('txt_files/b_1000.txt', 'w') as file:
    for i in range(1000):
        file.write('{:.2f}\n'.format(b_1000[i] * 10))





mat_diag_pos_5 = np.random.random((5, 5))

with open('txt_files/mat_diag_pos_5.txt', 'w') as file:
    for i in range(5):
        sum = 0
        # for j in range(i + 1):
        #     sum += mat_diag_pos_20[i, j]


        for j in range(i + 1, 5):
            mat_diag_pos_5[i, j] = 0

    mat_diag_pos_5 = np.matmul(mat_diag_pos_5, np.transpose(mat_diag_pos_5))


    for i in range(5):
        sum = 0

        for j in range(5):
            sum += mat_diag_pos_5[i, j]

        mat_diag_pos_5[i, i] = sum
        for j in range(5):
            file.write('{} {} {:.3f} \n'.format(i, j, mat_diag_pos_5[i, j] * 10))


b_5 = np.random.random(5)

with open('txt_files/b_5.txt', 'w') as file:
    for i in range(5):
        file.write('{:.2f}\n'.format(b_5[i] * 10))