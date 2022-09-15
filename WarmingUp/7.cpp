#include "pch.h"
#include <Windows.h>
#include <map>

std::uniform_int_distribution<int32> uid_alpha{ 0, 7 };
uint32 score{ 0 };

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)				// 콘솔창의 핸들정보 받기

#define BLACK			SetConsoleTextAttribute(COL, 0x0000)		// 검정색
#define DARK_BLUE		SetConsoleTextAttribute(COL, 0x0001)		// 파란색
#define DARK_GREEN		SetConsoleTextAttribute(COL, 0x0002)		// 녹색
#define DARK_CYAN		SetConsoleTextAttribute(COL, 0x0003)		// 청녹색
#define DARK_RED		SetConsoleTextAttribute(COL, 0x0004)		// 검붉은색
#define DARK_MAGENTA	SetConsoleTextAttribute(COL, 0x0005)		// 보라색
#define GOLD			SetConsoleTextAttribute(COL, 0x0006)		// 금색
#define GRAY			SetConsoleTextAttribute(COL, 0x0007)		// 밝은 회색 (ORIGINAL CONSOLE COLOR)
#define DARK_GRAY		SetConsoleTextAttribute(COL, 0x0008)		// 회색
#define BLUE			SetConsoleTextAttribute(COL, 0x0009)		// 파란색
#define GREEN			SetConsoleTextAttribute(COL, 0x000a)		// 연두색
#define CYAN			SetConsoleTextAttribute(COL, 0x000b)		// 하늘색
#define RED				SetConsoleTextAttribute(COL, 0x000c)		// 빨간색
#define MAGENTA			SetConsoleTextAttribute(COL, 0x000d)		// 자주색
#define YELLOW			SetConsoleTextAttribute(COL, 0x000e)		// 노란색
#define WHITE			SetConsoleTextAttribute(COL, 0x000f)		// 흰색
#define ORIGINAL GRAY

std::vector<std::vector<char>> Init(std::map<char, bool>* found)
{
	std::vector<std::vector<char>> board;
	std::map<char, int32> count;
	int32 i{ 0 };

	while (board.size() != 4)
	{
		std::vector<char> line;

		while (line.size() != 4)
		{
			char alphabet{ 65 + static_cast<char>(uid_alpha(dre)) };

			if (count.contains(alphabet) == false)
				count.insert(std::make_pair(alphabet, 0));

			if (count[alphabet] == 2)
				continue;

			line.push_back(alphabet);
			++count[alphabet];
		}

		board.push_back(line);
	}

	for (int32 i = 0; i < 8; ++i)
	{
		found->insert(std::make_pair('A' + i, false));
	}

	return board;
}

int32 ChangeAToI(char c)
{
	if (std::isupper(c) == true)
	{
		return c - 'A';
	}
	else
	{
		return c - 'a';
	}
}

void PrintColorLetter(char c)
{
	switch (c)
	{
		case 'A': RED;
		break;
		case 'B': YELLOW;
		break;
		case 'C': GREEN;
		break;
		case 'D': CYAN;
		break;
		case 'E': BLUE;
		break;
		case 'F': MAGENTA;
		break;
		case 'G': GOLD;
		break;
		case 'H': WHITE;
		break;
	}

	std::cout << std::format(" {}", c);
	ORIGINAL;
}

void PrintBoard(std::vector<std::vector<char>>* board, std::map<char, bool>* found, std::string* card1 = nullptr, std::string* card2 = nullptr)
{
	std::cout << std::format("  a b c d\n");

	int32 x1;
	int32 y1;
	int32 x2;
	int32 y2;

	if (card1 != nullptr)
	{
		x1 = std::tolower((*card1)[0]) - 'a';
		y1 = (*card1)[1] - '1';
	}

	if (card2 != nullptr)
	{
		x2 = std::tolower((*card2)[0]) - 'a';
		y2 = (*card2)[1] - '1';

		if ((*board)[y1][x1] == (*board)[y2][x2])
		{
			(*found)[(*board)[y1][x1]] = true;
			++score;
		}
	}

	for (int32 i = 0; i < board->size(); ++i)
	{
		std::cout << std::format("{}", i + 1);

		for (int32 j = 0; j < (*board)[i].size(); ++j)
		{
			char c{ (*board)[i][j] };

			if (card1 == nullptr)
			{
				if ((*found)[c] == true)
					PrintColorLetter(c);
				else
					std::cout << std::format(" {}", '*');

				continue;
			}

			if (card2 == nullptr)
			{
				if ((*found)[c] == true)
					PrintColorLetter(c);
				else if (x1 == j && y1 == i)
					std::cout << " ○";
				else
					std::cout << std::format(" {}", '*');
			}
			else
			{
				if (x1 == j && y1 == i)
					PrintColorLetter((*board)[y1][x1]);
				else if (x2 == j && y2 == i)
					PrintColorLetter((*board)[y2][x2]);
				else
				{
					if ((*found)[c] == true)
						PrintColorLetter(c);
					else
						std::cout << std::format(" {}", '*');
				}
			}
		}

		std::cout << std::endl;
	}
}

int32 Command(std::vector<std::vector<char>>* board, std::map<char, bool>* found, std::string* card, std::string* card1, std::string* card2)
{
	std::cin >> *card;

	switch ((*card)[0])
	{
		case 'R': FALLTHROUGH
		case 'r':
		{
			found->clear();
			*board = Init(found);

			return -1;
		}
		case 'Q': FALLTHROUGH
		case 'q':
		{
			std::cout << std::format("프로그램 종료\n");

			return 0;
		}
		default:
		{
			std::system("cls");
			PrintBoard(board, found, card1, card2);
		}
	}

	return 1;
}

void run7()
{
	std::map<char, bool> found;
	std::vector<std::vector<char>> board{ Init(&found) };

	std::string card1;
	std::string card2;
	int32 try_limit{ 20 };

	while (try_limit != 0)
	{
		std::system("cls");

		PrintBoard(&board, &found);

		std::cout << std::format("try count : {}\n", try_limit);
		std::cout << std::format("input card 1 : ");

		switch (Command(&board, &found, &card1, &card1, nullptr))
		{
			case -1:
			continue;
			case 0:
			return;
		}

		std::cout << std::format("try count : {}\n", try_limit);
		std::cout << std::format("input card 2 : ");

		switch (Command(&board, &found, &card2, &card1, &card2))
		{
			case -1:
			continue;
			case 0:
			return;
		}

		std::system("pause");

		--try_limit;
	}

	std::format("Total score : {}", score);
}