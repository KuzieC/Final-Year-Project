import matplotlib.pyplot as plt
import numpy as np
import random


def random_hex_number():
    return format(random.randint(0, 16777215), '06X')


def plot_obstacle():
    for i in range(size_obstacle):
        ax.scatter(int(obstacle[i].split(",")[0]), int(
            obstacle[i].split(",")[1]), c="black", marker=".", s=2000)


f = open("data//map3.txt", "r")
diam = f.readline()
x = int(diam.split(" ")[0])
y = int(diam.split(" ")[1])
obstacles = f.readline()
obstacle = obstacles.split(" ")
size_obstacle = len(obstacle)

start = f.readline()
goal = f.readline()
size = f.readline()

starts = start.split(" ")
goals = goal.split(" ")
sizes = size.split(" ")
num = len(sizes)-1

sssx = []
sssy = []
gggx = []
gggy = []

for i in range(num):
        temp1 = int(starts[i].split(",")[0])
        temp2 = int(starts[i].split(",")[1])
        temp3 = int(goals[i].split(",")[0]) 
        temp4 = int(goals[i].split(",")[1])
        sssx.append(temp1)
        sssy.append(temp2)
        sssx.append(temp1+int(sizes[i]))
        sssy.append(temp2)
        sssx.append(temp1)
        sssy.append(temp2+int(sizes[i]))
        sssx.append(temp1+int(sizes[i]))
        sssy.append(temp2+int(sizes[i]))
        gggx.append(temp3)
        gggy.append(temp4)
        gggx.append(temp3+int(sizes[i]))
        gggy.append(temp4)
        gggx.append(temp3)
        gggy.append(temp4+int(sizes[i]))
        gggx.append(temp3+int(sizes[i]))
        gggy.append(temp4+int(sizes[i]))



round = 0
fig, ax = plt.subplots()
plt.xlim(0, x)
plt.ylim(0, y)
plt.grid(color='black', linestyle='-', linewidth=1)
plt.axis('scaled')
ax.set_xticks(np.arange(x+1))
ax.set_yticks(np.arange(y+1))
ax.set_axisbelow(True)

color = []
cc = ""
for i in range(num):
    cc = random_hex_number()
    for j in range(4):
        color.append("#"+cc)

plot_obstacle()
ax.scatter( sssx,sssy,c=color, marker=".", s=1500)
        # print(coordx[i],coordy[i])  cxcx
ax.scatter( gggx,gggy,c=color, marker=".", s=1500)
plt.show()
