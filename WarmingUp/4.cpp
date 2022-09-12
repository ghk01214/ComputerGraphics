#include "pch.h"
#include <conio.h>

std::uniform_int_distribution<int32> uid_width{ 0, 590 };
std::uniform_int_distribution<int32> uid_height{ 0, 390 };
std::uniform_int_distribution<int32> uid_move{ 10, 100 };

enum
{
	rect1 = 0,
	rect2
};

struct POINT
{
	int32 x, y;
};

struct RECT
{
	POINT lt;
	POINT rb;
};

void MoveX(RECT* rect, const int32& direction, const int32& distance)
{
	if (rect->lt.x + (direction * distance) < 0)
	{
		std::cout << std::format("Cannot move to x direction(out of range)\n");
		return;
	}

	if (rect->rb.x + (direction * distance) > 800)
	{
		std::cout << std::format("Cannot move to x direction(out of range)\n");
		return;
	}

	rect->lt.x += direction * distance;
	rect->rb.x += direction * distance;
}

void MoveY(RECT* rect, const int32& direction, const int32& distance)
{
	if (rect->lt.y + (direction * distance) < 0)
	{
		std::cout << std::format("Cannot move to y direction(out of range)\n");
		return;
	}

	if (rect->rb.y + (direction * distance) > 600)
	{
		std::cout << std::format("Cannot move to y direction(out of range)\n");
		return;
	}

	rect->lt.y += direction * distance;
	rect->rb.y += direction * distance;
}

bool CheckCollision(RECT* r1, RECT* r2)
{
	if (r2->lt.x <= r1->rb.x && r1->rb.x <= r2->rb.x)
	{
		if (r2->lt.y <= r1->rb.y && r1->rb.y <= r2->rb.y)
			return true;
		
		if (r2->lt.y <= r1->lt.y && r1->lt.y <= r2->rb.y)
			return true;
	}

	if (r2->lt.x <= r1->lt.x && r1->lt.x <= r2->rb.x)
	{
		if (r2->lt.y <= r1->rb.y && r1->rb.y <= r2->rb.y)
			return true;

		if (r2->lt.y <= r1->lt.y && r1->lt.y <= r2->rb.y)
			return true;
	}

	return false;
}

void run4()
{
	std::vector<int32> size;
	size.reserve(2);

	switch (uid(dre))
	{
		case 0:
		{
			size.push_back(50);
			size.push_back((uid(dre) + 1) * 70);
		}
		break;
		case 1:
		{
			size.push_back(100);
			size.push_back((uid(dre) + 1) * 70);
		}
		break;
		case 2:
		{
			size.push_back(200);
			size.push_back((uid(dre) + 1) * 70);
		}
		break;
	}

	POINT p1{ uid_width(dre), uid_height(dre) };
	POINT p2{ uid_width(dre), uid_height(dre) };

	RECT r1{ { p1.x, p1.y }, { p1.x + size[rect1], p1.y + size[rect1]} };
	RECT r2{ { p2.x, p2.y }, { p2.x + size[rect2], p2.y + size[rect2]} };

	std::vector<int32> move{ uid_move(dre), uid_move(dre) };

	std::cout << std::format("RECT 1 : ({}, {}), ({}, {})\n", r1.lt.x, r1.lt.y, r1.rb.x, r1.rb.y);
	std::cout << std::format("RECT 2 : ({}, {}), ({}, {})\n", r2.lt.x, r2.lt.y, r2.rb.x, r2.rb.y);
	std::cout << std::endl;

	bool flag_collide{ CheckCollision(&r1, &r2) };
	bool flag_rect1_move{ true };

	while (flag_collide == false)
	{
		switch (_getch())
		{
			case 'W': FALLTHROUGH
			case 'w':
			{
				if (flag_rect1_move == true)
					MoveY(&r1, -1, move[rect1]);
				else
					MoveY(&r2, -1, move[rect2]);
			}
			break;
			case 'A': FALLTHROUGH
			case 'a':
			{
				if (flag_rect1_move == true)
					MoveX(&r1, -1, move[rect1]);
				else
					MoveX(&r2, -1, move[rect2]);
			}
			break;
			case 'S': FALLTHROUGH
			case 's':
			{
				if (flag_rect1_move == true)
					MoveY(&r1, 1, move[rect1]);
				else
					MoveY(&r2, 1, move[rect2]);
			}
			break;
			case 'D': FALLTHROUGH
			case 'd':
			{
				if (flag_rect1_move == true)
					MoveX(&r1, 1, move[rect1]);
				else
					MoveX(&r2, 1, move[rect2]);
			}
			break;
		}

		if (flag_rect1_move == true)
			std::cout << std::format("RECT 1 moved\n");
		else
			std::cout << std::format("RECT 2 moved\n");

		flag_rect1_move = !flag_rect1_move;

		std::cout << std::format("RECT 1 : ({}, {}), ({}, {})\n", r1.lt.x, r1.lt.y, r1.rb.x, r1.rb.y);
		std::cout << std::format("RECT 2 : ({}, {}), ({}, {})\n", r2.lt.x, r2.lt.y, r2.rb.x, r2.rb.y);
		std::cout << std::endl;

		flag_collide = CheckCollision(&r1, &r2);
	}

	std::cout << std::format("RECT 1 & RECT 2 Collide!!\n");
}