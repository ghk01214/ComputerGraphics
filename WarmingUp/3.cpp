#include "pch.h"
#include "3.h"

bool insert_flag{ false };

void Reverse(std::list<std::string>* list)
{
	for (auto iter = list->begin(); iter != list->end(); ++iter)
	{
		std::string str{ iter->rbegin(), iter->rend() };

		*iter = str;
		std::cout << str << std::endl;
	}
}

void Insert(std::list<std::string>* list)
{
	if (insert_flag == false)
	{
		for (auto& line : *list)
		{
			for (int32 i = 0, index = 0; (index = 3 * (i + 1) + (i * 2)) < line.size(); ++i)
			{
				line.insert(index, "@@");
			}

			std::cout << line << std::endl;
		}

		insert_flag = true;
	}
	else
	{
		for (auto& line : *list)
		{
			for (std::string::size_type pos{}; (pos = line.find('@')) != line.npos;)
			{
				line.erase(pos, 2);
			}

			std::cout << line << std::endl;
		}

		insert_flag = false;
	}
}

void ReverseInRange(std::list<std::string>* list, const char criteria)
{
	for (auto& line : *list)
	{
		auto begin{ line.begin() };
		auto end{ line.begin() };
		std::string::size_type old{};

		for (std::string::size_type pos{}; ((pos = line.find(criteria, old)) != line.npos) || end != line.end();)
		{
			if (pos == line.npos)
				end = line.end();
			else
				std::advance(end, pos - old);

			std::string temp{ begin, end };
			std::string replace{ temp.rbegin(), temp.rend() };

			line.replace(begin, end, replace);

			if (pos != line.npos)
			{
				std::advance(end, 1);
				old = ++pos;
			}

			begin = end;
		}

		std::cout << line << std::endl;
	}
}

void ChangeLetter(std::list<std::string>* list)
{
	char before;
	char after;

	std::cout << std::format("change : ");
	std::cin >> before;
	std::cout << std::format("to : ");
	std::cin >> after;

	for (auto& line : *list)
	{
		for (std::string::size_type pos{}; line.npos != (pos = line.find(before));)
		{
			line.replace(pos, sizeof(before), &after, sizeof(after));
		}

		std::cout << line << std::endl;
	}
}

void SameFromFToB(std::list<std::string>* list)
{
	for (auto& line : *list)
	{
		std::string range{};
		auto riter{ line.crbegin() };

		for (auto iter = line.cbegin(); iter != line.cend() && riter != line.crend(); ++iter, ++riter)
		{
			if (*iter != *riter)
			{
				break;
			}

			if (std::distance(line.cbegin(), iter) == line.length() / 2)
			{
				break;
			}

			range.push_back(*iter);
		}

		std::cout << std::format("{} : ", line);

		if (range.empty())
		{
			std::cout << 0 << std::endl;
			continue;
		}

		std::cout << range << std::endl;
	}
}

void run3()
{
	std::ifstream in{ "data.txt" };

	if (in.fail())
	{
		std::cout << std::format("File open failed\n");
		return;
	}

	std::string line;
	std::list<std::string> list;

	while (std::getline(in, line))
	{
		list.push_back(line);
	}

	char command;

	while (true)
	{
		std::cout << std::format("command : ");
		std::cin >> command;

		switch (command)
		{
			case 'D': FALLTHROUGH
			case 'd':
			{
				Reverse(&list);
			}
			break;
			case 'E': FALLTHROUGH
			case 'e':
			{
				Insert(&list);
			}
			break;
			case 'F': FALLTHROUGH
			case 'f':
			{
				if (insert_flag == false)
					ReverseInRange(&list, ' ');
				else
					ReverseInRange(&list, '@');
			}
			break;
			case 'G': FALLTHROUGH
			case 'g':
			{
				ChangeLetter(&list);
			}
			break;
			case 'H': FALLTHROUGH
			case 'h':
			{
				SameFromFToB(&list);
			}
			break;
			case 'Q': FALLTHROUGH
			case 'q':
			{
				std::cout << std::format("프로그램 종료\n");

				return;
			}
			break;
		}

		std::cout << std::endl;

		std::cin.ignore();
		command = 0;

		std::system("pause");
		std::system("cls");
	}
}