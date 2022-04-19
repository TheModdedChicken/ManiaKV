#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>
#include <map>
#include <functional>

namespace mkv {
	extern std::map<std::string, std::function<void(void)>> args;

	void ParseArgv (int argc, char* argv[]);
}

#endif // !ARGS_HPP
