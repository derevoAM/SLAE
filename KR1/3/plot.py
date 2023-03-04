import matplotlib.pyplot as plt
import numpy as np

n = np.array([])
tau = np.array([])
with open("fpi_3.txt", "r") as f:
    for line in f:
        data = line.split(' ')
        n = np.append(n, int(data[0]))
        tau = np.append(tau, float(data[1]))



fig, ax = plt.subplots(figsize=(16, 10), dpi=150)

fig.suptitle("Dependence of the number of iterations on the residual",
             fontsize='xx-large')

plt.grid(True)

plt.xticks(np.arange(1e-5, 1e-3, 1e-4))
plt.yticks(np.arange(0, max(n), 100000))

ax.plot(tau, n)

plt.xlabel(r'$\tau$', fontsize=14)
plt.xlabel(r'Number of iterations', fontsize=14)
plt.savefig("plot_3.png")
plt.show()
