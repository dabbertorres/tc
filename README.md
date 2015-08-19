# tc
Text Completion done with the C++ standard library

Uses C++ 11/14.

# How to use
Simple as!
```c++
#include <Completer.hpp>

... // Not sure what goes here. Your own code for something?

tc::Completer complete;

complete.add("myFavoriteWord");
... // more favorite words

// get some input
std::string input = ...

auto results = complete.complete(input);

for(auto& s : ret)
	std::cout << s << '\n';
std::cout << '\n';
```

And that's it! Simple (3 function calls if you count default constructors)!
