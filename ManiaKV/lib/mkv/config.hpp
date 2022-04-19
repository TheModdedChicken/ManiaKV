#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <lib/json.hpp>
#include <string>
#include <vector>
#include <map>

#include "character.hpp"
#include "stage.hpp"

class Config {
public:
	std::string configPath;
	nlohmann::json configData;

	// General Options
	std::string title = "ManiaKV";
	std::string language = "*en-US";

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
	std::vector<std::string> languages = {};
	std::map<std::string, Stage> stages = {};
	std::map<std::string, Character> characters = {};


	Config (std::string configLocation);

	void SaveConfig ();

	void BackupConfig ();

	int GetLanguagePos (std::string id);

	void SetLanguage (std::string id);

	void Reload(std::string configLocation);

	void ReloadApp (std::string configLocation);

private:
	bool configIsLoaded = false;
	bool assestsAreLoaded = false;

	void WriteConfig(std::string path);

	void Load (std::string configLocation);

	void LoadLanguage (std::string id);

	void LoadCharacters ();

	void LoadStages ();

	void Unload ();

	void UnloadCharacters();

	void UnloadStages();
};

#endif // !CONFIG_HPP