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
	std::string configLoc;
	json configJson;

	int windowWidth;
	int windowHeight;

	std::map<std::string, Character> characters;
	std::map<std::string, Stage> stages;

	// TO-DO: Clean up Stage and Character loading

	Config (std::string configLocation) {
		Load(configLocation);
	}

	void PostLoad () {
		LoadCharacters();
		LoadStages();
	}

	void Reload () {
		Load(configLoc);
	}
	void Reload (std::string configLocation) {
		this->Load(configLocation);
	}

private:
	void Load (std::string configLocation) {
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
			std::cout << stage;
			Stage stageClass = { stage, characters, windowWidth, windowHeight };
			stages.insert(
				std::pair<std::string, Stage>(stageClass.id, stageClass)
			);
		}

		return stages;
	}

	std::string userdataF = "./userdata/";
};