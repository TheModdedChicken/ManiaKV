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
inline map<string, json> flags = {};

json GetStates () {
	if (statesJson == NULL) {
		try {
			std::ifstream i(mkvdefs::statesLoc);
			i >> statesJson;

			return statesJson;
		} catch (json::exception) {
			statesJson = {{"init", 1}};
			std::ofstream o(mkvdefs::statesLoc);
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
		std::ofstream o(mkvdefs::statesLoc);
		o << std::setw(4) << writtenStatesJson << std::endl;
	}
}

void WriteStates () {
	std::ofstream o(mkvdefs::statesLoc);
	o << std::setw(4) << statesJson << std::endl;

	writtenStatesJson = statesJson;
}