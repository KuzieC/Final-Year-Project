
#include <fstream>
#include <chrono>
#include "LowLevelSolver.h"
#include "HighLevelSolver.h"
#include "map.h"
#include <random>
#include <algorithm>

void writeoutput(std::vector<std::vector<Cell>> optimalPaths, Map &map)
{
	std::ofstream outfile;
	outfile.open("result.txt");
	outfile << map.cells[0].size()-1 << " " << map.cells.size()-1 << std::endl;
	for (int i = 0; i < map.cells.size(); i++)
	{
		for (int j = 0; j < map.cells[0].size(); j++)
		{
			if (map.cells[i][j].isObstacle)
			{
				outfile << j << "." << i << " ";
			}
		}
	}
	outfile << std::endl;
	for (int i = 0; i < map.agents.size(); i++)
	{
		outfile << map.agents[i].len << " ";
	}
	outfile << std::endl;
	for (int i = 0; i < map.agents.size(); i++)
	{
		for (auto cell : optimalPaths[i])
		{
			outfile << cell.x << "." << cell.y << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}

void randomlise(int xx, int yy, int sizes, int level)
{
	std::random_device rd;	// obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	int len = int(0.3 * std::min(xx,yy));
	if (level == 1) // easy
	{
		std::ofstream outfile;
		outfile.open("data\\random.txt");
		outfile << xx  << " " << yy << std::endl;
		outfile << std::endl;
		std::uniform_int_distribution<> distrx(0, xx); // define the range
		std::uniform_int_distribution<> distry(0, yy); // define the range
		std::vector<Cell> start;
		std::vector<Cell> end;
		for (int j = 0; j < sizes; j++)
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < start.size(); i++)
			{
				if (start[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			start.push_back(Cell(x, y));
			outfile << x << "," << y << " ";
		}
		outfile << std::endl;
		for (int j = 0; j < sizes; j++)
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < end.size(); i++)
			{
				if (end[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			end.push_back(Cell(x, y));
			outfile << distrx(gen) << "," << distry(gen) << " ";
		}
		outfile << std::endl;
		for (int i = 0; i < sizes; i++)
		{
			outfile << 0 << " ";
		}
	}
	else if (level == 2) // mid
	{
		std::ofstream outfile;
		outfile.open("data\\random.txt");
		outfile << xx + 1 << " " << yy + 1 << std::endl;
		outfile << std::endl;
		std::uniform_int_distribution<> distrx(0, xx);
		std::uniform_int_distribution<> distry(0, yy);
		std::uniform_int_distribution<> distrx1(0, (xx - len));
		std::uniform_int_distribution<> distry1(0, (yy - len));
		std::vector<Cell> start;
		std::vector<Cell> end;
		for (int j = 0; j < sizes - 1; j++)
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < start.size(); i++)
			{
				if (start[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			start.push_back(Cell(x, y));
			outfile << x << "," << y << " ";
		}
		int x = distrx1(gen);
		int y = distry1(gen);
		for (int i = 0; i < start.size(); i++)
		{
			if (start[i] == Cell(x, y) || start[i] == Cell(x, y + len) || start[i] == Cell(x + len, y) || start[i] == Cell(x + len, y + len))
			{
				x = distrx1(gen);
				y = distry1(gen);
				i = -1;
			}
		}
		start.push_back(Cell(x, y));
		start.push_back(Cell(x+len, y));
		start.push_back(Cell(x, y+len));
		start.push_back(Cell(x+len, y+len));
		outfile << x << "," << y << " ";
		outfile << std::endl;

		for (int j = 0; j < sizes - 1; j++)
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < end.size(); i++)
			{
				if (end[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			end.push_back(Cell(x, y));
			outfile << x << "," << y << " ";
		}
		x = distrx1(gen);
		y = distry1(gen);
		for (int i = 0; i < end.size(); i++)
		{
			if (end[i] == Cell(x, y) || end[i] == Cell(x, y + len) || end[i] == Cell(x + len, y) || end[i] == Cell(x + len, y + len))
			{
				x = distrx1(gen);
				y = distry1(gen);
				i = -1;
			}
		}
		end.push_back(Cell(x, y));
		end.push_back(Cell(x+len, y));
		end.push_back(Cell(x, y+len));
		end.push_back(Cell(x+len, y+len));
		outfile << x << "," << y << " ";
		outfile << std::endl;
		for (int i = 0; i < sizes - 1; i++)
		{
			outfile << 0 << " ";
		}
		outfile << len;
	}
	else if (level == 3) // hard
	{
		std::ofstream outfile;
		outfile.open("data\\random.txt");
		outfile << xx + 1 << " " << yy + 1 << std::endl;
		outfile << std::endl;
		std::uniform_int_distribution<> distrx(0, xx);
		std::uniform_int_distribution<> distry(0, yy);
		std::uniform_int_distribution<> distrx1(0, (xx - len));
		std::uniform_int_distribution<> distry1(0, (yy - len));
		std::vector<Cell> start;
		std::vector<Cell> end;
		for (int j = 0; j < sizes - 3; j++) //size 0 start
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < start.size(); i++)
			{
				if (start[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			start.push_back(Cell(x, y));
			outfile << x << "," << y << " ";
		}
		for (int j = 0; j < 3; j++)//large start
		{
			int x = distrx1(gen);
			int y = distry1(gen);
			for (int i = 0; i < start.size(); i++)
			{
				if (start[i] == Cell(x, y) || start[i] == Cell(x, y + len) || start[i] == Cell(x + len, y) || start[i] == Cell(x + len, y + len))
				{
					x = distrx1(gen);
					y = distry1(gen);
					i = -1;
				}
			}
			start.push_back(Cell(x, y));
			start.push_back(Cell(x+len, y));
			start.push_back(Cell(x, y+len));
			start.push_back(Cell(x+len, y+len));
			outfile << x << "," << y << " ";
		}
		outfile << std::endl;
		for (int j = 0; j < sizes - 3; j++) //size 0 end
		{
			int x = distrx(gen);
			int y = distry(gen);
			for (int i = 0; i < end.size(); i++)
			{
				if (end[i] == Cell(x, y))
				{
					x = distrx(gen);
					y = distry(gen);
					i = -1;
				}
			}
			end.push_back(Cell(x, y));
			outfile << x << "," << y << " ";
		}
		for (int j = 0; j < 3; j++) //large size end
		{
			int x = distrx1(gen);	
			int y = distry1(gen);
	
			for (int i = 0; i < end.size(); i++)
			{
				if (end[i] == Cell(x, y) || end[i] == Cell(x, y + len) || end[i] == Cell(x + len, y) || end[i] == Cell(x + len, y + len))
				{
					x = distrx1(gen);
					y = distry1(gen);
					i = -1;
				}
			}
			end.push_back(Cell(x    , y));
			end.push_back(Cell(x+len, y));
			end.push_back(Cell(x    , y+len));
			end.push_back(Cell(x+len, y+len));
			outfile << x << "," << y << " ";
		}
		outfile << std::endl;
		for (int i = 0; i < sizes - 3; i++)
		{
			outfile << 0 << " ";
		}
		for (int j = 0; j < 3; j++)
		{
			outfile << len << " ";
		}
		outfile << std::endl;
	}
}
int main()
{
	int totaltime = 0;
	int epoch = 1;
	int success = 0;
	int x = 50;
	int y = 30;
	int numberOfRobots = 8  ;
	int maxmiumT = 0;
	int minT = INT_MAX;
	std::vector<int> timeacc;
	for (int i = 0; i < epoch; i++)
	{
		//randomlise(x, y, numberOfRobots, 2);
		auto started = std::chrono::high_resolution_clock::now();

		std::vector<std::vector<Cell>> optimalPaths;
		map m1;
		m1.readMap("data\\map4.txt"); 
		// printMap(map);
		HighLevelSolver solver;
		optimalPaths = solver.solve(m1.m);

		auto done = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		// std::cout << elapsedTim	we << " milliseconds " << std::endl;
		// printSolution(optimalPaths);
		if (optimalPaths.size() == m1.m.agents.size())
		{
			writeoutput(optimalPaths, m1.m);
			timeacc.push_back(elapsedTime);
			success++;
			totaltime += elapsedTime;
			if (elapsedTime < minT)	
				minT = elapsedTime;
			if (elapsedTime > maxmiumT)
				maxmiumT = elapsedTime;

			//std::cout << "running " << i << " is success, time is " << elapsedTime << " ms" << std::endl;
		}
	}
	
	//std::cout << success << "/" << epoch << " is success, average runtime for each epoch is " << totaltime / success << " ms, max time is " << maxmiumT << " ms, min time is " << minT << " ms" << std::endl;
	std::ofstream outfile;
	outfile.open("statistic.txt");
	for( auto i : timeacc){
		outfile<< i << ","; 
	}
	outfile.close();
	return 0;
}
