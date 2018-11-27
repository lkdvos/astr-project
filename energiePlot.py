filename = "SunEarthL1"
import numpy as np
import matplotlib.pyplot as plt

t, E = np.loadtxt("program/data/{}_Energy.txt".format(filename), unpack=True, skiprows=1)

#grenzen vinden
Emin = min(E)
tmin = min(t)

Emax = max(E)
tmax = max(t)

print(tmin, tmax)
print(Emin, Emax)

plt.plot()
plt.semilogy(t, E)
plt.title('relatieve Efout ifv t')

plt.show()
