import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

t = np.array([])
with open('speed') as f1:
    for line in f1:
        t = np.append(t, int(line))

lam = np.arange(-10, 800, 0.5)


fig, ax = plt.subplots(figsize=(8, 5), dpi=50)

fig.suptitle("Time from Lmax-Lmin",
             fontsize='xx-large')

plt.grid(True)
ax.scatter(lam, t)


ax.legend(loc='best', fontsize=12)
plt.ylabel('Lmax-Lmin', fontsize=14)
plt.xlabel('Time, $\mu s$', fontsize=14)
plt.savefig("T(lam).png")
plt.show()