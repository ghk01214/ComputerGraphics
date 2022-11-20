#pragma once

class Maze
{
private:
public:
	Maze(int32_t size);
	~Maze();
	
private:
	std::vector<uchar> _maze;
	int32_t _size;

	uint32_t _x;
	uint32_t _y;
};
