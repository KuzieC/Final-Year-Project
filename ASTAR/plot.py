import matplotlib.pyplot as plt
import numpy as np
from numpy import ndarray


def plot(length: int, height: int, grid_size: int, path: ndarray, mapp: list[tuple[int, int]]):
    fig, ax = plt.subplots()
    ax.set_xticks(np.arange(0, length + grid_size, grid_size), minor=False)
    ax.set_yticks(np.arange(0, height + grid_size, grid_size), minor=False)
    plt.grid(color='r', linestyle='-', linewidth=0.1)
    obst_x = []
    obst_y = []
    for i in mapp:
        obst_x.append(i[0])
        obst_y.append(height - i[1])
    for loc in path:
        plt.xlim(0, length)
        plt.ylim(0, height)
        plt.scatter(obst_x, obst_y, color="blue", marker=".", s=2000)
        plt.scatter(loc[0], height - loc[1], color="green", marker=".", s=2000)
        plt.scatter(loc[0]+grid_size, height - loc[1], color="green", marker=".", s=2000)
        plt.scatter(loc[0]-grid_size, height - loc[1], color="green", marker=".", s=2000)
        plt.scatter(loc[0], height - loc[1]+grid_size, color="green", marker=".", s=2000)
        plt.scatter(loc[0], height - loc[1]-grid_size, color="green", marker=".", s=2000)
        plt.scatter(loc[0]+grid_size, height - loc[1]+grid_size, color="green", marker=".", s=2000)
        plt.scatter(loc[0]+grid_size, height - loc[1]-grid_size, color="green", marker=".", s=2000)
        plt.scatter(loc[0]-grid_size, height - loc[1]+grid_size, color="green", marker=".", s=2000)
        plt.scatter(loc[0]-grid_size, height - loc[1]-grid_size, color="green", marker=".", s=2000)
        # # if k != 0:
        # #     fig.canvas.draw()

        # # else:
        # #     plt.show()
        fig.canvas.draw()
        plt.pause(0.1)  # number of time per frame
        plt.cla()
        ax.set_xticks(np.arange(0, length + grid_size, grid_size), minor=False)
        ax.set_yticks(np.arange(0, height + grid_size, grid_size), minor=False)
        plt.grid(color='r', linestyle='-', linewidth=0.1)
