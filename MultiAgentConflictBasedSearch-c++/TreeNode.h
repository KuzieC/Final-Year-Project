#pragma once
#include "LowLevelSolver.h"
#include "util.h"

class TreeNode
{
private:
	int cost = 0;
	int conflicts = 0;
	std::vector<Constraint> constraints;
	std::vector<std::vector<Cell>> solution;

public:
	void addConstraint(const Constraint &constaint);
	void updateSolution(const Map &map);
	void updateCost();
	int getCost() const;
	void updateConflicts(const Map &map);
	int getConflcit() const;
	std::vector<std::vector<Cell>> getSolution() const;
	std::vector<Constraint> getConstraints() const;
	TreeNode();
	TreeNode(const std::vector<Constraint> &constraints);
	~TreeNode();
	friend bool operator==(const TreeNode &a, const TreeNode &b);
};
