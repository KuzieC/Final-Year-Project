/**
 * @file TreeNode.cpp
 * @brief Implementation of constraint tree node for CBS algorithm
 * 
 * TreeNodes represent states in the CBS constraint tree. Each node
 * contains a set of constraints and the corresponding solutions
 * for all agents that respect those constraints.
 */

#include "TreeNode.h"
#include "HighLevelSolver.h"

TreeNode::TreeNode() = default;
TreeNode::~TreeNode() = default;

/**
 * @brief Returns the current solution (paths for all agents)
 * @return Vector of paths, one for each agent
 */
std::vector<std::vector<Cell>> TreeNode::getSolution() const
{
	return solution;
}

/**
 * @brief Returns the total cost of all paths in this node
 * @return Sum of all path lengths
 */
int TreeNode::getCost() const {
	return cost;
}

/**
 * @brief Returns the constraints applied to this node
 * @return Vector of constraints
 */
std::vector<Constraint> TreeNode::getConstraints() const {
	return this->constraints;
}

/**
 * @brief Constructor that initializes node with given constraints
 * @param constraints Initial set of constraints for this node
 */
TreeNode::TreeNode(const std::vector<Constraint> &constraints) {
	this->constraints = constraints;
}

/**
 * @brief Adds a new constraint to this node
 * @param constaint The constraint to add (note: parameter name has typo)
 */
void TreeNode::addConstraint(const Constraint & constaint) {
	this->constraints.emplace_back(constaint);
}

/**
 * @brief Updates the solution by running low-level pathfinding with current constraints
 * @param map The environment map with agents and obstacles
 */
void TreeNode::updateSolution(const Map &map) {
	LowLevelSolver solver;
	solution = solver.findOptimalPaths(constraints, map);
}

/**
 * @brief Recalculates the total cost based on current solution
 * 
 * Cost is computed as the sum of all path lengths.
 * Longer paths result in higher costs.
 */
void TreeNode::updateCost() {
	auto cost = 0;
	for (auto route : solution) {
		cost += route.size();
	}
	this->cost = cost;
}

/**
 * @brief Returns the number of conflicts in this node
 * @return Number of remaining conflicts (note: method name has typo)
 */
int TreeNode::getConflcit() const{
	return conflicts;
}

/**
 * @brief Recalculates the number of conflicts in the current solution
 * @param map The environment map with agent information
 * 
 * Counts both vertex conflicts and edge conflicts between all agent pairs.
 */
void TreeNode::updateConflicts(const Map &map){
	int count = 0;
	// Check all pairs of agents for conflicts
	for(int i = 0; i < solution.size();i++){
		for(int j = i+1;j<solution.size();j++){
			// Check for both vertex conflicts and edge conflicts
			if(HighLevelSolver::hasConflict(solution[i], solution[j], map.agents[i].len, map.agents[j].len)||
			   HighLevelSolver::hasEdgeConflict(solution[i], solution[j], map.agents[i].len, map.agents[j].len)){
				count++;
			}
		}
	}
	this->conflicts = count;
}

/**
 * @brief Equality operator for comparing tree nodes
 * @param lhs Left-hand side node
 * @param rhs Right-hand side node
 * @return true if nodes have same cost and solution
 */
bool operator==(const TreeNode& lhs, const TreeNode& rhs)
{
    return lhs.getCost() == rhs.getCost() &&
           lhs.getSolution()  == rhs.getSolution() ;
}