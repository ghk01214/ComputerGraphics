#include <iostream>
#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include "Util.h"

bool Util::ReadFile(const std::string& path, std::string* blob)
{
	std::ifstream file{ path };
	std::stringstream data{};

	if (file.fail())
	{
		std::cout << std::format("{} file load failed...\n", path);
		return false;
	}

	data << file.rdbuf();
	*blob = data.str();

	return true;
}

std::string Util::ReadFile(const std::string& path)
{
	std::ifstream file{ path };
	std::stringstream data{};

	if (file.fail())
	{
		std::cout << std::format("{} file load failed...\n", path);
		return std::string{};
	}

	data << file.rdbuf();

	return data.str();
}
