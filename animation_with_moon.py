

# tijd x1 y1 z1 vx1 vy1 vz1 x2... xn yn zn vxn vyn vzn
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

filename = "SunEarthMoonVenusRK4"

# Open datafile.
f = open("program/data/{}.txt".format(filename), "r")

invoer = []
for line in f:
	lijst = line.split()
	if lijst[0] == "#":
		# Make list of objects.
		objects = lijst

	if lijst[0][0] != "#":
		lijst = list(map(float, lijst))
		invoer.append(lijst)

objects.remove("#")
f.close()

n = int((len(invoer[0])-1)/6) # n is number of objects.


# Make list of following structure:
#[ [[x1,y1,z1][x2,y2,z2]...[xn,yn,zn]](t0)
#     [[x1,y1,y2][x2,y2,z2]...[xn,yn,zn]](t1)   ... (tn)]

print(n)


punten = []
tijd = []
for lijn in invoer[0:len(invoer)]:
    tijd.append(lijn[0])
    deel = []
    for i in range(n):
        deel.append([lijn[1+i*6], lijn[2+i*6], lijn[3+i*6]])
    punten.append(deel)
print(len(punten))

# Find boundaries of x,y,z.
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

punten = np.array(punten)

# Make list of colors for lines in plot.
colors = ['black', 'blue', 'red', 'green', 'yellow', 'orange', 'purple']

def update(p, *fargs):
	for i in range(n):
		print(p)

		ax1 = plt.subplot(131)
		ax1.set_xlim(xmin, xmax)
		ax1.set_ylim(ymin, ymax)
		ax1.set_xlabel('X')
		ax1.set_ylabel('Y')
		ax1.plot(punten[:p,i,0], punten[:p,i,1], linestyle='-', marker='None', color=colors[i], label=objects[i])

		if i==1 or i==2:
		    ax2 = plt.subplot(132)
		    ax2.plot(punten[:p,i,0] - punten[:p,1,0], punten[:p,i,1] - punten[:p,1,1], linestyle = '-', marker='None', color=colors[i], 	label='')
		    ax2.set_xlim(-0.003,0.003)
		    ax2.set_ylim(-0.003,0.003)
		    ax2.set_xlabel('X')
		    ax2.set_ylabel('Y')

		if i==3 or i==4:
		    ax3 = plt.subplot(133)
		    ax3.plot(punten[:p,i,0] - punten[:p,3,0], punten[:p,i,1] - punten[:p,3,1], linestyle = '-', marker='None', color=colors[i], label='')
		    ax3.set_xlim(-0.003,0.003)
		    ax3.set_ylim(-0.003,0.003)
		    ax3.set_xlabel('X')
		    ax3.set_ylabel('Y')

	plt.subplots_adjust(wspace=0.3)

	if (p==1 or p==-1):	# Fixing legend for plots
		handles,labels = ax1.get_legend_handles_labels()
		ax1.legend(handles[0:n], labels[0:n], loc='upper center', bbox_to_anchor=(1.5, 1.12), fancybox=True, shadow=True, ncol=n)


# animatie
ani = animation.FuncAnimation(fig, update, frames = len(punten), fargs=(10,), interval = 100, blit = False, repeat = False)
ani.save("program/animations/{}.mp4".format(filename))

# plot eindconfiguratie
update(-1)
plt.show()
