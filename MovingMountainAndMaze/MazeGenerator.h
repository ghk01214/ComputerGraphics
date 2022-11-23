#pragma once

class MazeGenerator
{
private:
	using cell = std::pair<int32_t, std::pair<int32_t, int32_t>>;

	enum DIRECTION
	{
		NONE = 0,
		NORTH,
		EAST,
		SOUTH,
		WEST,
		MAX
	};
public:
	MazeGenerator(int32_t width, int32_t height);
	~MazeGenerator();

	std::vector<std::vector<char>>& GetMaze() { return _maze; }

private:
	void MakeGrid();
	void Create();
	
	int32_t Index(int32_t x, int32_t y, std::vector<cell> cell_list);
	void Print();

private:
	int32_t _width;
	int32_t _height;

	int32_t _row;
	int32_t _column;

	std::vector<std::vector<char>> _maze;
};
