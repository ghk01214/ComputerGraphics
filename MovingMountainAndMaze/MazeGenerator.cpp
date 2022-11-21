#include "pch.h"
#include "MazeGenerator.h"

std::uniform_int_distribution<int32_t> uid_dir{ 1, 4 };

MazeGenerator::MazeGenerator(int32_t size) :
	_size{ size }
{
	MakeGrid();
	SetWalkable();
	Create();

	//Print();
}

MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::MakeGrid()
{
	for (int32_t i = 0; i < _size * 2 + 1; ++i)
	{
		std::vector<char> temp(_size * 2 + 1, 'X');

		_maze.push_back(temp);
	}

	//create the holes
	for (int32_t i = 0; i < _maze.size(); ++i)
	{
		for (int32_t j = 0; j < _maze[i].size(); ++j)
		{
			if (j % 2 == 0 or i % 2 == 0)
				_maze[i][j] = '#';
			else
				_maze[i][j] = ' ';

			if (j == 0 or j == _maze[i].size() - 1)
				_maze[i][j] = '#';

			if (i == 0 or i == _maze.size() - 1)
				_maze[i][j] = '#';

			//created entrace and exit
			if (j == 0 && i == 1)
				_maze[i][j] = ' ';

			if (j == _maze[i].size() - 1 && i == _maze.size() - 2)
				_maze[i][j] = ' ';
		}
	}
}

void MazeGenerator::SetWalkable()
{
	_walkable.reserve(_maze.size());

	for (int32_t i = 0; i < _maze.size(); ++i)
	{
		std::vector <bool> temp(_maze[i].size(), true);

		_walkable.push_back(temp);
	}

	for (int32_t i = 0; i < _maze.size(); ++i)
	{
		for (int32_t j = 0; j < _maze[i].size(); ++j)
		{
			if (j % 2 == 0 || i % 2 == 0)
				_walkable[i][j] = false;
			else
				_walkable[i][j] = true;

			if (j == 0 || j == _maze[i].size() - 1)
				_walkable[i][j] = false;

			if (i == 0 || i == _maze.size() - 1)
				_walkable[i][j] = false;
		}
	}
}

void MazeGenerator::Create()
{
	int32_t x{ 1 };
	int32_t y{ 1 };

	_walk_back = false;

	while (true)
	{
		if (_walk_back == false)
			SavePosition(x, y);

		_walk_back = false;

		CheckDirection(x, y);
		
		std::uniform_int_distribution<size_t> uid{ 0, _direction.size() - 1 };
		//_walk_direction = _direction[uid(dre)];
		_walk_direction = _direction[rand() % _direction.size()];

		_walkable[y][x] = false; // can cause error while backtracking

		if (_walk_direction == DIRECTION::NORTH)
		{
			_maze[y - 1][x] = ' ';
			y = y - 2;
		}

		if (_walk_direction == DIRECTION::EAST)
		{
			_maze[y][x + 1] = ' ';
			x = x + 2;
		}

		if (_walk_direction == DIRECTION::SOUTH)
		{
			_maze[y + 1][x] = ' ';
			y = y + 2;
		}

		if (_walk_direction == DIRECTION::WEST)
		{
			_maze[y][x - 1] = ' ';
			x = x - 2;
		}

		if (_walk_direction == DIRECTION::NONE)
		{
			BackTrack(&x, &y);
		}

		//check if completed
		if (CheckCompletion() == true)
			return;
	}
}

void MazeGenerator::SavePosition(int32_t x, int32_t y)
{
	_position.push_back(x);
	_position.push_back(y);
}

void MazeGenerator::BackTrack(int32_t* x, int32_t* y)
{
	_position.pop_back();
	_position.pop_back();

	*x = _position[_position.size() - 2];
	*y = _position[_position.size() - 1];
	_walk_back = true;
}

void MazeGenerator::CheckDirection(int32_t width, int32_t height)
{
	if (_direction.size() > 0)
		_direction.erase(_direction.begin(), _direction.end());

	//checks the corners
	if (height == 1 && width == 1)
	{
		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east

		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south
	}
	else if (height == 1 && width == _walkable[height].size() - 2)
	{
		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south

		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}
	else if (height == _walkable.size() - 2 && width == 1)
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north

		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east
	}
	else if (height == _walkable.size() - 2 && width == _walkable[height].size() - 2)
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north

		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}
	//checks the sides
	else if (height == 1 && (width > 2 and width < _walkable[height].size() - 3))
	{
		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east

		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south

		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}
	else if (height == _walkable.size() - 2 && (width > 2 && width < _walkable[height].size() - 3))
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north

		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east

		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}
	else if ((height > 2 && height < _walkable.size() - 3) && width == 1)
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north

		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east
		
		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south
	}
	else if ((height > 2 && height < _walkable.size() - 3) && width == _walkable.size() - 2)
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north
		
		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south
		
		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}
	else
	{
		if (_walkable[height - 2][width] == 1)
			_direction.push_back(DIRECTION::NORTH); //north
		
		if (_walkable[height][width + 2] == 1)
			_direction.push_back(DIRECTION::EAST); //east
		
		if (_walkable[height + 2][width] == 1)
			_direction.push_back(DIRECTION::SOUTH); //south
		
		if (_walkable[height][width - 2] == 1)
			_direction.push_back(DIRECTION::WEST); //west
	}

	if (_direction.size() == 0)
		_direction.push_back(DIRECTION::NONE); //nothing
}

bool MazeGenerator::CheckCompletion()
{
	for (int32_t i = 0; i < _maze.size(); ++i)
	{
		for (int32_t j = 0; j < _maze[i].size(); ++j)
		{
			if (_walkable[i][j] == 1)
				return false;
		}
	}

	return true;
}

void MazeGenerator::Print()
{
	for (int32_t i = _maze.size() - 1; i >= 0; --i)
	{
		for (int32_t j = _maze[i].size() - 1; j >= 0; --j)
		{
			std::cout << std::format("{} ", _maze[i][j]);
		}

		std::cout << std::endl;
	}
}
