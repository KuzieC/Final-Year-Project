#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @file util.h
 * @brief Core data structures for Multi-Agent Conflict-Based Search (CBS) algorithm
 * 
 * This file contains the fundamental structures used throughout the CBS implementation:
 * - Cell: Represents a grid cell in the environment
 * - Agent: Represents an agent with start/goal positions and size
 * - Conflict: Represents conflicts between agent paths
 * - Constraint: Represents constraints added to resolve conflicts
 * - Map: Represents the environment grid and agent configuration
 */

/**
 * @struct Cell
 * @brief Represents a single cell in the grid environment
 * 
 * Used for A* pathfinding and conflict detection. Contains position information
 * and pathfinding-specific data (f, g, h values).
 */
struct Cell {
	bool isObstacle = false;    ///< True if this cell contains an obstacle
	int x, y;                   ///< Grid coordinates (x, y)
	int f = 0, g = 0, h = 0;    ///< A* pathfinding values: f=g+h, g=cost from start, h=heuristic to goal
	Cell *parent;               ///< Parent cell for path reconstruction in A*
	
	Cell() = default;
	Cell(int x, int y) : x(x), y(y) { }

	/// Two cells are equal if their coordinates are the same
	bool operator==(const Cell& other) const {
		return x == other.x && y == other.y;
	}
	
	bool operator!=(const Cell& other) const {
		return x != other.x || y != other.y;
	}

	/// Assignment operator for copying cell data
	Cell operator=(const Cell & rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		f = rhs.f;
		g = rhs.g;
		h = rhs.h;
		isObstacle = rhs.isObstacle;
		return *this;
	}
};

/**
 * @struct Agent
 * @brief Represents an agent in the multi-agent pathfinding problem
 * 
 * Each agent has a unique ID, start position, goal position, and size.
 * The 'len' parameter defines the side length of the square-shaped agent.
 */
struct Agent {
	int id;                     ///< Unique identifier for this agent
	Cell start = Cell(0, 0);    ///< Starting position of the agent
	Cell end = Cell(0, 0);      ///< Goal position of the agent
	int len;                    ///< Side length of the square agent (0 for point agents)
	
	Agent(int id) : id(id) {
		// Constructor initializes agent with given ID
	}
};

/**
 * @struct Conflict
 * @brief Represents a conflict between two agents at a specific time
 * 
 * Conflicts occur when two agents occupy the same cell at the same time,
 * or when they attempt to swap positions (edge conflict).
 */
struct Conflict {
	std::pair<int, int> conflictedAgentsID;  ///< IDs of the two conflicting agents (ai, aj)
	Cell cell1;                              ///< First conflicting cell position
	Cell cell2;                              ///< Second conflicting cell position (for edge conflicts)
	int time;                                ///< Time step when the conflict occurs
	
	Conflict(int firstAgentID, int secondAgentID, Cell cell1, Cell cell2, int time) :
		cell1(cell1), cell2(cell2), time(time) {
		conflictedAgentsID = std::make_pair(firstAgentID, secondAgentID);
	}
};

/**
 * @struct Constraint
 * @brief Represents a constraint added to resolve conflicts
 * 
 * Constraints prohibit a specific agent from occupying a specific cell at a specific time.
 * They are added to the constraint tree during the CBS algorithm execution.
 */
struct Constraint {
	Cell cell;     ///< The cell that is constrained
	int agentID;   ///< The agent that is constrained from using this cell
	int time;      ///< The time step when the constraint applies
	
	// Constructor with proper initialization order to match member declaration order
	Constraint(int agentID, Cell cell, int time) :
		cell(cell), agentID(agentID), time(time) { }
};

/**
 * @struct Map
 * @brief Represents the environment and agent configuration
 * 
 * Contains the grid layout with obstacles and the list of agents to be planned for.
 */
struct Map {
	std::vector<std::vector<Cell>> cells;  ///< 2D grid representing the environment
	std::vector<Agent> agents;             ///< List of all agents in the problem
};


