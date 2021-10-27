#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "json.hpp"
#include "input.hpp"

using json = nlohmann::json;

class Stage {
public:
	json stageJson;
	std::string id;
	std::vector<int> keys;
	std::vector<std::string> characters;
	int hotkey = -1;

	Stage (json stageIniJson) {
		stageJson = stageIniJson;
		LoadStage();
	}

	void LoadStage () {
		try {
			hotkey = stageJson.at("hotkey");
		} catch (json::exception err) {};

		try {
			id = stageJson.at("id");
			for (std::string character : stageJson.at("characters")) characters.push_back(character);

			for (std::string key : stageJson.at("keys")) {
				keys.push_back(GetKeyCode(key));
			}
		} catch (json::exception err) {
			std::cout << err.what();
			throw err;
		}
	}
};