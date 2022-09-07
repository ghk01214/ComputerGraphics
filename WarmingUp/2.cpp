#include "pch.h"
#include "2.h"

bool IsCapitalWord(const std::string* word)
{
	auto num{ std::find_if(word->cbegin(), word->cend(), [](char c)
		{
			return std::isupper(c);
		}) };

	if (num == word->cend())
		return false;

	return true;
}

bool HasLetter(const std::string* word)
{
	auto letter{ std::find_if(word->cbegin(), word->cend(), [](char c)
	{
		return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
	}) };

	if (letter == word->cend())
		return false;

	return true;
}

bool IsNumber(const std::string* word)
{
	try
	{
		int32 num{ std::stoi(*word) };

		if (HasLetter(word))
			throw num;
		else
			return true;
	}
	catch (const std::exception& e)
	{
		return false;
	}
	catch (int32 e)
	{
		return false;
	}
}

void run2()
{
	std::ifstream in{ "data.txt" };

	if (in.is_open() == false)
	{
		std::cout << std::format("File open failed\n");
		return;
	}

	std::string word;
	std::list<std::string> list;

	while (in >> word)
	{
		list.push_back(word);
	}

	auto word_list{ list | std::views::filter([](const std::string& word) {return IsNumber(&word) == false; }) };
	auto num{ list | std::views::filter([](const std::string& word) { return IsNumber(&word); }) };
	auto cap{ list | std::views::filter([](const std::string& word) {return IsCapitalWord(&word); }) };
	
	int32 word_count{};
	int32 num_count{};
	int32 capital_count{};

	for (auto& str : word_list)
	{
		++word_count;
	}

	std::cout << std::format("word count : {}\n", word_count);

	for (auto& str : num)
	{
		std::cout << str << " ";
		++num_count;
	}

	std::cout << std::format("\nnumber count : {}\n", num_count);

	for (auto& str : cap)
	{
		std::cout << str << " ";
		++capital_count;
	}

	std::cout << std::format("\ncapital count : {}\n", capital_count);
}