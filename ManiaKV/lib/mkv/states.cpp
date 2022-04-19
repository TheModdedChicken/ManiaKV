#include <lib/json.hpp>
#include <fstream>
#include <string>
#include <memory>
#include <optional>

#include "defs.hpp"
#include "utility.hpp"

#include "states.hpp"

using nlohmann::json;
using std::string;
using std::map;
using std::vector;
using std::shared_ptr;
using std::optional;

namespace mkv {
	inline json statesJson = NULL;
	inline vector<string> writableStatesJson = {};
	inline json writtenStatesJson = {};

	// TO-DO: Create toggleable states
	inline map<string, bool> toggles = {};

	std::map<STATES, string> StatesMap = {
		{INIT, "init"},
		{STAGE, "stage"},
		{LOGOPS, "logops"},
		{UPDATE_SKIP, "update_skip"}
	};

	json GetWritableStates () {
		json out = writtenStatesJson;
		auto stateIt = statesJson.items();
		for (auto state : stateIt) {
			if (ExistsInVector(writableStatesJson, state.key())) out[state.key()] = state.value();
		}
		return out;
	}

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

	optional<json> GetState (STATES state) {
		try {
			return GetStates().at(StatesMap[state]);
		} catch (...) {
			return std::nullopt;
		}
	}

	void SetState (STATES state, json value, bool writable) {
		if (statesJson == NULL) GetStates();
		string stateName = StatesMap[state];

		statesJson[stateName] = value;
		if (writable) writableStatesJson.push_back(stateName);
	}

	void WriteState (STATES state) {
		if (writableStatesJson.empty()) return;
		string stateName = StatesMap[state];
		if (!ExistsInVector(writableStatesJson, stateName)) return;

		writtenStatesJson[stateName] = statesJson[stateName];

		std::ofstream o(mkv::statesPath);
		o << std::setw(4) << writtenStatesJson << std::endl;
	}

	void WriteStates () {
		if (writableStatesJson.empty()) return;

		json out = GetWritableStates();

		std::ofstream o(mkv::statesPath);
		o << std::setw(4) << out << std::endl;

		writtenStatesJson = out;
	}
}