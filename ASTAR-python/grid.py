from typing import Tuple
import numpy as np


class Grid:

    def __init__(self, grid_size, static_obstacles, height, length):
        self.grid_size = grid_size
        self.height = height
        self.length = length
        #self.minx, self.maxx, self.miny, self.maxy = self.calculate_boundaries(static_obstacles)
        self.minx = 0
        self.miny = 0
        self.maxx = length
        self.maxy = height
        self.grid = self.make_grid(grid_size, self.minx, self.maxx, self.miny, self.maxy, self.length, self.height)

    @staticmethod
    def calculate_boundaries(static_obstacles: np.ndarray) -> Tuple[int, int, int, int]:
        min_ = np.min(static_obstacles, axis=0)
        max_ = np.max(static_obstacles, axis=0)
        return min_[0], max_[0], min_[1], max_[1]

    @staticmethod
    def make_grid(grid_size: int, minx: int, maxx: int, miny: int, maxy: int, length, height) -> np.ndarray:
        # Calculate the size of the sides
        x_size = length // grid_size
        y_size = height // grid_size
        # Initialize the grid, assuming grid is 2D
        grid = np.zeros([y_size, x_size, 2], dtype=np.int32)
        # Fill the grid in
        y = 0 - grid_size / 2
        for i in range(y_size):
            y += grid_size
            x = 0 - grid_size / 2
            for j in range(x_size):
                x += grid_size
                grid[i][j] = np.array([x, y])
        return grid

    '''
    Snap an arbitrary position to the center of the grid
    '''

    def snap_to_grid(self, position: np.ndarray) -> np.ndarray:
        i = (position[1] - self.miny) // self.grid_size
        j = (position[0] - self.minx) // self.grid_size
        if i >= len(self.grid):
            i -= 1
        if j >= len(self.grid[0]):
            j -= 1
        return self.grid[i][j]
