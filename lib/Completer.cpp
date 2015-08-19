#include "Completer.hpp"

namespace
{
	static void vectorAppend(std::vector<std::string>& dest, const std::vector<std::string>& src)
	{
		for(auto& s : src)
			dest.emplace_back(s);
	}
}

namespace tc
{
	void Completer::add(const std::string& str)
	{
		Radix* top = &data;

		for(auto& c : str)
		{
			top->emplace(c, Node());
			top = &(*top)[c].nodes;
		}
		
		// we use null characters to signify the end of a string in the data.
		top->emplace('\0', Node());
	}

	void Completer::add(const std::vector<std::string>& vec)
	{
		for(auto& s : vec)
			add(s);
	}

	Completer::Results Completer::complete(const std::string& input) const
	{
		std::vector<std::string> ret;

		const Radix* top = &data;
		auto lastIt = input.end() - 1;

		// traverse down the tree until we've reached the end of the input (or exit early if no matches)
		for(auto it = input.begin(); it != input.end(); ++it)
		{
			if(top->find(*it) != top->end())
			{
				top = &top->at(*it).nodes;

				// if we're at the last character of the input, branch out and find all matches from here
				if(it == lastIt)
					vectorAppend(ret, depthTraverse(*top, input));
			}
			else
			{
				break;
			}
		}

		return ret;
	}

	Completer::Results Completer::depthTraverse(const Radix& radix, const std::string& prefix) const
	{
		std::vector<std::string> ret;

		for(auto& it : radix)
		{
			// if not at the end of a word...
			if(it.first != '\0')
			{
				// build new prefix and search further
				std::string np = prefix + it.first;
				auto depth = depthTraverse(it.second.nodes, np);

				// add results to return value
				vectorAppend(ret, depth);
			}
			else
			{
				// found a null character, so the prefix is a word
				ret.emplace_back(prefix);
			}
		}

		return ret;
	}
}
