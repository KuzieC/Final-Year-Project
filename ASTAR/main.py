from planner import Planner
from plot import plot


def main():
    length = 52
    height = 32
    grid_size = 2
    robot_radius = 4
    map1 = [(11, 1), (11, 3), (11, 5), (11, 7), (11, 9), (11, 11), (11, 13), (11, 15), (11, 17), (11, 19),
            (11, 21),
            (13, 1), (13, 3), (13, 5), (13, 7), (13, 9), (13, 11), (13, 13), (13, 15), (13, 17),
            (13, 19), (13, 21),
            (15, 11), (17, 11), (19, 11), (21, 11), (23, 11), (25, 11), (27, 11), (29, 11), (31, 11),
            (33, 11), (35, 11), (37, 11), (39, 11), (41, 11),
            (39, 13), (41, 13), (39, 15), (41, 15), (39, 17), (41, 17), (39, 19), (41, 19), (39, 21), (41, 21),
            (25, 23), (25, 25), (25, 27), (25, 29), (25, 31),
            (27, 23), (27, 25), (27, 27), (27, 29), (27, 31)]


    p = Planner(grid_size, robot_radius, length, height, map1)
    path1 = p.plan((5, 7), (19,5), {0: {(0, 0)}})
    path2 = p.plan((19, 5), (5,7), {0: {(0, 0)}})
    plot(length, height, grid_size, path1, map1)
    plot(length, height, grid_size, path2, map1)


main()
