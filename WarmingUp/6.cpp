#include "pch.h"
#include <conio.h>

struct POINT
{
	int32 x, y;
};

enum
{
	left = 0,
	right,
	up,
	down
};

std::uniform_int_distribution<int32> uid_direction{ left, down };
std::uniform_int_distribution<int32> uid_step{ 1, 8 };

void FindNewDirection(POINT* p, int32* direction, int32 prev_direction)
{
	int32 blocked{};

	if (p->x == 0)
	{
		if (*direction == left)
			blocked |= *direction;
	}
	else if (p->x == 29)
	{
		if (*direction == right)
			blocked |= *direction;
	}

	if (p->y == 0)
	{
		if (*direction == up)
			blocked |= *direction;
	}
	else if (p->y == 29)
	{
		if (*direction == down)
			blocked |= *direction;
	}

	while ((blocked & *direction) == *direction || *direction == prev_direction)
	{
		*direction = uid_direction(dre);
	}
}

int32 MakeRoute(std::vector<std::vector<int32>>* coord)
{
	POINT p{ 0, 0 };

	int32 prev_drection{ left };
	int32 i{ 0 };

	while (p.x != 29 || p.y != 29)
	{
		int32 direction{ uid_direction(dre) };

		FindNewDirection(&p, &direction, prev_drection);

		int32 step{ uid_step(dre) };

		switch (direction)
		{
			case left:
			{
				if (p.x - step < 0)
					step = p.x;

				for (int32 j = 0; j < step; ++j)
				{
					(*coord)[p.y][p.x--] = ++i;
				}
			}
			break;
			case right:
			{
				if (p.x + step > 29)
					step = 29 - p.x;

				for (int32 j = 0; j < step; ++j)
				{
					(*coord)[p.y][p.x++] = ++i;
				}
			}
			break;
			case up:
			{
				if (p.y - step < 0)
					step = p.y;

				for (int32 j = 0; j < step; ++j)
				{
					(*coord)[p.y--][p.x] = ++i;
				}
			}
			break;
			case down:
			{
				if (p.y + step > 29)
					step = 29 - p.y;

				for (int32 j = 0; j < step; ++j)
				{
					(*coord)[p.y++][p.x] = ++i;
				}
			}
			break;
		}

		prev_drection = direction;
	}

	(*coord)[p.y][p.x] = ++i;

	return i;
}

void PrintRoute(std::vector<std::vector<int32>>* coord, int32 steps)
{
	for (auto& v : *coord)
	{
		for (auto& c : v)
		{
			std::cout << std::format(" {}", c);
		}

		std::cout << std::endl;
	}

	std::cout << std::format("Total steps : {}", steps);
}

void MoveRoute(std::vector<std::vector<int32>>* coord, int32 direction)
{
	std::vector<int32> temp;
	temp.reserve(30);

	if (direction == left)
	{
		for (int32 i = 0; i < temp.capacity(); ++i)
		{
			temp.push_back((*coord)[i][0]);
		}

		for (int32 i = 0; i < coord->size(); ++i)
		{
			for (int32 j = 0; j < (*coord)[i].size() - 1; ++j)
			{
				(*coord)[i][j] = (*coord)[i][j + 1];
			}
		}

		for (int32 i = 0; i < temp.size(); ++i)
		{
			(*coord)[i][29] = temp[i];
		}
	}
	else if (direction == right)
	{
		for (int32 i = 0; i < temp.capacity(); ++i)
		{
			temp.push_back((*coord)[i][29]);
		}

		for (int32 i = 0; i < coord->size(); ++i)
		{
			for (int32 j = (*coord)[i].size() - 1; j > 0; --j)
			{
				(*coord)[i][j] = (*coord)[i][j - 1];
			}
		}

		for (int32 i = 0; i < temp.size(); ++i)
		{
			(*coord)[i][0] = temp[i];
		}
	}
}

void run6()
{
	std::vector<int32> line(30, 0);
	std::vector<std::vector<int32>> coord(30, line);

	int32 steps{ MakeRoute(&coord) };
	PrintRoute(&coord, steps);

	while (true)
	{
		int c{ _getch() };

		std::system("cls");

		switch (c)
		{
			case 'R': FALLTHROUGH
			case 'r':
			{
				for (auto& v : coord)
				{
					v = line;
				}

				steps = MakeRoute(&coord);
			}
			break;
			case 'A': FALLTHROUGH
			case 'a':
			{
				MoveRoute(&coord, left);
			}
			break;
			case 'D': FALLTHROUGH
			case 'd':
			{
				MoveRoute(&coord, right);
			}
			break;
			case 'Q': FALLTHROUGH
			case 'q':
			{
				std::cout << std::format("프로그램 종료\n");

				return;
			}
		}

		PrintRoute(&coord, steps);
	}
}