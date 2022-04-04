#include <lib/json.hpp>
#include <fstream>
#include <string>
#include <memory>

#include "../main/defs.hpp"

namespace mkv {
	using nlohmann::json;
	using std::string;
	using std::map;
	using std::vector;
	using std::shared_ptr;

	inline json statesJson = NULL;
	inline json writtenStatesJson = {};

	// TO-DO: Create toggleable states
	inline map<string, bool> toggles = {};

	enum STATES {
		INIT = 0,
		STAGE = 1,
		LOGOPS = 2,
		UPDATE_SKIP = 3,
	};

	std::map<STATES, string> StatesMap = {
		{INIT, "init"},
		{STAGE, "stage"},
		{LOGOPS, "logops"},
		{UPDATE_SKIP, "update_skip"}
	};

	string GetStateName (STATES state) {
		return StatesMap[state];
	}

	json GetStates () {
		if (statesJson == NULL) {
			try {
				std::ifstream i(mkv::statesPath);
				i >> statesJson;

				return statesJson;
			} catch (json::exception) {
				statesJson = { {"init", 1} };
				std::ofstream o(mkv::statesPath);
				o << std::setw(4) << statesJson << std::endl;

				writtenStatesJson = statesJson;
				return statesJson;
			}
		} else return statesJson;
	}

	json GetState (STATES state) {
		return GetStates().at(StatesMap[state]);
	}

	void SetState (STATES state, json value, bool write = false) {
		if (statesJson == NULL) GetStates();

		statesJson[StatesMap[state]] = value;
		if (write == true) {
			writtenStatesJson[StatesMap[state]] = value;
			std::ofstream o(mkv::statesPath);
			o << std::setw(4) << writtenStatesJson << std::endl;
		}
	}

	void WriteStates () {
		if (statesJson == NULL) GetStates();

		std::ofstream o(mkv::statesPath);
		o << std::setw(4) << statesJson << std::endl;

		writtenStatesJson = statesJson;
	}
}