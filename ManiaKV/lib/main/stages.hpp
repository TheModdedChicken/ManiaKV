#ifndef STAGES_HPP
#define STAGES_HPP

#include "raylib.h"
#include <string>
#include <vector>
#include <memory>

#include "../main/states.hpp"
#include "../main/Config.hpp"
#include "../main/utility.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;

class StageController {
public:
	shared_ptr<Config> __config;
	string currentStage;
	string lastStage;
	string currentBackground;
	string currentTable;
	vector<Character> currentCharacters;
	vector<Key> currentKeys;
	map<string, Stage> stages;
	map<string, vector<int>> shortcuts;

	int frameCount = 0;

	// TO-DO: Add session data file for state saving
	StageController (shared_ptr<Config> config) {
		__config = config;
		vector<string> stageStrs = extract_keys(__config->stages);

		CacheStages(stageStrs);
		try {
			LoadStage(GetState("stage"));
		} catch (json::exception) {
			LoadStage(stageStrs[0]);
		}
	}

	void CacheStages (vector<string> stageStrs) {
		for (string stageStr : stageStrs) {
			Stage stage = __config->stages.at(stageStr);
			stages.insert({ stage.id, stage });
			shortcuts.insert({ stage.id, stage.shortcut });
		}
	}

	void LoadStage (string stageStr) {
		currentCharacters.clear();
		currentKeys.clear();

		Stage stage = stages.at(stageStr);
		if (currentStage != stage.id) lastStage = currentStage;
		SetState("stage", stage.id);
		currentStage = stage.id;
		currentBackground = stage.textures["background"];
		currentTable = stage.textures["table"];
		currentKeys = stage.keys;

		for (string stageCharacterStr : stage.characters) {
			for (string characterStr : extract_keys(__config->characters)) {
				if (stageCharacterStr == characterStr) currentCharacters.push_back(__config->characters.at(stageCharacterStr));
			}
		}
	}

	void RenderData () {
		DrawText(("Cur. Stage: " + currentStage).c_str(), 10, 5, 20, LIGHTGRAY);
		DrawText(("Last Stage: " + lastStage).c_str(), 10, 25, 20, LIGHTGRAY);
		DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 45, 20, LIGHTGRAY);
	}

	void Render () {
		CheckHotkeys();

		int characterCount = (int)currentCharacters.size();
		if (characterCount > 2) {
			DrawText("Scenes cannot have more than two characters", 10, 30, 20, LIGHTGRAY);
		}

		// Controlls sprite position
		vector<vector<int>> positions = {
			{
				characterCount > 1 ? -(__config->windowWidth * 20 / 100) : -(__config->windowWidth * 5 / 100),
				characterCount > 1 ? -((__config->windowHeight + 25) * 8 / 100) : -((__config->windowHeight + 25) * 2 / 100)
			},
			{
				__config->windowWidth * 20 / 100,
				(__config->windowHeight - 25) * 9 / 100
			}
		};

		// Draw background if exists
		try {
			DrawTexture(__config->cache.GetTexture(currentBackground), 0, 0, WHITE);
		} catch (std::out_of_range) {
		}

		for (int i = 0; i < characterCount; i++) {
			try {
				Character character = currentCharacters[i];
				DrawTexture(__config->cache.GetTexture(character.textures.at("main").at("body")), positions[i][0], positions[i][1], WHITE);
			} catch (std::out_of_range) {
			}
		}

		// Draw table if exists
		try {
			DrawTexture(__config->cache.GetTexture(currentTable), 0, 0, WHITE);
		} catch (std::out_of_range) {
		}

		for (int i = 0; i < characterCount; i++) {
			try {
				Character character = currentCharacters[i];
				DrawTexture(__config->cache.GetTexture(character.textures.at("main").at("instrument")), positions[i][0], positions[i][1], WHITE);
			} catch (std::out_of_range) {
			}
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

			try {
				if (checksPassed) DrawTexture(__config->cache.GetTexture(key.texture), positions[size][0], positions[size][1], WHITE);
			} catch (std::out_of_range) {
			}
		}

		if (frameCount > 60) frameCount = 0;
		else frameCount++;
	}

private:
	void CheckHotkeys () {
		for (string stage : extract_keys(shortcuts)) {
			bool isPressed = true;

			for (int key : shortcuts.at(stage)) {
				if (!IsKeyDownSW(key)) isPressed = false;
			}

			if (isPressed) LoadStage(stage);
		}
	}
};

#endif // !STAGES_HPP