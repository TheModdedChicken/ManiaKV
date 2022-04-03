#ifndef STATES_HPP
#define STATES_HPP

#include <lib/json.hpp>
#include <string>

namespace mkv {
	enum STATES {
		INIT = 0,
		STAGE = 1,
		LOGOPS = 2,
	};

	std::string GetStateName (STATES state);

	// Get all states
	nlohmann::json GetStates();
	// Get value of specified state
	nlohmann::json GetState(STATES state);

	// Set local state value
	void SetState(STATES state, nlohmann::json value, bool write = false);

	// Write all states to drive
	void WriteStates();
}

#endif // !STATES_HPP