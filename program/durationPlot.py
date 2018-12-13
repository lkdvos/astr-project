import numpy as np
import matplotlib.pyplot as plt

print("geef bestandsnamen (met spatie ertussen):  ")

bestanden = input().split()

plt.plot()
plt.ylabel("execution time per integration step [ms]")
plt.xlabel("N")

N = []
t = []

for bestand in bestanden:
    data = (open("program/duration/duration_" + bestand + "_RK4.txt", 'r').readline()).split()
    a = float(data[0])
    b = float(data[1])
    N.append(a), t.append(b)

plt.axis([0, max(N)+1, min(t)-10**(-5), max(t)+10**(-5)])
plt.plot(sorted(N),sorted(t), marker='o', markersize=6,label="data")
plt.show()
