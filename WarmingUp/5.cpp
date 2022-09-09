#include "pch.h"
#include "ring.h"

struct Vertex
{
	int32 x, y, z;
};

void PrintList(const ring<Vertex>* list)
{
	for (int32 i = list->max_size() - 1; i >= 0; --i)
	{
		if (list->is_empty(i) == false)
			std::cout << i << " : " << std::endl;
		else
			std::cout << std::format("{} : ({}, {}, {})\n", i, (*list)[i].first.x, (*list)[i].first.y, (*list)[i].first.z);
	}
}

int32 Distance(const Vertex* point)
{
	return point->x * point->x + point->y * point->y + point->z * point->z;
}

Vertex Farthest(const ring<Vertex>* list)
{
	Vertex point{};
	int32 distance{ 0 };

	for (int32 i = 0; i < list->max_size(); ++i)
	{
		if ((*list)[i].second == false)
			continue;

		int32 new_dis{ Distance(&(*list)[i].first) };

		if (distance < new_dis)
		{
			distance = new_dis;
			point = (*list)[i].first;
		}
	}

	return point;
}

Vertex Nearest(const ring<Vertex>* list)
{
	Vertex point{};
	int32 distance{ INFINITE };

	for (int32 i = 0; i < list->max_size(); ++i)
	{
		if ((*list)[i].second == false)
			continue;

		int32 new_dis{ Distance(&(*list)[i].first) };

		if (distance > new_dis)
		{
			distance = new_dis;
			point = (*list)[i].first;
		}
	}

	return point;
}

void SortByDistance(ring<Vertex>* list, int32 start, int32 end)
{
	if (start >= end)
		return;

	int32 pivot{ start };
	int32 i{ pivot + 1 };
	int32 j{ end };
	std::pair<Vertex, bool> temp;

	while (i <= j)
	{
		while ((i <= end) && (Distance(&((*list)[i].first)) <= Distance(&((*list)[pivot].first))))
		{
			++i;
		}

		while ((j > start) && (Distance(&((*list)[j].first)) >= Distance(&((*list)[pivot].first))))
		{
			--j;
		}

		if (i > j)
		{
			temp = (*list)[j];
			(*list)[j] = (*list)[pivot];
			(*list)[pivot] = temp;
		}
		else
		{
			temp = (*list)[i];
			(*list)[i] = (*list)[j];
			(*list)[j] = temp;
		}
	}

	SortByDistance(list, start, j - 1);
	SortByDistance(list, j + 1, end);
}

void run5()
{
	char command;
	Vertex vertex;
	ring<Vertex> list;
	ring<Vertex> origin;
	bool sort_flag{ false };

	while (true)
	{
		std::cout << std::format("command : ");
		std::cin >> command;

		switch (command)
		{
			case '+':
			{
				std::cout << std::format("vertex : ");
				std::cin >> vertex.x >> vertex.y >> vertex.z;
				
				list.push_back(vertex);

				PrintList(&list);
			}
			break;
			case '-':
			{
				list.pop_back();

				PrintList(&list);
			}
			break;
			case 'E': FALLTHROUGH
			case 'e':
			{
				std::cout << std::format("vertex : ");
				std::cin >> vertex.x >> vertex.y >> vertex.z;

				list.push_front(vertex);

				PrintList(&list);
			}
			break;
			case 'D': FALLTHROUGH
			case 'd':
			{
				list.pop_front();
				
				PrintList(&list);
			}
			break;
			case 'L': FALLTHROUGH
			case 'l':
			{
				std::cout << std::format("size of buffer : {}\n", list.size());
			}
			break;
			case 'C': FALLTHROUGH
			case 'c':
			{
				list.clear();
			}
			break;
			case 'M': FALLTHROUGH
			case 'm':
			{
				Vertex farthest{ Farthest(&list) };

				std::cout << std::format("farthest vertex : ({}, {}, {})\n", farthest.x, farthest.y, farthest.z);
			}
			break;
			case 'N': FALLTHROUGH
			case 'n':
			{
				Vertex nearest{ Nearest(&list) };

				std::cout << std::format("farthest vertex : ({}, {}, {})\n", nearest.x, nearest.y, nearest.z);
			}
			break;
			case 'S': FALLTHROUGH
			case 's':
			{
				if (sort_flag == false)
				{
					origin = list;
					SortByDistance(&list, 0, list.max_size() - 1);
					list.align();

					sort_flag = true;
				}
				else
				{
					list = origin;
					sort_flag = false;
				}

				PrintList(&list);
			}
			break;
			case 'Q': FALLTHROUGH
			case 'q':
			{
				std::cout << std::format("프로그램 종료\n");

				return;
			}
		}

		std::cin.ignore();
		command = 0;

		std::system("pause");
		std::system("cls");
	}
}