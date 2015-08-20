#include <iostream>
#include <fstream>
#include <string>

#include <chrono>

#include "../lib/Completer.hpp"

std::vector<std::string> readFile(const std::string& file);

int main()
{
	tc::Completer complete;

	auto contents = readFile("text.txt");

	complete.add(contents);

	std::string input = "\0";
	while(true)
	{
		std::cout << ": ";
		std::cin >> input;

		if(input == "!x")
			break;

		auto start = std::chrono::high_resolution_clock::now().time_since_epoch();
		auto ret = complete.complete(input);
		auto end = std::chrono::high_resolution_clock::now().time_since_epoch();

		for(auto& s : ret)
			std::cout << s << '\n';
		std::cout << "time to complete: " << (end - start).count() / 1000000.0 << "ms\n\n";
	}

	return 0;
}

std::vector<std::string> readFile(const std::string& file)
{
	std::ifstream fin;

	fin.open("text.txt");

	if(!fin)
		return {};

	std::vector<std::string> contents;

	std::string in;
	while(fin >> in)
		contents.push_back(in);

	return contents;
}
