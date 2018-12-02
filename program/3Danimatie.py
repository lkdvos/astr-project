# -*- coding: utf-8 -*-
"""
Created on Wed Nov 14 22:39:28 2018

@author: Iris
"""

filename = "SolarSystem"

#tijd x1 y1 z1 vx1 vy1 vz1 x2... xn yn zn vxn vyn vzn
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation
invoer = np.loadtxt("program/data/{}.txt".format(filename))
n = int((len(invoer[0])-1)/6) #aantal deeltjes


#omvormen naar lijst van deze vorm:
#[ [[x1,y1,z1][x2,y2,z2]...[xn,yn,zn]](t0)
#     [[x1,y1,y2][x2,y2,z2]...[xn,yn,zn]](t1)   ... (tn)]

print(n)


punten = []
tijd = []
for lijn in invoer[1:500]:
    tijd.append(lijn[0])
    deel = []
    for i in range(n):
        deel.append([lijn[1+i*6], lijn[2+i*6], lijn[3+i*6]])
    punten.append(deel)
print(punten)

#grenzen vinden
xvals = []
yvals = []
zvals = []
for tijdpunt in punten:
    for deeltje in tijdpunt:
        xvals.append(deeltje[0])
        yvals.append(deeltje[1])
        zvals.append(deeltje[2])

xmin = min(xvals)
xmax = max(xvals)

ymin = min(yvals)
ymax = max(yvals)

zmin = min(zvals)
zmax = max(zvals)

print(xmin, xmax)
print(ymin, ymax)
print(zmin, zmax)



fig = plt.figure(figsize=(18,7))

"""
#Uncomment this if you want to plot an inputfile that doesn't contain Earth/Moon system and/or Jupiter/Io system.

ax = plt.axes(projection='3d')
ax.set_xlim(xmin, xmax)
ax.set_ylim(ymin, ymax)
ax.set_zlim(zmin, zmax)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
"""

punten = np.array(punten)

#Make list of colors for lines in plot.
colors = ['black', 'blue', 'red', 'green', 'yellow', 'orange', 'purple']

#Make list of all possible objects that can be plot.
objects = ['Sun', 'Earth', 'Moon', 'Jupiter', 'Io', 'Venus', 'Mars', 'Saturn', 'L1', 'L2']

def update(p, *fargs):

   
    for i in range(n):
	print p
	
	"""
	#Uncomment this if you want to plot an inputfile that doesn't contain Earth/Moon system and/or Jupiter/Io system.

	if p>0:
             ax.plot(punten[:p,i,0], punten[:p,i,1], punten[:p,i,2], linestyle='-', marker='None', color=colors[i], label=objects[i])
	if p==1:
	     ax.legend()
	"""

        """
	#Uncomment this if you want to plot an inputfile that contains Earth/Moon system and/or Jupiter/Io system.

	ax1 = plt.subplot(131)
	ax1.set_xlim(xmin, xmax)
	ax1.set_ylim(ymin, ymax)
	ax1.set_xlabel('X')
	ax1.set_ylabel('Y')
	ax1.plot(punten[:p,i,0], punten[:p,i,1], linestyle='-', marker='None', color=colors[i], label=objects[i])
	if i==1 or i==2:
	    ax2 = plt.subplot(132)
	    ax2.plot(punten[p,i,0] - punten[p,1,0], punten[p,i,1] - punten[p,1,1], marker='o', color=colors[i], label='')
	    ax2.set_xlim(-0.003,0.003)
	    ax2.set_ylim(-0.003,0.003)
	    ax2.set_xlabel('X')
	    ax2.set_ylabel('Y')
	if i==3 or i==4:
	    ax3 = plt.subplot(133)
	    ax3.plot(punten[p,i,0] - punten[p,3,0], punten[p,i,1] - punten[p,3,1], marker='o', color=colors[i], label='')
	    ax3.set_xlim(-0.003,0.003)
	    ax3.set_ylim(-0.003,0.003)
	    ax3.set_xlabel('X')
	    ax3.set_ylabel('Y')
	"""

    if p==1:
	
	"""
	#Uncomment this if you want to plot an inputfile that doesn't contain Earth/Moon system and/or Jupiter/Io system.
	
	handles,labels = ax.get_legend_handles_labels()
	ax.legend(handles[0:5], labels[0:5], loc='upper center', bbox_to_anchor=(0.5, 1.12),
	fancybox=True, shadow=True, ncol=5)
	"""

	"""
	#Uncomment this if you want to plot an inputfile that contains Earth/Moon system and/or Jupiter/Io system.

	handles,labels = ax1.get_legend_handles_labels()
        ax1.legend(handles[0:5], labels[0:5], loc='upper center', bbox_to_anchor=(0.5, 1.12),
        fancybox=True, shadow=True, ncol=5)
	"""
	


ani = animation.FuncAnimation(fig, update, frames = len(punten), fargs=(10,), interval = 100, blit = False)
plt.show()
#ani.save("program/data/{}.mp4".format(filename), writer='ffmpeg')
