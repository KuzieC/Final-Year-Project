#pragma once
#include "TreeNode.h"
#include "util.h"

class HighLevelSolver
{
private:
	static inline bool isEmpty(const std::vector<TreeNode> &tree);
	static int getMinCost(const std::vector<TreeNode> &tree);
	static TreeNode findBestNode(const std::vector<TreeNode> &tree);
	static bool CheckEverything(const Map &map);
	static int calculateConflicts(TreeNode &Node, const Map &map);

public:
	HighLevelSolver();
	~HighLevelSolver();
	static bool hasConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj);
	static bool hasConflict(const TreeNode &node, const Map &map);
	static bool hasEdgeConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj);
	static bool hasEdgeConflict(const TreeNode &P, const Map &map);
	static std::vector<std::vector<Cell>> solve(const Map &map);
};
