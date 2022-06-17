#ifndef STATES_HPP
#define STATES_HPP

#include <lib/json.hpp>
#include <string>
#include <optional>

namespace mkv {
	enum STATES {
		STAGE = 1,
		LOGOPS = 2,
		UPDATE_SKIP = 3,
	};

	std::string GetStateName (STATES state);

	// Get all states
	nlohmann::json GetStates();
	// Get value of specified state
	std::optional<nlohmann::json> GetState(STATES state);

	// Set local state value
	void SetState(STATES state, nlohmann::json value, bool write = false);

	// Write one state to drive
	void WriteState(STATES state);

	// Write all states to drive
	nlohmann::json WriteStates(bool clear = false);
}

#endif // !STATES_HPP