#pragma once

#include <string>
#include "Config.hpp"

class StageHandler {
public:
	Config* config;
	std::string currentStage;
	Texture2D currentBackground;
	Texture2D currentTable;
	std::vector<Character> currentCharacters;
	std::vector<Key> currentKeys;
	std::map<std::string, Stage> stages;
	std::map<std::string, std::string> hotkeys;

	// TO-DO: Add session data file for state saving
	StageHandler (Config* configIn) {
		config = configIn;
		std::vector<std::string> stageStrs = extract_keys(config->stages);

		CacheStages(stageStrs);
		LoadStage(stageStrs[1]);
	}

	void CacheStages (std::vector<std::string> stageStrs) {
		for (std::string stageStr : stageStrs) {
			Stage stage = config->stages.at(stageStr);
			stages.insert({ stage.id, stage });
			hotkeys.insert({ std::to_string(stage.hotkey), stage.id });
		}
	}

	void LoadStage (std::string stageStr) {
		currentCharacters.clear();
		currentKeys.clear();

		Stage stage = stages.at(stageStr);
		currentStage = stage.id;
		currentBackground = stage.textures.at("background");
		currentTable = stage.textures.at("table");
		currentKeys = stage.keys;

		for (std::string stageCharacterStr : stage.characters) {
			for (std::string characterStr : extract_keys(config->characters)) {
				if (stageCharacterStr == characterStr) currentCharacters.push_back(config->characters.at(stageCharacterStr));
			}
		}
	}

	void CheckHotkeys () {
		for (std::string hotkey : extract_keys(hotkeys)) {
			if (IsKeyDownSW(GetKeyCode("CTRL")) && IsKeyDownSW(GetKeyCode("SHIFT")) && IsKeyDownSW(GetKeyCode(hotkey))) {
				LoadStage(hotkeys.at(hotkey));
			}
		}
	}

	void Render () {
		int characterCount = currentCharacters.size();
		if (characterCount > 2) {
			DrawText("Scenes cannot have more than two characters", 10, 30, 20, LIGHTGRAY);
		}

		// Controlls sprite size
		std::vector<std::vector<int>> sizes = {
			{
				characterCount > 1 ? -(config->windowWidth * 20 / 100) : -(config->windowWidth * 5 / 100),
				characterCount > 1 ? -((config->windowHeight + 25) * 8 / 100) : -((config->windowHeight + 25) * 2 / 100)
			},
			{
				config->windowWidth * 20 / 100,
				(config->windowHeight - 25) * 9 / 100
			}
		};

		DrawTexture(currentBackground, 0, 0, WHITE);

		for (int i = 0; i < characterCount; i++) {
			Character character = currentCharacters[i];
			DrawTexture(character.textures.at("main").at("body"), sizes[i][0], sizes[i][1], WHITE);
		}

		DrawTexture(currentTable, 0, 0, WHITE);

		for (int i = 0; i < characterCount; i++) {
			Character character = currentCharacters[i];
			DrawTexture(character.textures.at("main").at("instrument"), sizes[i][0], sizes[i][1], WHITE);
		}

		// Display Key Presses
		for (int i = 0; i < currentKeys.size(); i++) {
			Key key = currentKeys[i];
			int size = characterCount > 1
				? i + 2 / 2 > currentKeys.size() / 2 ? 1 : 0
				: 0;

			bool checksPassed = true;

			for (int keyID : extract_keys(key.types)) {
				if (key.types.find(keyID) != key.types.end() && IsKeyDownSW(keyID) != key.types.at(keyID)) checksPassed = false;
			}

			if (checksPassed) DrawTexture(key.texture, sizes[size][0], sizes[size][1], WHITE);
		}
	}
};