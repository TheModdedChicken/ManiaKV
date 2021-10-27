#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "json.hpp"
#include "Character.hpp"
#include "Stage.hpp"

using json = nlohmann::json;

class Config {
public:
	json configJson;

	int windowWidth;
	int windowHeight;

	std::map<std::string, Character> characters;
	std::map<std::string, Stage> stages;

	Config (std::string configLocation) {
		std::ifstream i(configLocation);
		i >> configJson;

		try {
			windowWidth = configJson.at("windowWidth");
			windowHeight = configJson.at("windowHeight");
		} catch (json::exception err) {
			windowWidth = 1189;
			windowHeight = 669;
		}
	}

	std::map<std::string, Character> LoadCharacters () {
		for (json character : configJson.at("characters")) {
			Character characterClass = { character, windowWidth, windowHeight };
			characters.insert(
				std::pair<std::string, Character>(characterClass.id, characterClass)
			);
		}

		return characters;
	}

	std::map<std::string, Stage> LoadStages () {
		for (json stage : configJson.at("stages")) {
			Stage stageClass = { stageClass };
			stages.insert(
				std::pair<std::string, Stage>(stageClass.id, stageClass)
			);
		}

		return stages;
	}

private:
	std::string userdataF = "./userdata/";
};