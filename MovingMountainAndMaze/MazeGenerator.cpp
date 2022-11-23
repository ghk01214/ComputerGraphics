#include "pch.h"
#include "MazeGenerator.h"
#include <stack>

std::uniform_int_distribution<int32_t> uid{ 1, 100 };

MazeGenerator::MazeGenerator(int32_t width, int32_t height) :
	_width{ width },
	_height{ height },
	_row{ height * 2 + 1 },
	_column{ width * 2 + 1 }
{
	MakeGrid();
	Create();

	//Print();
}

MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::MakeGrid()
{
	std::vector<char> temp(_column, '#');
	_maze.resize(_row, temp);

	for (int32_t i = 0; i < _row; ++i)
	{
		for (int32_t j = 0; j < _column; ++j)
		{
			if (i % 2 != 0 and j % 2 != 0)
				_maze[i][j] = ' ';
		}
	}
}

void MazeGenerator::Create()
{
	std::vector<cell> cell_list;
	std::vector<bool> visit_list(_width * _height, false);
	std::stack<cell> stack;
	int32_t visited{};
	int32_t k{};

	for (int32_t i = 1; i < _row; i += 2)
	{
		for (int32_t j = 1; j < _column; j += 2)
		{
			cell_list.push_back(std::make_pair(k++, std::make_pair(i, j)));
		}
	}

	int32_t index{ uid(dre) % _height * _width };
	stack.push(cell_list[index]);
	visit_list[index] = true;
	++visited;

	while (visited < _height * _width)
	{
		std::vector<DIRECTION> neighbour;
		std::pair<int32_t, int32_t> in{ stack.top().second };

		if (in.first > 1)
		{
			int32_t x{ in.second };
			int32_t y{ in.first - 2 };

			if (_maze[y][x] and visit_list[Index(y, x, cell_list)] == false)
				neighbour.push_back(DIRECTION::NORTH);
		}

		if (in.second < _column - 2)
		{
			int32_t x{ in.second + 2 };
			int32_t y{ in.first };

			if (_maze[y][x] and visit_list[Index(y, x, cell_list)] == false)
				neighbour.push_back(DIRECTION::EAST);
		}

		if (in.first < _row - 2)
		{
			int32_t x{ in.second };
			int32_t y{ in.first + 2 };

			if (_maze[y][x] and visit_list[Index(y, x, cell_list)] == false)
				neighbour.push_back(DIRECTION::SOUTH);
		}

		if (in.second > 1)
		{
			int32_t x{ in.second - 2 };
			int32_t y{ in.first };

			if (_maze[y][x] and visit_list[Index(y, x, cell_list)] == false)
				neighbour.push_back(DIRECTION::WEST);
		}

		if (neighbour.empty() == true)
		{
			stack.pop();
			continue;
		}

		int32_t x{ in.second };
		int32_t y{ in.first };

		switch (neighbour[uid(dre) % neighbour.size()])
		{
			case DIRECTION::NORTH:
			{
				_maze[y - 1][x] = ' ';
				stack.push(cell_list[Index(y - 2, x, cell_list)]);
			}
			break;
			case DIRECTION::EAST:
			{
				_maze[y][x + 1] = ' ';
				stack.push(cell_list[Index(y, x + 2, cell_list)]);
			}
			break;
			case DIRECTION::SOUTH:
			{
				_maze[y + 1][x] = ' ';
				stack.push(cell_list[Index(y + 2, x, cell_list)]);
			}
			break;
			case DIRECTION::WEST:
			{
				_maze[y][x - 1] = ' ';
				stack.push(cell_list[Index(y, x - 2, cell_list)]);
			}
			break;
		}

		visit_list[stack.top().first] = true;
		++visited;
	}

	_maze[0][1] = ' ';
	_maze[_height * 2][_width * 2 - 1] = ' ';
}

int32_t MazeGenerator::Index(int32_t x, int32_t y, std::vector<cell> cell_list)
{
	for (auto& cell : cell_list)
	{
		if (cell.second.first == x and cell.second.second == y)
			return cell.first;
	}

	std::cout << std::format("No index found!\n");
	return -1;
}

void MazeGenerator::Print()
{
	for (auto& row : _maze)
	{
		for (auto& col : row)
		{
			std::cout << std::format("{} ", col);
		}

		std::cout << std::endl;
	}
}
