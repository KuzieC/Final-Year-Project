#include "HighLevelSolver.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
HighLevelSolver::HighLevelSolver() = default;
HighLevelSolver::~HighLevelSolver() = default;

Conflict normal(0, 0, Cell(0, 0), Cell(0, 0), 0);
Conflict edge(0, 0, Cell(0, 0), Cell(0, 0), 0);

// Returns true if there is a conflict between two given routes
bool HighLevelSolver::hasConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj)
{
	auto min_index = std::min(route1.size(), route2.size());
	for (int i = 0; i < min_index; i++)
	{
		Cell temp[8];
		temp[0] = Cell(route1[i].x,        route1[i].y);
		temp[1] = Cell(route1[i].x + leni, route1[i].y);
		temp[2] = Cell(route1[i].x,        route1[i].y + leni);
		temp[3] = Cell(route1[i].x + leni, route1[i].y + leni);
		temp[4] = Cell(route2[i].x,        route2[i].y);
		temp[5] = Cell(route2[i].x + lenj, route2[i].y);
		temp[6] = Cell(route2[i].x,        route2[i].y + lenj);
		temp[7] = Cell(route2[i].x + lenj, route2[i].y + lenj);
		for (int m = 0; m < 7; m++)
		{
			for (int n = m + 1; n < 8; n++)
			{
				if (temp[m] == temp[n])
				{
					normal = Conflict(i, i, temp[m], temp[n], i);
					return true;
				}
			}
		}
	}
	return false;
}

bool HighLevelSolver::hasConflict(const TreeNode &node, const Map &map)
{
	auto solutions = node.getSolution();
	for (int i = 0; i < solutions.size(); i++)
	{
		for (int j = i + 1; j < solutions.size(); j++)
		{
			if (hasConflict(solutions[i], solutions[j], map.agents[i].len, map.agents[j].len))
			{
				normal = Conflict(i, j, normal.cell1, normal.cell2, normal.time);
				return true;
			}
		}
	}
	return false;
}

// Returns true if there is an edge conflict between two routes.
bool HighLevelSolver::hasEdgeConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj)
{
	auto min_route_size = std::min(route1.size(), route2.size()) - 1;
	for (int i = 0; i < min_route_size; i++)
	{
		Cell temp[8];
		temp[0] = Cell(route1[i].x,        route1[i].y);
		temp[1] = Cell(route1[i].x + leni, route1[i].y);
		temp[2] = Cell(route1[i].x,        route1[i].y + leni);
		temp[3] = Cell(route1[i].x + leni, route1[i].y + leni);
		temp[4] = Cell(route2[i].x,        route2[i].y);
		temp[5] = Cell(route2[i].x + lenj, route2[i].y);
		temp[6] = Cell(route2[i].x,        route2[i].y + lenj);
		temp[7] = Cell(route2[i].x + lenj, route2[i].y + lenj);
		Cell temp1[8];
		temp1[0] = Cell(route1[i + 1].x,        route1[i + 1].y);
		temp1[1] = Cell(route1[i + 1].x + leni, route1[i + 1].y);
		temp1[2] = Cell(route1[i + 1].x,        route1[i + 1].y + leni);
		temp1[3] = Cell(route1[i + 1].x + leni, route1[i + 1].y + leni);
		temp1[4] = Cell(route2[i + 1].x,        route2[i + 1].y);
		temp1[5] = Cell(route2[i + 1].x + lenj, route2[i + 1].y);
		temp1[6] = Cell(route2[i + 1].x,        route2[i + 1].y + lenj);
		temp1[7] = Cell(route2[i + 1].x + lenj, route2[i + 1].y + lenj);
		for (int k = 0; k < 8; k++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (temp[k] == temp1[j] && temp[j] == temp1[k])
				{
					edge = Conflict(0, 0, temp[k], temp[j], i);
					return true;
				}
			}
		}
	}
	return false;
}

bool HighLevelSolver::hasEdgeConflict(const TreeNode &node, const Map &map)
{
	auto solutions = node.getSolution();

	for (int i = 0; i < solutions.size(); i++)
	{
		for (int j = i + 1; j < solutions.size(); j++)
		{
			if (hasEdgeConflict(solutions[i], solutions[j], map.agents[i].len, map.agents[j].len))
			{
				edge = Conflict(i, j, edge.cell1, edge.cell2, edge.time);
				return true;
			}
		}
	}
	return false;
}

Conflict HighLevelSolver::getFirstConflict(const TreeNode &P)
{
	auto solutions = P.getSolution();

	// Look for normal conflicts first
	for (int i = 0; i < solutions.size(); i++)
	{
		for (int j = i + 1; j < solutions.size(); j++)
		{
			auto min_index = std::min(solutions[i].size(), solutions[j].size());
			for (int k = 0; k < min_index; k++)
			{
				if (solutions[i][k] == solutions[j][k])
					return Conflict(i, j, solutions[i][k], solutions[i][k], k);
			}
		}
	}

	// Look for Edge Conflicts if there is no normal conflicts
	for (int i = 0; i < solutions.size(); i++)
	{
		for (int j = i + 1; j < solutions.size(); j++)
		{
			auto min_index = std::min(solutions[i].size(), solutions[j].size()) - 1;
			for (int k = 0; k < min_index; k++)
			{
				auto route1 = solutions[i];
				auto route2 = solutions[j];
				if (route1[k] == route2[k + 1] && route1[k + 1] == route2[k])
					return Conflict(i, j, route1[k + 1], route2[k + 1], k);
			}
		}
	}
	// Trivial. It is assured that this method is called only when there is conflict
	return Conflict(0, 0, Cell(0, 0), Cell(0, 0), 0);
}

// Returns min cost on tree
int HighLevelSolver::getMinCost(const std::vector<TreeNode> &tree)
{
	int min = INT_MAX;

	for (const auto &node : tree)
	{
		if (node.getCost() < min)
			min = node.getCost();
	}
	return min;
}

// Returns first node with minCost
TreeNode HighLevelSolver::findBestNode(const std::vector<TreeNode> &tree)
{
	auto minCost = getMinCost(tree);
	for (const auto &node : tree)
	{
		if (node.getCost() == minCost)
			return node;
	}
	return TreeNode();
}

inline bool HighLevelSolver::isEmpty(const std::vector<TreeNode> &tree)
{
	return tree.empty();
}

std::vector<std::vector<Cell>> HighLevelSolver::solve(const Map &map)
{
	std::vector<TreeNode> tree;

	auto root = TreeNode();
	root.updateSolution(map);
	root.updateCost();
	// std::cout<< map.agents.size()<<std::endl;
	if (root.getSolution().size() == map.agents.size())
	{
		tree.emplace_back(root);
	}
	// TODO

	while (!isEmpty(tree))
	{
		TreeNode P;
		for (auto i : tree)
		{
			if (!hasEdgeConflict(i, map) && !hasConflict(i, map))
			{
				return i.getSolution();
			}
		}
		std::cout << "size of the tree is " << tree.size() << std::endl;

		P = findBestNode(tree);
		std::cout << (P.getSolution())[0].size() << " " << P.getSolution()[1].size() << " " << P.getSolution()[2].size() << " " << P.getSolution()[3].size() << std::endl;
		int p = 0;
		// Remove current node from tree because it has conflicts.
		for (auto i : tree)
		{
			if (i == P)
			{
				tree.erase(tree.begin() + p);
				break;
			}
			p++;
		}

		if (hasConflict(P, map))
		{
			auto conflict = normal;

			for (int i = 0; i < 2; i++)
			{

				// Initialize new node with current nodes constraints
				TreeNode A(P.getConstraints());

				auto newConstraint = Constraint(conflict.conflictedAgentsID.first, conflict.cell1, conflict.time);

				if (i == 1)
				{
					newConstraint = Constraint(conflict.conflictedAgentsID.second, conflict.cell2, conflict.time);
				}

				// Add new constraint, solve with low level solver and update cost

				A.addConstraint(newConstraint);
				A.updateSolution(map);
				A.updateCost();

				// If a solution found, push it to the tree
				if (A.getSolution().size() == map.agents.size())
				{
					if (A.getCost() < INT_MAX)
					{
						tree.emplace_back(A);
					}
				}
			}
		}

		else if (hasEdgeConflict(P, map))
		{
			auto conflict = edge;
			// Remove current node from tree because it has conflicts.

			for (int i = 0; i < 2; i++)
			{

				// Initialize new node with current nodes constraints
				TreeNode A(P.getConstraints());

				auto newConstraint = Constraint(conflict.conflictedAgentsID.first, conflict.cell1, conflict.time + 1);
				auto constrain2 = Constraint(conflict.conflictedAgentsID.first, conflict.cell2, conflict.time + 1);
				// auto constrain3 = Constraint(conflict.conflictedAgentsID.first, conflict.cell1, conflict.time);
				// auto constrain4 = Constraint(conflict.conflictedAgentsID.first, conflict.cell2, conflict.time+1 );
				if (i == 1)
				{
					newConstraint = Constraint(conflict.conflictedAgentsID.second, conflict.cell2, conflict.time + 1);
					constrain2 = Constraint(conflict.conflictedAgentsID.second, conflict.cell1, conflict.time + 1);
					// constrain3 = Constraint(conflict.conflictedAgentsID.second, conflict.cell1, conflict.time+1);
					// constrain4 = Constraint(conflict.conflictedAgentsID.second, conflict.cell2, conflict.time);
				}

				// Add new constraint, solve with low level solver and update cost

				A.addConstraint(newConstraint);
				A.addConstraint(constrain2);
				// A.addConstraint(constrain3);
				// A.addConstraint(constrain4);
				A.updateSolution(map);
				A.updateCost();

				// If a solution found, push it to the tree
				if (A.getSolution().size() == map.agents.size())
				{
					if (A.getCost() < INT_MAX)
					{
						tree.emplace_back(A);
					}
				}
			}
		}

		// return std::vector<std::vector<Cell>>();
	}
	std::cout << "no solution" << std::endl;
	// Return empty vector if there is no solution.

	return std::vector<std::vector<Cell>>();
}
