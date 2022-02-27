#include <lib/json.hpp>
#include <fstream>
#include <string>
#include <memory>

#include "../main/defs.hpp"

using nlohmann::json;
using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

inline json statesJson = NULL;
inline json writtenStatesJson = NULL;

// TO-DO: Create toggleable states
inline map<string, bool> toggles = {};

json GetStates () {
	if (statesJson == NULL) {
		try {
			std::ifstream i(mkv::statesLoc);
			i >> statesJson;

			return statesJson;
		} catch (json::exception) {
			statesJson = {{"init", 1}};
			std::ofstream o(mkv::statesLoc);
			o << std::setw(4) << statesJson << std::endl;

			writtenStatesJson = statesJson;
			return statesJson;
		}
	} else return statesJson;
}

json GetState (string state) {
	return GetStates().at(state);
}

void SetState (string state, json value, bool write = false) {
	statesJson[state] = value;
	if (write == true) {
		writtenStatesJson[state] = value;
		std::ofstream o(mkv::statesLoc);
		o << std::setw(4) << writtenStatesJson << std::endl;
	}
}

void WriteStates () {
	std::ofstream o(mkv::statesLoc);
	o << std::setw(4) << statesJson << std::endl;

	writtenStatesJson = statesJson;
}