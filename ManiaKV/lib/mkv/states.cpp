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
	inline json SessionStates = {};
	inline vector<string> LocalStates = {};
	inline json SavedStates = {};

	// TO-DO: Create toggleable states
	inline map<string, bool> toggles = {};

	std::map<STATES, string> StatesMap = {
		{STAGE, "stage"},
		{LOGOPS, "logops"},
		{UPDATE_SKIP, "update_skip"}
	};

	json GetWritableStates () {
		json out = SavedStates;
		auto stateIt = SessionStates.items();
		for (auto state : stateIt) {
			if ( ExistsInVector(LocalStates, state.key()) ) 
				out[state.key()] = state.value();
		}
		return out;
	}

	string GetStateName (STATES state) {
		return StatesMap[state];
	}

	json GetStates () {
		if (SavedStates.empty()) {
			try {
				std::ifstream i(mkv::statesPath);
				i >> SavedStates;
				SessionStates = SavedStates;

				return SessionStates;
			} catch (json::exception) {
				SessionStates = WriteStates(true);
				return SessionStates;
			}
		} else return SessionStates;
	}

	optional<json> GetState (STATES state) {
		try {
			return GetStates().at(StatesMap[state]);
		} catch (...) {
			return std::nullopt;
		}
	}

	void SetState (STATES state, json value, bool writable) {
		if (SessionStates.empty()) GetStates();
		string stateName = StatesMap[state];

		SessionStates[stateName] = value;
		if (writable) LocalStates.push_back(stateName);
	}

	void WriteState (STATES state) {
		if (LocalStates.empty()) return;
		string stateName = StatesMap[state];
		if (!ExistsInVector(LocalStates, stateName)) return;

		SavedStates[stateName] = SessionStates[stateName];

		std::ofstream o(mkv::statesPath);
		o << std::setw(4) << SavedStates << std::endl;
	}

	json WriteStates (bool clear) {
		if (!clear && LocalStates.empty()) return SavedStates;

		json out;
		if (clear) out = { {"init", 1} };
		else out = GetWritableStates();

		std::ofstream o(mkv::statesPath);
		o << std::setw(4) << out << std::endl;

		SavedStates = out;
		return SavedStates;
	}
}