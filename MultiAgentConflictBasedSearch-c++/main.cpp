

#include <chrono>
#include "LowLevelSolver.h"
#include "HighLevelSolver.h"

std::vector<std::string> split(std::string s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}
	return result;
}

Map readMap(std::string filename)
{

	Map map; // Grid map
	int row, col;

	std::ifstream infile(filename);
	std::string line;
	std::string line2;
	std::string line3;
	getline(infile, line);

	auto splitted = split(line, ' ');
	col = std::stoi(splitted[0]);
	row = std::stoi(splitted[1]);

	getline(infile, line);

	// split second line to get obstacles
	std::istringstream k(line);
	std::string s;

	std::vector<std::vector<Cell>> cells;

	for (int i = 0; i < row; i++)
	{

		std::vector<Cell> row_;
		for (int j = 0; j < col; j++)
		{
			Cell n(j, i);
			n.isObstacle = false;
			row_.emplace_back(n);
		}
		cells.emplace_back(row_);
	};

	while (getline(k, s, ' '))
	{
		auto splitted = split(s, ',');
		int x = std::stoi(splitted[0]);
		int y = std::stoi(splitted[1]);
		// std:: cout<<x<<y<<std::endl;
		cells[x][y].isObstacle = true;
	}

	// next lines are agents. start1 start2
	int start, end;

	std::vector<Agent> agents;

	int agentID = 0;
	getline(infile, line);
	getline(infile, line2);
	getline(infile, line3);
	k.clear();
	s = ' ';
	std::istringstream k1(line);
	std::istringstream k2(line2);
	std::istringstream k3(line3);
	std::string s2;
	std::string s3;
	while (getline(k1, s, ' '))
	{
		Agent agent(agentID);
		getline(k2, s2, ' ');
		getline(k3, s3, ' ');
		auto splitted = split(s, ',');
		auto splitted2 = split(s2, ',');

		int startx = std::stoi(splitted[0]);
		int starty = std::stoi(splitted[1]);
		int endx = std::stoi(splitted2[0]);
		int endy = std::stoi(splitted2[1]);
		agent.len = std::stoi(s3);
		agent.start = Cell(startx, starty);
		agent.end = Cell(endx, endy);
		agents.emplace_back(agent);
		agentID++;
	}

	map.cells = cells;
	map.agents = agents;

	return map;
}

void printMap(Map map)
{
	std::cout << map.cells.size() << " " << map.cells[0].size() << std::endl;
	for (int i = 0; i < map.cells.size(); i++)
	{
		for (int j = 0; j < map.cells[0].size(); j++)
		{
			if (map.cells[j][i].isObstacle == true)
				std::cout << "X";
			else
				std::cout << "_";
		}
		std::cout << std::endl;
	}
}

void printAgents(Map map)
{
	for (int i = 0; i < map.agents.size(); i++)
	{
		std::cout << map.agents[i].start.y;
	}
}

void testLowLevel(Map map)
{
	LowLevelSolver solver;
	auto x = solver.findOptimalPaths(std::vector<Constraint>(), map);

	std::cout << x.size();
	for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < x[0].size(); j++)
		{
			std::cout << x[i][j].x << "," << x[i][j].y << std::endl;
		}
	}
}

unsigned int Factorial(unsigned int number)
{
	return number <= 1 ? number : Factorial(number - 1) * number;
}

void printSolution(std::vector<std::vector<Cell>> optimalPaths)
{
	int k = 0;
	for (auto path : optimalPaths)
	{

		std::cout << "Optimal path of agent" << k++ << "\n";
		for (auto cell : path)
		{
			std::cout << cell.x << cell.y << "\n";
			// std::cout << "aaa";
		}
	}
}

int main()
{
	auto started = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<Cell>> optimalPaths;
	Map map = readMap("data\\map.txt");
	printMap(map);
	HighLevelSolver solver;
	optimalPaths = solver.solve(map);
	printSolution(optimalPaths);
	auto done = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
	std::cout << elapsedTime << " milliseconds ";

	return 0;
}
