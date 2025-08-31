/**
 * @file map.cpp
 * @brief Implementation of map loading functionality
 * 
 * Handles reading map files that contain:
 * - Grid dimensions
 * - Obstacle positions
 * - Agent start/goal positions and sizes
 */

#include "map.h"
#include "util.h"

map::map() = default;
map::~map() = default;

/**
 * @brief Utility function to split strings by delimiter
 * @param s Input string to split
 * @param delim Delimiter character
 * @return Vector of split string parts
 */
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

/**
 * @brief Reads map configuration from file
 * @param filename Path to the map file
 * 
 * Expected file format:
 * Line 1: width height
 * Line 2: obstacle coordinates (x1,y1 x2,y2 ...)
 * Line 3: agent start positions (x1,y1 x2,y2 ...)
 * Line 4: agent goal positions (x1,y1 x2,y2 ...)  
 * Line 5: agent sizes (len1 len2 ...)
 */
void map::readMap(std::string filename)
{
	Map map; // Grid map structure
	int row, col;
	std::vector<std::vector<Cell>> cells;
	std::ifstream infile;
	infile.open(filename);
	std::string line;
	std::string line2;
	std::string line3;
	
	// Read dimensions from first line
	getline(infile, line);
	auto splitted = split(line, ' ');
	col = std::stoi(splitted[0]);
	row = std::stoi(splitted[1]);

	// Read obstacle line
	getline(infile, line);

	// Initialize grid with all cells as non-obstacles
	std::istringstream k(line);
	std::string s;

	// Create the grid structure
	for (int i = 0; i <= row; i++)
	{
		std::vector<Cell> row_;
		for (int j = 0; j <= col; j++)
		{
			Cell n(j, i);
			row_.emplace_back(n);
		}
		cells.emplace_back(row_);
	};

	// Parse obstacle positions and mark them in the grid
	while (getline(k, s, ' '))
	{
		auto splitted = split(s, ',');
		int x = std::stoi(splitted[0]);
		int y = std::stoi(splitted[1]);
		cells[y][x].isObstacle = true;  // Mark cell as obstacle
	}

	// Read agent configuration lines
	// Note: variables 'start' and 'end' are declared but unused - this causes warnings
	// int start, end;  // Commented out to fix unused variable warning

	std::vector<Agent> agents;

	int agentID = 0;
	getline(infile, line);   // Agent start positions
	getline(infile, line2);  // Agent goal positions  
	getline(infile, line3);  // Agent sizes
	
	k.clear();
	s = ' ';
	std::istringstream k1(line);   // Stream for start positions
	std::istringstream k2(line2);  // Stream for goal positions
	std::istringstream k3(line3);  // Stream for agent sizes
	std::string s2;
	std::string s3;
	
	// Parse agents data (start positions, goal positions, sizes)
	while (getline(k1, s, ' '))
	{
		Agent agent(agentID);
		getline(k2, s2, ' ');
		getline(k3, s3, ' ');
		
		auto splitted = split(s, ',');    // Start position
		auto splitted2 = split(s2, ',');  // Goal position

		int startx = std::stoi(splitted[0]);
		int starty = std::stoi(splitted[1]);
		int endx = std::stoi(splitted2[0]);
		int endy = std::stoi(splitted2[1]);
		
		agent.len = std::stoi(s3);                 // Agent size
		agent.start = Cell(startx, starty);        // Start position
		agent.end = Cell(endx, endy);              // Goal position
		agents.emplace_back(agent);
		agentID++;
	}

	// Store the parsed data in the map structure
	map.cells = cells;
	map.agents = agents;
	infile.close();
	this->m = map;  // Assign to class member
}


