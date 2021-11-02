#pragma once
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "Character.hpp"
#include "Stage.hpp"

using json = nlohmann::json;

class Config {
public:
	std::string configLoc;
	json configJson;

	std::map<std::string, Character> characters;
	std::map<std::string, Stage> stages;

	// TO-DO: Add optimizations to texture loading
	std::map<std::string, Texture2D> textures;

	// Window options
	int windowWidth = 1189;
	int windowHeight = 669;
	bool alwaysOntop = false;
	bool transparent = false;
	bool undecorated = false;

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
			json windowConfig = configJson.at("window");

			try {
				windowWidth = windowConfig.at("windowWidth");
				windowHeight = windowConfig.at("windowHeight");
			} catch (json::exception err) {}

			try {
				alwaysOntop = windowConfig.at("alwaysOntop");
			} catch (json::exception err) {}

			try {
				transparent = windowConfig.at("transparent");
			} catch (json::exception err) {}

			try {
				undecorated = windowConfig.at("undecorated");
			} catch (json::exception err) {}
		} catch (json::exception err) {}
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