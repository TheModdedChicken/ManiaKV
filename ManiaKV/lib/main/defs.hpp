#ifndef DEFS_HPP
#define DEFS_HPP

#include <string>

namespace mkv {
	std::string const userdataLoc = "./userdata/";
	std::string const configPath = userdataLoc + "config.json";
	std::string const statesLoc = userdataLoc + "states.json";

	typedef struct COORDINATES {
		int x;
		int y;
	} COORDINATES;
}

#endif // !DEFS_HPP
