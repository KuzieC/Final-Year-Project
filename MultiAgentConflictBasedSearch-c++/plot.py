import matplotlib.pyplot as plt
import numpy as np
import random

def random_hex_number():
    return format(random.randint(0, 16777215), '06X')
def plot_obstacle():
    for i in range (size_obstacle):
        ax.scatter(int(obstacle[i].split(".")[0]),int(obstacle[i].split(".")[1]),c = "black",marker=".",s = 2000)
f = open("result.txt","r")
diam = f.readline()
x = int(diam.split(" ")[0])
y = int(diam.split(" ")[1])
obstacles = f.readline()
obstacle = obstacles.split(" ")
size_obstacle = len(obstacle)-1

size = f.readline()
words = size.split(" ")
num = len(words) -1
paths = []
max_length = 0
for i in range (num):
    paths.append(f.readline())
    paths[i] = paths[i][0:-2]

for i in range (num):
    h = paths[i]
    length = len(h.split(" "))
    if length > max_length:
        max_length = length

coordx = [[]]
Corx = [[]]
coordy = [[]]
CorY = [[]]
i = 0
for path in paths:
    l = len(path.split(" "))
    temp = path.split(" ")[l-1]
    print(temp)
    while   l < max_length:
        paths[i] = paths[i]+ " " +temp 
        l += 1
    i+=1
for i in range (max_length):
    coordx.append([])
    #Corx.append([])
    coordy.append([])
    #CorY.append([])
print(paths)
m = 0
for path in paths:
    k = 0
    
    for j in path.split(" "):
        coordx[k].append(int(j.split(".")[0]))
        coordy[k].append(int(j.split(".")[1]))
        coordx[k].append(int(j.split(".")[0])+int(words[m]))
        coordy[k].append(int(j.split(".")[1]))
        coordx[k].append(int(j.split(".")[0]))
        coordy[k].append(int(j.split(".")[1])+int(words[m]))
        coordx[k].append(int(j.split(".")[0])+int(words[m]))
        coordy[k].append(int(j.split(".")[1])+int(words[m]))
        k += 1
    m += 1
 

round = 0
fig,ax = plt.subplots()
plt.xlim(0,x)
plt.ylim(0,y)
ax.set_xticks(np.arange(x+1))
ax.set_yticks(np.arange(y+1))
ax.set_axisbelow(True)
plt.grid(color='black', linestyle='-', linewidth=1)
plt.axis('scaled')
color = []
cc = ""
figManager = plt.get_current_fig_manager()
# figManager.resize(*figManager.window.maxsize())
for i in range (num):
    cc = random_hex_number()
    for j in range(4):
        color.append("#"+cc)
for i in range(max_length):
    plot_obstacle()
    ax.scatter(coordx[i],coordy[i],c = color,marker = ".",s = 1500)
    #print(coordx[i],coordy[i])
  
    plt.draw()
    plt.pause(0.5)  
    if i == max_length - 1:
        plt.show()                                                 #number of time per frame
    round +=1
    plt.cla()
    plt.xlim(0,x)
    plt.ylim(0,y)
    ax.set_xticks(np.arange(x+1))
    ax.set_yticks(np.arange(y+1))
    ax.set_axisbelow(True)
    plt.grid(color='black', linestyle='-', linewidth=1)

plt.show()
    # plt.xlim((0,1000))
    # plt.ylim((0,1000))
    # plt.scatter(aircraft_length, aircraft_width, color= "blue",marker= ".", s=1)
    # plt.scatter(danger_x, danger_y, color= "red",marker= ".", s=3)
    # # if k != 0:
    # #     fig.canvas.draw()

    # # else:
    # #     plt.show()
    # fig.canvas.draw()
    # plt.pause(0.2)                                                             #number of time per frame
    # #plt.cla()
    # ax.set_xticks(np.arange(0,length_airspace+length_unit,length_unit), minor=False)
    # ax.set_yticks(np.arange(0,width_airspace+width_unit,width_unit), minor=False)
    # plt.grid(color='r', linestyle='-', linewidth=0.1)
 
