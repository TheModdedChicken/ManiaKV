#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <lib/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <condition_variable>

#include "Cache.hpp"
#include "input.hpp"

#include "../components/Character.hpp"
#include "../components/Stage.hpp"

using nlohmann::json;
using std::string;
using std::map;
using std::condition_variable;

condition_variable cv;

class Config {
public:
	string configPath;
	json configData;
	Cache cache{};

	// General Options
	string title = "ManiaKV";
	string language = "*en-US";

	// Window Options
	int windowWidth = 1189;
	int windowHeight = 669;
	bool alwaysOntop = false;
	bool transparent = false;
	bool undecorated = false;
	int windowStartingX = NULL;
	int windowStartingY = NULL;

	// Core Options
	map<string, Stage> stages;
	map<string, Character> characters;

	// TO-DO: Clean up Stage and Character loading

	Config (string configLocation) {
		InitWindow(windowWidth, windowHeight, title.c_str());
		Load(configLocation);
		LoadCharacters();
		LoadStages();
	}

	void Reload(string configLocation) {
		Unload();
		Load(configLocation);
		LoadCharacters();
		LoadStages();
	}

	void ReloadApp (string configLocation) {
		Unload();
		CloseWindow();
		InitWindow(windowWidth, windowHeight, title.c_str());
		Load(configLocation);
		LoadCharacters();
		LoadStages();
	}

private:
	bool configIsLoaded = false;
	bool assestsAreLoaded = false;

	void Load (string configLocation) {
		std::ifstream i(configLocation);
		i >> configData;
		configPath = configLocation;

		SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

		try {
			try {
				language = configData.at("language");
				mkv::LoadKeycodeFile("./languages/" + language + ".json");
			} catch (json::exception err) {
			}

			json windowConfig = configData.at("window");

			try {
				windowWidth = windowConfig.at("width");
				windowHeight = windowConfig.at("height");
				SetWindowSize(windowWidth, windowHeight);
			} catch (json::exception err) {
			}

			try {
				title = windowConfig.at("title");
				SetWindowTitle(title.c_str());
			} catch (json::exception err) {
			}

			try {
				windowStartingX = windowConfig.at("x");
				windowStartingY = windowConfig.at("y");
				SetWindowPosition(windowStartingX, windowStartingY);
			} catch (json::exception err) {
				/*SetWindowPosition(
					(int)(GetMonitorWidth(GetCurrentMonitor()) / 2) - (windowWidth / 2),
					(int)(GetMonitorHeight(GetCurrentMonitor()) / 2) - (windowHeight / 2)
				);*/
			}

			try {
				alwaysOntop = windowConfig.at("alwaysOntop");
				if (alwaysOntop) SetWindowState(FLAG_WINDOW_TOPMOST);
			} catch (json::exception err) {
			}

			try {
				transparent = windowConfig.at("transparent");
				if (transparent) SetWindowState(FLAG_WINDOW_TRANSPARENT);
			} catch (json::exception err) {
			}

			try {
				undecorated = windowConfig.at("undecorated");
				if (undecorated) SetWindowState(FLAG_WINDOW_UNDECORATED);
			} catch (json::exception err) {
			}

		} catch (json::exception err) {
		}

		cache.width = windowWidth;
		cache.height = windowHeight;

		configIsLoaded = true;
	}

	map<string, Character> LoadCharacters () {
		for (json character : configData.at("characters")) {
			Character characterClass = { cache, character, windowWidth, windowHeight };
			characters.insert({ characterClass.id, characterClass });
		}

		return characters;
	}

	map<string, Stage> LoadStages () {
		for (json stage : configData.at("stages")) {
			std::cout << stage;
			Stage stageClass = { cache, stage, characters, windowWidth, windowHeight };
			stages.insert({ stageClass.id, stageClass });
		}

		return stages;
	}

	void Unload () {
		cache.RemoveAllTextures();
		ClearWindowState(FLAG_WINDOW_TOPMOST);
		ClearWindowState(FLAG_WINDOW_TRANSPARENT);
		ClearWindowState(FLAG_WINDOW_UNDECORATED);

		// Core Options
		UnloadCharacters();
		UnloadStages();

		// General Options
		title = "ManiaKV";
		language = "*en-US";

		// Window Options
		windowWidth = 1189;
		windowHeight = 669;
		alwaysOntop = false;
		transparent = false;
		undecorated = false;
		windowStartingX = NULL;
		windowStartingY = NULL;
	}

	void UnloadCharacters() {
		characters.clear();
	}

	void UnloadStages() {
		stages.clear();
	}
};

#endif // !CONFIG_HPP