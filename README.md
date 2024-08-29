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

### Prerequisites

- C++ compiler supporting C++11 or later
- Python 3.6+
- Qt 5.12+ (optional, for UI components)

