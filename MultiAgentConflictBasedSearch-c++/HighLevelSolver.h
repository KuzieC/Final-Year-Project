#pragma once
#include "TreeNode.h"
#include "util.h"

/**
 * @class HighLevelSolver
 * @brief Implements the high-level search component of the Conflict-Based Search (CBS) algorithm
 * 
 * The HighLevelSolver manages the constraint tree and coordinates the overall CBS algorithm.
 * It detects conflicts between agent paths and creates new constraint tree nodes to resolve them.
 * The main responsibility is to orchestrate the interaction between conflict detection and
 * low-level path planning.
 */
class HighLevelSolver
{
private:
	/// Checks if the constraint tree is empty
	static inline bool isEmpty(const std::vector<TreeNode> &tree);
	
	/// Returns the minimum cost among all nodes in the constraint tree
	static int getMinCost(const std::vector<TreeNode> &tree);
	
	/// Finds and returns the node with the lowest cost in the constraint tree
	static TreeNode findBestNode(const std::vector<TreeNode> &tree);
	
	/// Validates the input map configuration (agents don't start/end in same positions)
	static bool CheckEverything(const Map &map);
	
	/// Counts the total number of conflicts in a given tree node
	static int calculateConflicts(TreeNode &Node, const Map &map);

public:
	HighLevelSolver();
	~HighLevelSolver();
	
	/// Detects vertex conflicts between two agent routes (same cell, same time)
	static bool hasConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj);
	
	/// Detects conflicts for all agent pairs in a tree node
	static bool hasConflict(const TreeNode &node, const Map &map);
	
	/// Detects edge conflicts between two agent routes (agents swapping positions)
	static bool hasEdgeConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj);
	
	/// Detects edge conflicts for all agent pairs in a tree node
	static bool hasEdgeConflict(const TreeNode &P, const Map &map);
	
	/// Main CBS algorithm entry point - returns optimal conflict-free paths for all agents
	static std::vector<std::vector<Cell>> solve(const Map &map);
};
