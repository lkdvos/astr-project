

# tijd x1 y1 z1 vx1 vy1 vz1 x2... xn yn zn vxn vyn vzn
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

filename = "testH/RK4test_03"

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

n = int((len(invoer[0])-1)/3) # n is number of objects.


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
        deel.append([lijn[1+i*3], lijn[2+i*3], lijn[3+i*3]])
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

ax = plt.axes(projection='3d')
ax.set_xlim(xmin, xmax)
ax.set_ylim(ymin, ymax)
ax.set_zlim(zmin, zmax)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')


punten = np.array(punten)

# Make list of colors for lines in plot.
colors = ['black', 'blue', 'red', 'green', 'yellow', 'orange', 'purple']

def update(p, *fargs):
	for i in range(n):
		print(p)
		ax.plot(punten[:p,i,0], punten[:p,i,1], punten[:p,i,2], linestyle='-', marker='None', color=colors[i], label=objects[i])

	#plt.subplots_adjust(wspace=0.3)
	if p==1 or p==-1:
		handles,labels = ax.get_legend_handles_labels()
		ax.legend(handles[0:n], labels[0:n], loc='upper center', bbox_to_anchor=(0.5, 1.12), fancybox=True, shadow=True, ncol=n)

# animatie
ani = animation.FuncAnimation(fig, update, frames = len(punten), fargs=(10,), interval = 100, blit = False, repeat = False)
#ani.save("program/animations/{}.mp4".format(filename))

# plot eindconfiguratie
#update(-1)
plt.show()
