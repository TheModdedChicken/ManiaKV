#ifndef STATES_HPP
#define STATES_HPP

#include <lib/json.hpp>
#include <string>

// Get all states
nlohmann::json GetStates();
// Get value of specified state
nlohmann::json GetState(std::string state);

// Set local state value
void SetState(std::string state, nlohmann::json value, bool write = false);

// Write all states to drive
void WriteStates();

#endif // !STATES_HPP
