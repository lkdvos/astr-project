import numpy as np
import matplotlib.pyplot as plt

filenames = [
"SunEarth",
"SunEarthL1",
"SunEarthL1L2",
]

methods = [
"RK4",
"Verlet",

]



def importData(filename, method):
    t, E = np.loadtxt("program/data/{}{}_Energy.txt".format(filename, method), unpack=True, skiprows=1)
    Emin = min(E)
    tmin = min(t)

    Emax = max(E)
    tmax = max(t)
    print("imported {} with {}".format(filename, method))
    print("boundaries are: ")
    print("t [{}, {}]".format(tmin, tmax))
    print("E [{}, {}]".format(Emin, Emax))
    return (t, E, (tmin, tmax), (Emin, Emax))

def plot(filename, methods):


    plt.plot()
    subplots = len(methods)

    for i in range(subplots):
        t, E, tBounds, Ebounds = importData(filename, methods[i])
        if i == 0:
            ding = plt.subplot(1, subplots, i+1)
        else:
            plt.subplot(1, subplots, i+1, sharex=ding, sharey=ding)
        plt.semilogy(t, E)
        plt.title('{} met {}'.format(filename, methods[i]))
    plt.show()

for filename in filenames:
    plot(filename, methods)
