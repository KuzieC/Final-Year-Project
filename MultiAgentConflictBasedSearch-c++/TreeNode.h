#pragma once
#include "LowLevelSolver.h"
#include "util.h"

/**
 * @class TreeNode
 * @brief Represents a node in the CBS constraint tree
 * 
 * Each TreeNode contains:
 * - A set of constraints that apply to this node
 * - Solutions (paths) for all agents respecting these constraints
 * - The total cost of all paths
 * - The number of remaining conflicts
 * 
 * TreeNodes form a tree structure where each child adds one additional constraint
 * to resolve a conflict detected in the parent node.
 */
class TreeNode
{
private:
	int cost = 0;                                    ///< Total cost of all agent paths
	int conflicts = 0;                               ///< Number of conflicts remaining in this node
	std::vector<Constraint> constraints;             ///< Set of constraints applied to this node
	std::vector<std::vector<Cell>> solution;         ///< Paths for all agents satisfying the constraints

public:
	/// Adds a new constraint to this node
	void addConstraint(const Constraint &constaint);
	
	/// Updates the solution by running low-level pathfinding with current constraints
	void updateSolution(const Map &map);
	
	/// Recalculates the total cost based on current solution
	void updateCost();
	
	/// Returns the total cost of all paths in this node
	int getCost() const;
	
	/// Recalculates the number of conflicts in the current solution
	void updateConflicts(const Map &map);
	
	/// Returns the number of conflicts in this node (note: typo in method name)
	int getConflcit() const;
	
	/// Returns the current solution (paths for all agents)
	std::vector<std::vector<Cell>> getSolution() const;
	
	/// Returns the constraints applied to this node
	std::vector<Constraint> getConstraints() const;
	
	/// Default constructor - creates root node with no constraints
	TreeNode();
	
	/// Constructor that initializes node with given constraints
	TreeNode(const std::vector<Constraint> &constraints);
	
	~TreeNode();
	
	/// Equality operator for comparing tree nodes
	friend bool operator==(const TreeNode &a, const TreeNode &b);
};
