#include "map.h"
#include "util.h"
map::map() = default;
map::~map() = default;
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

void map::readMap(std::string filename)
{

	Map map; // Grid map
	int row, col;
	std::vector<std::vector<Cell>> cells;
	std::ifstream infile;
	infile.open(filename);
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

	// std::cout << col << row << std::endl;
	for (int i = 0; i <= row; i++)
	{
		std::vector<Cell> row_;
		for (int j = 0; j <= col; j++)
		{
			Cell n(j, i);
			// n.isObstacle = false;
			row_.emplace_back(n);
		}
		cells.emplace_back(row_);
	};

	while (getline(k, s, ' '))
	{
		auto splitted = split(s, ',');
		int x = std::stoi(splitted[0]);
		int y = std::stoi(splitted[1]);
		// std:: cout<<x<<y<< cells[x][y].isObstacle << std::endl;
		cells[y][x].isObstacle = true;
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
	infile.close();
	this->m = map;
}


