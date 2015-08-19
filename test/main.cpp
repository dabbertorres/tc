#include <iostream>
#include <string>

#include "Completer.hpp"

int main()
{
	tc::Completer complete;

	complete.add("hello");
	complete.add("helli");
	complete.add("helloworld");
	complete.add("hi");
	complete.add("hellb");
	complete.add("helz");
	complete.add("greg");

	auto ret = complete.complete("hel");

	for(auto& s : ret)
		std::cout << s << '\n';
	std::cout << '\n';

	std::cin.ignore();

	return 0;
}
