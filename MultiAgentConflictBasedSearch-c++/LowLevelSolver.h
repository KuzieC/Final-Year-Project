#pragma once
#include <vector>
#include <set>
#include <cstdlib>
#include "TreeNode.h"
#include "util.h"
#include <unordered_map>

/**
 * @class LowLevelSolver
 * @brief Implements constraint-aware A* pathfinding for individual agents
 * 
 * The LowLevelSolver is responsible for finding optimal paths for individual agents
 * while respecting a given set of constraints. It uses A* search with modifications
 * to handle time-based constraints and support for square-shaped agents.
 * 
 * Key features:
 * - Supports both point agents (len=0) and square agents (len>0)
 * - Respects temporal constraints from the CBS algorithm
 * - Uses Manhattan distance heuristic
 * - Handles obstacles and boundary checking
 */
class LowLevelSolver
{
private:
	std::vector<std::vector<Cell>> optimalPaths;      ///< Storage for computed optimal paths
	std::vector<Cell> successorCells;                 ///< Temporary storage for successor generation
	std::vector<Cell> optimalPath;                    ///< Current optimal path being computed
	std::unordered_multimap<int,Cell> OPEN;           ///< Open list for A* (priority queue by f-value)
	std::vector<Cell> CLOSE;                          ///< Closed list for A* (visited nodes)
	int time{};                                       ///< Current time step in pathfinding
	
	/// Checks if a cell contains an obstacle
	static inline bool isObstacle(const Map &map, int x, int y);
	
	/// Checks if there's a constraint for given agent at specific position and time
	static inline bool isConstraint(int agentID, int x, int y, int time, const std::vector<Constraint> &constraints);
	
	/// Checks if there's a semi-constraint (softer constraint) for given agent at specific position and time
	static inline bool isSemiConstraint(int agentID,int x, int y, int time, const std::vector<Constraint> &constraints);
	
	/// Checks if a cell is contained in the given container (note: typo in parameter spacing)
	static inline bool contains(std	::unordered_multimap<int,Cell> cells, Cell cell);
	
	/// Checks if a cell is contained in the given vector
	static inline bool contains1(std::vector<Cell> cells, Cell cell);
	
	/// Finds the index of a cell in the given vector
	static int findIndex(std::vector<Cell> cells, Cell cell);
	
	/// Validates that start and goal positions are valid for the given agent
	static bool checkStartGoalCells(const Cell &start, const Cell &goal, const Map &map,const int agentID);
	
	/// Calculates Manhattan distance between two cells (heuristic function)
	static int findHeuristicDistance(Cell current_cell, Cell cell);
	
	/// Checks if given coordinates are within map boundaries
	static bool isValid(int x, int y, const Map &map);
	
	/// Updates the cost function (f, g, h values) for a successor cell
	static void updateCostFunction(Cell &successor, Cell goal, int time);
	
	/// Finds the cell with minimum f-value in the OPEN list
	static std::pair<int,Cell> findMinCostCell(const std::unordered_multimap<int,Cell> &OPEN);

public:
	LowLevelSolver();
	~LowLevelSolver();
	
	/// Checks if a move respects all hard constraints for the given agent
	bool checkConstraint(Cell current_cell, const Map &map, int agentID, int time,const std::vector<Constraint> constraints, int shiftx,int shifty);
	
	/// Checks if a move respects all soft constraints for the given agent  
	bool checkSemiConstraint(Cell current_cell, const Map &map, int agentID, int time,const std::vector<Constraint> constraints, int shiftx,int shifty);
	
	/// Finds optimal path for a specific agent given constraints
	std::vector<Cell> solve(const std::vector<Constraint> &constraints, std::vector<Constraint> &semiconstraints, const Map &map, int agentID);
	
	/// Finds optimal paths for all agents given constraints
	std::vector<std::vector<Cell>> findOptimalPaths(const std::vector<Constraint> &constraints, const Map &map);
};




