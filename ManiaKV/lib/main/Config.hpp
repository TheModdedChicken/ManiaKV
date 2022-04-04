#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <lib/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>

#include "input.hpp"

#include "../main/defs.hpp"
#include "../main/Character.hpp"
#include "../main/console.hpp"
#include "../components/Stage.hpp"

using nlohmann::json;
using std::string;
using std::map;
namespace fs = std::filesystem;

class Config {
public:
	string configPath;
	json configData;

	// General Options
	string title = "ManiaKV";
	string language = "*en-US";

	// Window Options
	bool failedToLoad = false;
	int windowWidth = 594;
	int windowHeight = 334;
	bool alwaysOntop = false;
	bool transparent = false;
	bool undecorated = false;
	int windowStartingX = NULL;
	int windowStartingY = NULL;

	// Core Options
	vector<string> languages = {};
	map<string, Stage> stages = {};
	map<string, Character> characters = {};

	// TO-DO: Clean up Stage and Character loading

	Config (string configLocation) {
		console::log("Initializing application...", __THISFILE__);

		InitWindow(windowWidth, windowHeight, title.c_str());
		try {
			Load(configLocation);
			LoadCharacters();
			LoadStages();
		} catch (...) {
			failedToLoad = true;
		}
	}

	// Fix config saving
	void SaveConfig () {
		console::log("Saving config...", __THISFILE__);
		WriteConfig(mkv::configPath);
	}

	void BackupConfig () {
		console::log("Backing up config...", __THISFILE__);
		WriteConfig(mkv::backupConfigPath);
	}

	int GetLanguagePos (string id) {
		return GetIndexInVector(languages, id);
	}

	void SetLanguage (string id) {
		if (std::find(languages.begin(), languages.end(), id) != languages.end()) {
			LoadLanguage(id);
			configData["language"] = id;
			BackupConfig();
		}
	}

	void Reload(string configLocation) {
		console::log("Reloading config...", __THISFILE__);

		Unload();
		Load(configLocation);
		LoadCharacters();
		LoadStages();
	}

	void ReloadApp (string configLocation) {
		console::log("Reloading application...", __THISFILE__);

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

	void WriteConfig(string path) {
		console::log("Wrote cached config to: " + path, __THISFILE__);

		std::ofstream o(path);
		o << std::setw(2) << configData << std::endl;
	}

	void Load (string configLocation) {
		console::log("Loading config...", __THISFILE__);

		std::ifstream i(configLocation);
		i >> configData;
		configPath = configLocation;

		SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

		try {
			try {
				console::log("Loading languages...", __THISFILE__);
				language = configData.at("language");

				for (const auto& entry : fs::directory_iterator("./languages/")) {
					string path = entry.path().u8string();
					int substr = path.find_last_of("/");
					string nameExt = path.substr((int)substr + 1);
					int extLoc = nameExt.find_last_of(".");

					string name = nameExt.substr(0, extLoc);
					string ext = nameExt.substr(extLoc, nameExt.length());

					if (ext == ".json") {
						languages.push_back(name);
						console::log("Found language: " + name, __THISFILE__);
					}
				}

				LoadLanguage(language);
			} catch (json::exception err) {
			}

			console::log("Loading window properties...", __THISFILE__);
			json windowConfig = configData.at("window");

			try {
				windowWidth = windowConfig.at("width");
				windowHeight = windowConfig.at("height");
				SetWindowSize(windowWidth, windowHeight);

				console::log("Loaded window size: W-" + std::to_string(windowWidth) + " H-" + std::to_string(windowHeight), __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load window size. Loading defaults: W-" + std::to_string(windowWidth) + " H-" + std::to_string(windowHeight), __THISFILE__);
			}

			try {
				title = windowConfig.at("title");
				SetWindowTitle(title.c_str());

				console::log("Loaded window title: " + title, __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load window title. Loading default: " + title, __THISFILE__);
			}

			try {
				windowStartingX = windowConfig.at("x");
				windowStartingY = windowConfig.at("y");
				SetWindowPosition(windowStartingX, windowStartingY);

				console::log("Loaded window position: X-" + std::to_string(windowStartingX) + " Y-" + std::to_string(windowStartingY), __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load window position. Loading defaults: X-" + std::to_string(windowStartingX) + " Y-" + std::to_string(windowStartingY), __THISFILE__);
			}

			try {
				alwaysOntop = windowConfig.at("alwaysOntop");
				if (alwaysOntop) SetWindowState(FLAG_WINDOW_TOPMOST);

				console::log("Loaded property 'alwaysOntop': " + BoolToString(alwaysOntop), __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load property 'alwaysOntop'. Loading default: " + BoolToString(alwaysOntop), __THISFILE__);
			}

			try {
				transparent = windowConfig.at("transparent");
				if (transparent) SetWindowState(FLAG_WINDOW_TRANSPARENT);
				console::log("Loaded property 'transparent': " + BoolToString(transparent), __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load property 'transparent'. Loading default: " + BoolToString(transparent), __THISFILE__);
			}

			try {
				undecorated = windowConfig.at("undecorated");
				if (undecorated) SetWindowState(FLAG_WINDOW_UNDECORATED);

				console::log("Loaded property 'undecorated': " + BoolToString(undecorated), __THISFILE__);
			} catch (json::exception err) {
				console::log("Failed to load property 'undecorated'. Loading default: " + BoolToString(undecorated), __THISFILE__);
			}

		} catch (json::exception err) {
			console::log("Something went wrong when trying to load your config file.", __THISFILE__);
		}

		configIsLoaded = true;
	}

	void LoadLanguage (string id) {
		if (std::find(languages.begin(), languages.end(), id) != languages.end()) {
			mkv::LoadKeycodeFile("./languages/" + id + ".json");
			language = id;

			console::log("Loaded language: " + id, __THISFILE__);
		}
	}

	void LoadCharacters () {
		console::log("Loading characters...", __THISFILE__);

		for (json character : configData.at("characters")) {
			characters.insert({ character.at("id"), CreateCharacter(character, windowWidth, windowHeight)});
			console::log("Loaded character: " + (string)character.at("id"), __THISFILE__);
		}
	}

	void LoadStages () {
		console::log("Loading stages...", __THISFILE__);

		for (json stage : configData.at("stages")) {
			console::log((string)stage.at("id") + " " + stage.dump(), "config.hpp");
			Stage stageClass = { stage, std::make_shared<map<string, Character>>(characters), windowWidth, windowHeight };
			stages.insert({ stageClass.id, stageClass });
			console::log("Loaded stage: " + stageClass.id, __THISFILE__);
		}
	}

	void Unload () {
		console::log("Unloading config...", __THISFILE__);

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
		console::log("Unloading characters...", __THISFILE__);

		for (std::pair<string, Character> characterPair : characters) {
			characterPair.second.UnloadTextures();
			console::log("Unloaded character: " + characterPair.first, __THISFILE__);
		}
		characters.clear();
	}

	void UnloadStages() {
		console::log("Unloading stages...", __THISFILE__);

		for (std::pair<string, Stage> stagePair : stages) {
			stagePair.second.UnloadTextures();
			console::log("Unloaded stage: " + stagePair.first, __THISFILE__);
		}
		stages.clear();
	}
};

#endif // !CONFIG_HPP