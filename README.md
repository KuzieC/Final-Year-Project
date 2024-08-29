# Multi-Agent Pathfinding with Formation (MAPF-F)

## Project Overview

This project focuses on solving the **Multi-Agent Pathfinding with Formation** (MAPF-F) problem, which is an extension of the standard Multi-Agent Pathfinding (MAPF) problem. In MAPF-F, multiple agents must maintain a fixed formation while navigating through a given environment, often to transport large objects that single agents cannot carry alone.

The solution adapts the Conflict-Based Search (CBS) algorithm, adding specialized handling for maintaining formation during movement and resolving conflicts when agents are part of a group.

## Features

- **Formation Maintenance**: Ensures that a group of agents maintains a specific formation (e.g., square or diamond) while navigating.
- **Collision Avoidance**: Extends CBS to handle vertex and swap conflicts for both individual agents and groups in formation.
- **Customizable Agent Groups**: Allows for the definition of different group sizes and formations.

## Technologies Used

- **C++**: The core algorithm is implemented in C++ for performance.
- **Python**: Used for visualization and additional utilities.
- **Qt**: For developing the user interface (optional).

## Usuage
- ./mapf_f --map mapfile.txt --agents agentsfile.txt --formation square
## Project Files and Structure

### Data Folder

The `Data` folder contains the map files used by the algorithm. Each map file is structured as follows:
1. **First Line**: Defines the size of the map. For example, `11 11` represents an 11x11 grid.
2. **Second Line**: Lists the coordinates of static obstacles within the map.
3. **Third Line**: Specifies the starting location of each agent group.
4. **Fourth Line**: Indicates the goal location of each agent group.
5. **Fifth Line**: Defines the size of each agent group.

### Main Files

- **`Main.cpp`**: This is the main file containing the entry point for the program. It reads a map file and translates it into a map class object, then executes the pathfinding algorithm. After execution, the results are written to `result.txt`, and the time taken for each run is logged in `statistic.txt`. These statistics can be used for further analysis, such as generating box charts.

### Plotting Scripts

- **`plot.py`**: This script plots the movement of agents based on the results in `result.txt`.
- **`plotBox.py`**: This script generates a box chart using the data in `statistic.txt`, which is useful for analyzing the performance and time taken for different runs.
- **`ploystartgoal.py`**: This script visualizes the map, including obstacles, starting locations, and goal locations from the `map.txt` file. It helps users perform a visual check for potential conflicts before running the program.



### Prerequisites

- C++ compiler supporting C++11 or later
- Python 3.6+
- Qt 5.12+ (optional, for UI components)

