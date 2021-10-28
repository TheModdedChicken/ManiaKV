#pragma once

#include "Config.hpp"

class StageHandler {
public:
	Config *config;
	std::string currentStage;
	Texture2D currentBackground;
	Texture2D currentTable;
	std::vector<Character> currentCharacters;
	std::vector<Key> currentKeys;

	// TO-DO: Add session data file for state saving
	StageHandler (Config *configIn) {
		config = configIn;
		std::vector<std::string> stages = extract_keys(config->stages);
		// TO-DO: Pre-load all stages to ensure hotkeys are enabled immediately
		LoadStage(stages[0]);
	}

	void LoadStage (std::string stageStr) {
		Stage stage = config->stages.at(stageStr);
		currentStage = stage.id;
		currentBackground = stage.textures.at("background");
		currentTable = stage.textures.at("table");
		currentKeys = stage.keys;

		for (std::string stageCharacterStr : stage.characters) {
			for (std::string characterStr : extract_keys(config->characters)) {
				// TO-DO: Add check to ensure characters don't exceed key count
				if (stageCharacterStr == characterStr) currentCharacters.push_back(config->characters.at(stageCharacterStr));
			}
		}
	}

	void Render () {
		if (currentCharacters.size() > 2) {
			DrawText("Scenes cannot have more than two characters", 10, 30, 20, LIGHTGRAY);
		}

		DrawTexture(currentBackground, 0, 0, WHITE);

		// TO-DO Add dynamic loading
		for (Character character : currentCharacters) {
			DrawTexture(character.textures.at("body"), 0, 0, WHITE);
		}

		DrawTexture(currentTable, 0, 0, WHITE);

		for (Character character : currentCharacters) {
			DrawTexture(character.textures.at("instrument"), 0, 0, WHITE);
		}
		
		// Display Key Presses
		for (Key key : currentKeys) {
			bool checksPassed = true;

			for (int keyID : extract_keys(key.types)) {
				std::cout << keyID;
				if (IsKeyDownSW(keyID) != key.types.at(keyID)) checksPassed = false;
			}

			if (checksPassed) DrawTexture(key.texture, 0, 0, WHITE);
		}
	}
};