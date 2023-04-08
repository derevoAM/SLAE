import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

it1 = np.array([])
res1 = np.array([])
with open('des_1') as f1:
    for line in f1:
        a, b = line.split()
        it1 = np.append(it1, int(a) - 1)
        res1 = np.append(res1, float(b))

it2 = np.array([])
res2 = np.array([])
with open('des_2') as f2:
    for line in f2:
        a, b = line.split()
        it2 = np.append(it2, int(a) - 1)
        res2 = np.append(res2, float(b))

it3 = np.array([])
res3 = np.array([])
with open('des_3') as f3:
    for line in f3:
        a, b = line.split()
        it3 = np.append(it3, int(a))
        res3 = np.append(res3, float(b))

it4 = np.array([])
res4 = np.array([])
with open('des_4') as f4:
    for line in f4:
        a, b = line.split()
        it4 = np.append(it4, int(a))
        res4 = np.append(res4, float(b))



fig, ax = plt.subplots(figsize=(8, 5), dpi=50)

fig.suptitle("Log of residual from iterations number",
             fontsize='xx-large')

plt.grid(True)

ax.set_yscale('log')
ax.scatter(it1, res1, s=20, color='r')
ax.scatter(it2, res2, s=20, color='b')
ax.scatter(it3, res3, s=20, color='g')
ax.scatter(it4, res4, s=20, color='y')



ax.plot(it1, res1, color='r', linestyle='--', label='FPI')
ax.plot(it2, res2, color='b', linestyle='--', label='FPI with tau opt')
ax.plot(it3, res3, color='g', linestyle='--', label='Chebyshev')
ax.plot(it4, res4, color='y', linestyle='--', label='SSOR')

ax.legend(loc='best', fontsize=12)
plt.ylabel('log(r)', fontsize=14)
plt.xlabel('N', fontsize=14)
plt.savefig("r(N).png")
plt.show()