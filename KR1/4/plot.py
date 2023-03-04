import matplotlib.pyplot as plt
import numpy as np

n_fpi = np.array([])
r_fpi = np.array([])
with open("fpi.txt", "r") as f:
    i = 0
    for line in f:
        data = line.split(' ')
        r_fpi = np.append(r_fpi, np.log(float(data[0])))
        n_fpi = np.append(n_fpi, data[1])
        if i > 100:
            break
        else:
            i += 1


n_gaus = np.array([])
r_gaus = np.array([])
with open("gaus.txt", "r") as f:
    for line in f:
        data = line.split(' ')
        r_gaus = np.append(r_gaus, np.log(float(data[0])))
        n_gaus = np.append(n_gaus, data[1])


n_jac = np.array([])
r_jac = np.array([])
with open("jacobi.txt", "r") as f:
    for line in f:
        data = line.split(' ')
        r_jac = np.append(r_jac, np.log(float(data[0])))
        n_jac = np.append(n_jac, data[1])


fig, ax = plt.subplots(figsize=(16, 10), dpi=150)

fig.suptitle("Dependence of th logarithm of residual on the number of iterations",
             fontsize='xx-large')

plt.grid(True)

plt.xticks(np.arange(-1, 100, 5))


ax.plot(n_fpi, r_fpi, label='FIP')
ax.plot(n_gaus, r_gaus, label='Gaus-Zeidel')
ax.plot(n_jac, r_jac, label='Jacobi')
ax.legend(loc='best', fontsize=12)
plt.xlabel('n', fontsize=14)
plt.savefig("plot.png")
plt.show()
