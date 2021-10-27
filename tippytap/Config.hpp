#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "json.hpp"
#include "Character.hpp"

using json = nlohmann::json;

class Config {
public:
	json configJson;

	int windowWidth;
	int windowHeight;

	std::map<std::string, Character> characters;

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
		for (json character : configJson["characters"]) {
			Character characterClass = { character };

			try {
				characters.insert(
					std::pair<std::string, Character>(characterClass.id, characterClass)
				);
			} catch (json::exception err) {
				std::cout << err.what();
				throw err;
			}
		}

		return characters;
	}

private:
	std::string userdataF = "./userdata/";
};