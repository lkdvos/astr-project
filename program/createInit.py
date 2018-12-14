import numpy as np

N = 3
G = 1
tscale = 2898713210.51
M = 1000
filename = "test"
outputLocation = "program/init/testH/"

def initFile(filename, N, G, tscale):
    f = open("{}{}.txt".format(outputLocation, filename), 'w')
    f.write(str(N))
    f.write('\n')
    f.write(str(G))
    f.write('\n')
    f.write(str(tscale))
    f.write('\n')
    f.close()
    return

def writeParticles(filename, N):
    deeltjes = np.random.rand(N, 6)
    f = open("{}{}.txt".format(outputLocation, filename), 'a')
    for i in range(N):
        for j in range(6):
            if j >= 3:
                deeltjes[i][j] *= 100
            f.write(str(deeltjes[i][j]))
            f.write("\t")
        f.write("{} Deeltje{}\n".format(str(M), str(i)))
    f.close()
    return

def writeHValues(filename, h, endTime, printInterval):
    f = open("{}{}.txt".format(outputLocation, filename), 'a')
    f.write("{}\t{}\t{}".format(h, endTime, printInterval))
    f.close()
    return

def writeFile(filename, N, G, tscale, h, endTime, printInterval):
    initFile(filename, N, G, tscale)
    writeParticles(filename, N)
    writeHValues(filename, h, endTime, printInterval)

for n in range(6):
    h = 10**(-1*n)
    printInterval = 10**(n)
    endTime = 1000
    writeFile("{}_{:0>2d}".format(filename,n), N, G, tscale, h, endTime, printInterval)
