#include "pch.h"
#include "Maze.h"

std::uniform_int_distribution<int32_t> uid_dir{ 1, 4 };

Maze::Maze(int32_t size) :
	_size{ size },
	_maze(_size * _size, 0),
	_x{ 0 },
	_y{ 0 }
{
}

Maze::~Maze()
{
}
