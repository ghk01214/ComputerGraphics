#pragma once

class MazeGenerator
{
public:
	MazeGenerator(int32_t size);
	~MazeGenerator();

	void MakeGrid();
	void SetWalkable();

	void Create();
	void SavePosition(int32_t x, int32_t y);
	void BackTrack(int32_t* x, int32_t* y);
	void CheckDirection(int32_t width, int32_t height);
	bool CheckCompletion();

	void Print();

	std::vector<std::vector<char>> GetMaze() { return _maze; }
	
private:
	enum class DIRECTION
	{
		NONE = 0,
		NORTH,
		EAST,
		SOUTH,
		WEST,
		MAX
	} _walk_direction;

	std::vector<std::vector<char>> _maze;
	std::vector<std::vector<bool>> _walkable;
	std::vector<DIRECTION> _direction;
	std::vector<int32_t> _position;

	int32_t _size;
	bool _walk_back;
};
