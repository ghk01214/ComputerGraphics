#include <iostream>
#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include "Util.h"

bool Util::ReadFile(const std::string& path, std::string* blob)
{
	std::ifstream file{ path };

	if (file.fail())
	{
		std::cout << std::format("{} file load failed...\n", path);
		return false;
	}

	std::string line;

	while (std::getline(file, line))
	{
		*blob += line;
		*blob += "\n";
		//blob->append(line.c_str());
		//blob->append("\n");
	}

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
