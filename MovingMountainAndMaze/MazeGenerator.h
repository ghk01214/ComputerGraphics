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
	MazeGenerator(std::vector<std::vector<char>>& maze, int32_t width, int32_t height);
	~MazeGenerator();

	constexpr int32_t GetBlockNum() const { return _block_num; }

private:
	void MakeGrid(std::vector<std::vector<char>>& maze);
	void Create(std::vector<std::vector<char>>& maze);
	
	int32_t Index(int32_t x, int32_t y, std::vector<cell> cell_list);
	void Print(std::vector<std::vector<char>>& maze);

private:
	int32_t _width;
	int32_t _height;

	int32_t _row;
	int32_t _column;

	int32_t _block_num;
};
