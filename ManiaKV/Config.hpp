#pragma once
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <optional>

#include "Cache.hpp"
#include "Character.hpp"
#include "Stage.hpp"

using nlohmann::json;
using std::string;
using std::map;

class Config {
public:
	string configLoc;
	json configJson;

	map<string, Character> characters;
	map<string, Stage> stages;

	Cache cache{};

	// General Options
	string language = "us_en";

	// Window Options
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

	void Unload () {
		Load(configLoc);
	}

private:

	void Load (string configLocation) {
		std::ifstream i(configLocation);
		i >> configJson;

		try {
			try {
				language = configJson.at("language");
			} catch (json::exception err) {}

			json windowConfig = configJson.at("window");

			try {
				windowWidth = windowConfig.at("width");
				windowHeight = windowConfig.at("height");
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

		cache.width = windowWidth;
		cache.height = windowHeight;
	}

	map<string, Character> LoadCharacters () {
		for (json character : configJson.at("characters")) {
			Character characterClass = { cache, character, windowWidth, windowHeight };
			characters.insert({ characterClass.id, characterClass });
		}

		return characters;
	}

	map<string, Stage> LoadStages () {
		for (json stage : configJson.at("stages")) {
			std::cout << stage;
			Stage stageClass = { cache, stage, characters, windowWidth, windowHeight };
			stages.insert({ stageClass.id, stageClass });
		}

		return stages;
	}

	string userdataF = "./userdata/";
};