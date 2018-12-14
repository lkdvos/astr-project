import numpy as np
import matplotlib.pyplot as plt

filenames = [
"test_00",
"test_01",
"test_02",
"test_03",
]

methods = [
"RK4",
"ERK",
"VER",
"FR"

]



def importData(filename, method):
    t, E = np.loadtxt("program/dataEnergy/testH/{}{}.txt".format(method, filename), unpack=True, skiprows=1)
    Emin = min(E)
    tmin = min(t)

    Emax = max(E)
    tmax = max(t)
    print("imported {} with {}".format(filename, method))
    print("boundaries are: ")
    print("t [{}, {}]".format(tmin, tmax))
    print("E [{}, {}]".format(Emin, Emax))
    return (t, E, (tmin, tmax), (Emin, Emax))

def plot(filenames, methods):


    plt.plot()
    subplots = len(methods)

    for i in range(subplots):
        for j in range(len(filenames)):
            t, E, tBounds, Ebounds = importData(filenames[j], methods[i])
            if i == 0 and j == 0:
                ding = plt.subplot(1, subplots, i+1)
            else:
                plt.subplot(1, subplots, i+1, sharex=ding, sharey=ding)
                plt.semilogy(t, E)
        plt.title('{} met {}'.format("test", methods[i]))
    plt.show()

plot(filenames, methods)
