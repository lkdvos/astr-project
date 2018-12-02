#===============================================================================
#------------------IMPORTS------------------------------------------------------
#===============================================================================

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

#===============================================================================
#-------------------------------------------------------------------------------
#===============================================================================

filename = "SolarSystem"
method = "VER"



frames=1
scale = 10
colors = "plasma"

invoer = np.loadtxt("program/data/{}{}.txt".format(filename, method))
n = int((len(invoer[0])-1)/6) #aantal deeltjes




transposedData = np.transpose(invoer)
N = int((len(transposedData) - 1) / 6)
print(N)

#grenzen vinden

xmins = []
xmaxs = []
for i in range(N):
    xmins.append(np.amin(transposedData[6*i + 1]))
    xmaxs.append(np.amax(transposedData[6*i + 1]))
xmin = min(xmins)
xmax = max(xmaxs)

ymins = []
ymaxs = []
for i in range(N):
    ymins.append(np.amin(transposedData[6*i + 2]))
    ymaxs.append(np.amax(transposedData[6*i + 2]))
ymin = min(ymins)
ymax = max(ymaxs)

zmins = []
zmaxs = []
for i in range(N):
    zmins.append(np.amin(transposedData[6*i+ 3]))
    zmaxs.append(np.amax(transposedData[6*i + 3]))
zmin = min(zmins)
zmax = max(zmaxs)

fig, ax = plt.subplots()
xdata, ydata, zdata = [], [], []
ax = plt.axes(projection='3d')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_facecolor((0,0,0,0.4))

def init():
    global shown
    shown = []
    ax.set_xlim(xmin, xmax)
    ax.set_ylim(ymin, ymax)
    ax.set_zlim(zmin, zmax)

    xdata, ydata, zdata = [], [], []
    for i in range(N):
        xdata.append(transposedData[6*i + 1][0])
        ydata.append(transposedData[6*i + 2][0])
        zdata.append(transposedData[6*i + 3][0])
    shown.append(ax.scatter3D(xdata, ydata, zdata, s=scale, c=np.linspace(0,1,N), cmap=colors))
    global t
    t = ax.text2D(0, 0, 't = 0 days', transform=ax.transAxes)

def update(p, *fargs):
    global t
    global shown
    t.remove()
    if len(shown) >= frames:
        shown.pop(0).remove()

    xdata, ydata, zdata = [], [], []
    for i in range(N):
        xdata.append(transposedData[6*i + 1][p])
        ydata.append(transposedData[6*i + 2][p])
        zdata.append(transposedData[6*i + 3][p])

    t = ax.text2D(0, 0, 't = {:05.2f} days'.format(transposedData[0][p]), transform=ax.transAxes)
    shown.append(ax.scatter3D(xdata, ydata, zdata, s=scale, c=np.linspace(0,1,N), cmap=colors))

ani = animation.FuncAnimation(fig, update, frames=len(transposedData[0]), fargs=(10,), interval = 10, blit=False, init_func=init)
#plt.show()
ani.save("program/movie/{}{}.mp4".format(filename, method), writer='ffmpeg')
