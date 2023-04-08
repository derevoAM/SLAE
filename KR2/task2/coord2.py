import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

it1 = np.array([])
res1 = np.array([])
with open('points_1') as f1:
    for line in f1:
        a, b = line.split()
        it1 = np.append(it1, float(a))
        res1 = np.append(res1, float(b))

it2 = np.array([])
res2 = np.array([])
with open('points_2') as f2:
    for line in f2:
        a, b = line.split()
        it2 = np.append(it2, float(a))
        res2 = np.append(res2, float(b))

it3 = np.array([])
res3 = np.array([])
with open('points_3') as f3:
    for line in f3:
        a, b = line.split()
        it3 = np.append(it3, float(a))
        res3 = np.append(res3, float(b))

it4 = np.array([])
res4 = np.array([])
with open('points_4') as f4:
    for line in f4:
        a, b = line.split()
        it4 = np.append(it4, float(a))
        res4 = np.append(res4, float(b))

it5 = np.array([])
res5 = np.array([])
with open('points_5') as f5:
    for line in f5:
        a, b = line.split()
        it5 = np.append(it5, float(a))
        res5 = np.append(res5, float(b))

fig, ax = plt.subplots(figsize=(16, 10), dpi=50)

fig.suptitle("Convergence",
             fontsize='xx-large')

plt.grid(True)

ax.scatter(it2, res2, s=20, color='b')
ax.scatter(it4, res4, s=20, color='y')




ax.plot(it2, res2, color='b', linestyle='--', label='FPI with tau opt')
ax.plot(it4, res4, color='y', linestyle='--', label='Chebyshev')


ax.legend(loc='best', fontsize=12)
plt.ylabel('x4', fontsize=14)
plt.xlabel('x1', fontsize=14)
plt.savefig("FPI_opt, Chebushev.png")
plt.show()