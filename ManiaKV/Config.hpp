#pragma once
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "Character.hpp"
#include "Stage.hpp"

using json = nlohmann::json;
using std::string;
using std::map;

class Config {
public:
	string configLoc;
	json configJson;

	map<string, Character> characters;
	map<string, Stage> stages;

	// TO-DO: Add optimizations to texture loading
	map<string, Texture2D> textures;

	// Window options
	int windowWidth = 1189;
	int windowHeight = 669;
	bool alwaysOntop = false;
	bool transparent = false;
	bool undecorated = false;

	// TO-DO: Clean up Stage and Character loading

	Config (string configLocation) {
		Load(configLocation);
	}

	void PostLoad () {
		LoadCharacters();
		LoadStages();
	}

	void Reload () {
		Load(configLoc);
	}
	void Reload (string configLocation) {
		this->Load(configLocation);
	}

private:
	void Load (string configLocation) {
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

	map<string, Character> LoadCharacters () {
		for (json character : configJson.at("characters")) {
			Character characterClass = { character, windowWidth, windowHeight };
			characters.insert({ characterClass.id, characterClass });
		}

		return characters;
	}

	map<string, Stage> LoadStages () {
		for (json stage : configJson.at("stages")) {
			std::cout << stage;
			Stage stageClass = { stage, characters, windowWidth, windowHeight };
			stages.insert({ stageClass.id, stageClass });
		}

		return stages;
	}

	string userdataF = "./userdata/";
};