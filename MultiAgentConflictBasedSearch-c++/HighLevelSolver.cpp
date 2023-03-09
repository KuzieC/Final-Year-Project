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
// normal conflict detection, four to four, leni/lenj is the side length of two square
bool HighLevelSolver::hasConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj)
{
	auto min_index = std::min(route1.size(), route2.size());
	//check for size 0 square 
	if(leni == 0){
		if(lenj == 0){
			for (int i = 0; i < min_index; i ++){
				if(route1[i] == route2[i]){
					normal = Conflict(i,i,route1[i],route2[i],i);
					return true;
				}
			}
		}
		else{
			for (int i = 0; i < min_index; i++)
			{
				Cell temp[5];
				temp[0] = Cell(route2[i].x,        route2[i].y);
				temp[1] = Cell(route2[i].x + lenj, route2[i].y);
				temp[2] = Cell(route2[i].x,        route2[i].y + lenj);
				temp[3] = Cell(route2[i].x + lenj, route2[i].y + lenj);
				temp[4] = Cell(route1[i].x       , route1[i].y);
				for (int m = 0; m < 4; m++)
				{
					for (int n = m + 1; n < 5; n++)
					{
						if (temp[m] == temp[n])
						{
							normal = Conflict(i, i, temp[m], temp[n], i);
							return true;
						}
					}
				}
			}
		}
	}
	else if(lenj == 0){
		for (int i = 0; i < min_index; i++)
			{
				Cell temp[5];
				temp[0] = Cell(route1[i].x,        route1[i].y);
				temp[1] = Cell(route1[i].x + leni, route1[i].y);
				temp[2] = Cell(route1[i].x,        route1[i].y + leni);
				temp[3] = Cell(route1[i].x + leni, route1[i].y + leni);
				temp[4] = Cell(route2[i].x       , route2[i].y);
				for (int m = 0; m < 4; m++)
				{
					for (int n = m + 1; n < 5; n++)
					{
						if (temp[m] == temp[n])
						{
							normal = Conflict(i, i, temp[m], temp[n], i);
							return true;
						}
					}
				}
			}

	}
	else {
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
	}
	return false;
}
//overloader to extract solutions from node and compare
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
//edge conflict detection, 
bool HighLevelSolver::hasEdgeConflict(const std::vector<Cell> &route1, const std::vector<Cell> &route2, int leni, int lenj)
{
	auto min_index = std::min(route1.size(), route2.size()) - 1;
	if(leni == 0){
		if(lenj == 0){
			for (int i = 0; i < min_index; i ++){
					if (route1[i] == route2[i+1] && route1[i+1] == route2[i] && route1[i] != route2[i])
					{
						edge = Conflict(0, 0, route1[i], route2[i], i);
						return true;
					}


			}
		}
		else{
			for (int i = 0; i < min_index; i++)
			{
				int j = i+1;
				Cell temp[5];
				temp[0] = Cell(route2[i].x,        route2[i].y);
				temp[1] = Cell(route2[i].x + lenj, route2[i].y);
				temp[2] = Cell(route2[i].x,        route2[i].y + lenj);
				temp[3] = Cell(route2[i].x + lenj, route2[i].y + lenj);
				temp[4] = Cell(route1[i].x       , route1[i].y);
				Cell temp1[5]; 
				temp1[0] = Cell(route2[j].x,        route2[j].y);
				temp1[1] = Cell(route2[j].x + lenj, route2[j].y);
				temp1[2] = Cell(route2[j].x,        route2[j].y + lenj);
				temp1[3] = Cell(route2[j].x + lenj, route2[j].y + lenj);
				temp1[4] = Cell(route1[j].x       , route1[j].y);
				for (int k = 0; k < 5; k++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (temp[k] == temp1[j] && temp[j] == temp1[k] && temp[k] != temp[j])
						{
							edge = Conflict(0, 0, temp[k], temp[j], i);
							return true;
						}
					}
				}
			}
		}
	}
	else if(lenj == 0){
		for (int i = 0; i < min_index ; i++)
			{
				int j = i+1;
				Cell temp[5];
				temp[0] = Cell(route1[i].x,        route1[i].y);
				temp[1] = Cell(route1[i].x + leni, route1[i].y);
				temp[2] = Cell(route1[i].x,        route1[i].y + leni);
				temp[3] = Cell(route1[i].x + leni, route1[i].y + leni);
				temp[4] = Cell(route2[i].x       , route2[i].y);
				Cell temp1[5]; 
				temp1[0] = Cell(route1[j].x,        route1[j].y);
				temp1[1] = Cell(route1[j].x + leni, route1[j].y);
				temp1[2] = Cell(route1[j].x,        route1[j].y + leni);
				temp1[3] = Cell(route1[j].x + leni, route1[j].y + leni);
				temp1[4] = Cell(route2[j].x       , route2[j].y);
				for (int k = 0; k < 5; k++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (temp[k] == temp1[j] && temp[j] == temp1[k] && temp[k] != temp[j])
						{
							edge = Conflict(0, 0, temp[k], temp[j], i);
							return true;
						}
					}
				}
			}

	}
	else{
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
					if (temp[k] == temp1[j] && temp[j] == temp1[k] && temp[k] != temp[j])
					{
						edge = Conflict(0, 0, temp[k], temp[j], i);
						return true;
					}
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

int HighLevelSolver::calculateConflicts(TreeNode &Node, const Map &map){
	auto solution = Node.getSolution();
	int count = 0;
	for(int i = 0; i < solution.size();i++){
		for(int j = i+1;j<solution.size();j++){
			if(hasConflict(solution[i], solution[j], map.agents[i].len, map.agents[j].len)||hasEdgeConflict(solution[i], solution[j], map.agents[i].len, map.agents[j].len)){
				count++;
			}
		}
	}
	return count;
}
// Conflict HighLevelSolver::getFirstConflict(const TreeNode &P)
// {
// 	auto solutions = P.getSolution();

// 	// Look for normal conflicts first
// 	for (int i = 0; i < solutions.size(); i++)
// 	{
// 		for (int j = i + 1; j < solutions.size(); j++)
// 		{
// 			auto min_index = std::min(solutions[i].size(), solutions[j].size());
// 			for (int k = 0; k < min_index; k++)
// 			{
// 				if (solutions[i][k] == solutions[j][k]) 
// 					return Conflict(i, j, solutions[i][k], solutions[i][k], k);
// 			}
// 		}
// 	}

// 	// Look for Edge Conflicts if there is no normal conflicts
// 	for (int i = 0; i < solutions.size(); i++)
// 	{
// 		for (int j = i + 1; j < solutions.size(); j++)
// 		{
// 			auto min_index = std::min(solutions[i].size(), solutions[j].size()) - 1;
// 			for (int k = 0; k < min_index; k++)
// 			{
// 				auto route1 = solutions[i];
// 				auto route2 = solutions[j];
// 				if (route1[k] == route2[k + 1] && route1[k + 1] == route2[k])
// 					return Conflict(i, j, route1[k + 1], route2[k + 1], k);
// 			}
// 		}
// 	}
// 	// Trivial. It is assured that this method is called only when there is conflict
// 	return Conflict(0, 0, Cell(0, 0), Cell(0, 0), 0);
// }

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
	/*int minConflict = 0;*/
	int minCost = 0;
	TreeNode t;
	/* for ( auto &node : tree)
	 {
	 	if (node.getConflcit() > minConflict)
	 	{
	 		minConflict = node.getConflcit();
	 		t = node;
	 	}
	 }*/
	for ( auto &node : tree)
	{
		if (node.getConflcit() > minCost)
		{
			minCost = node.getConflcit() ;
			t = node;
		}
			
	}
	return t;
}

inline bool HighLevelSolver::isEmpty(const std::vector<TreeNode> &tree)
{
	return tree.empty();
}
bool HighLevelSolver::CheckEverything(const Map &map){
	int Size = map.agents.size();
	std::vector<Cell> start;
	std::vector<Cell> goal;
	for(auto p: map.agents){
		start.push_back(p.start);
		goal.push_back(p.end);
		if(p.len != 0){
			start.push_back(Cell(p.start.x,p.start.y+p.len));
			start.push_back(Cell(p.start.x+p.len,p.start.y));
			start.push_back(Cell(p.start.x+p.len,p.start.y+p.len));
			goal.push_back(Cell(p.end.x,p.end.y+p.len));
			goal.push_back(Cell(p.end.x+p.len,p.end.y));
			goal.push_back(Cell(p.end.x+p.len,p.end.y+p.len));
		}
	}
	for(int i = 0; i < Size - 1; i ++){
		for(int j = i + 1; j < Size ; j++){
				if(start[i] == start[j]){
					return false;
				}
				if(goal[i] == goal[j]){
					return false;
				}
		}
	}
	return true;
}

std::vector<std::vector<Cell>> HighLevelSolver::solve(const Map &map)
{
	
	std::vector<TreeNode> tree;
	
	auto root = TreeNode();
	root.updateSolution(map);
	root.updateCost();
	root.updateConflicts(map);
	// std::cout<< map.agents.size()<<std::endl;
	if (root.getSolution().size() == map.agents.size())
	{
		if (!hasEdgeConflict(root, map) && !hasConflict(root, map))
		{
			return root.getSolution();
		}
		tree.emplace_back(root);
	}
	else{
		std::cout<< "no solution"<<std::endl;
		exit;
	}
	// TODO

	while (!isEmpty(tree))
	{
		TreeNode P;
		if(tree.size()!= 1){
			auto i = tree[tree.size()-1];
			auto j = tree[tree.size()-2];
			if (!hasEdgeConflict(i, map) && !hasConflict(i, map))
			{
				return i.getSolution();
			}
			if (!hasEdgeConflict(j, map) && !hasConflict(j, map))
			{
				return j.getSolution();
			}
		}
		//if(tree.size() > 1000) return std::vector<std::vector<Cell>>();
		std::cout << "size of the tree is " << tree.size() << std::endl;
	
		P = findBestNode(tree);

		for(auto o:P.getSolution()){
			for(auto j : o){
				std::cout<< j.x<<"."<<j.y<<" ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
		//std::cout << (P.getSolution())[0].size() << " " << P.getSolution()[1].size() << " " << P.getSolution()[2].size() << " " << P.getSolution()[3].size() << std::endl;
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
			std::cout<<"vertex conflict "<<conflict.cell1.x<<"."<<conflict.cell1.y<<" "<<conflict.cell2.x<<"."<<conflict.cell2.y<<" "<<conflict.time<<" "<<conflict.conflictedAgentsID.first<<" "<<conflict.conflictedAgentsID.second<<std::endl;
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
				A.updateConflicts(map);

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
			std::cout<<"edge conflict "<<conflict.cell1.x<<"."<<conflict.cell1.y<<" "<<conflict.cell2.x<<"."<<conflict.cell2.y<<" "<<conflict.time<<" "<<conflict.conflictedAgentsID.first<<" "<<conflict.conflictedAgentsID.second<<std::endl;
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
				A.updateConflicts(map);

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
