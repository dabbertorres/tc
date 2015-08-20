#ifndef TC_COMPLETER_HPP
#define TC_COMPLETER_HPP

#ifndef _WIN32
	#define TEXTCOMPLETION_API
#else
	#define TEXTCOMPLETION_API __declspec(dllexport)
#endif

#include <string>
#include <map>
#include <vector>

namespace tc
{
	class TEXTCOMPLETION_API Completer
	{
		public:
			using Results = std::vector<std::string>;

			// feed known words to the completer
			void add(const std::string& str);
			void add(const std::vector<std::string>& vec);

			// ask for results given an input
			Results complete(const std::string& input) const;

		private:
			// so this is fun. It's sort of like... a recursive map.
			// A map of chars to a map of chars to a map of chars to a map of chars...
			// ...until you hit an empty map of chars (or one with just a null character in it).
			// That means you've found the end of a word.

			// forward declaration for the using statement below
			struct Node;

			// Radix Tree... Kind of. A "standard" implementation of one might be a good optimization though.
			using Radix = std::map<char, Node>;

			struct Node
			{
				Radix nodes;
			};

			// recursively traverses the data to build strings from the given map, down.
			Results depthTraverse(const Radix& radix, const std::string& prefix = "") const;
			
			Radix data;
	};
}

#endif
