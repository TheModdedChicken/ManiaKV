#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <memory>

#include "Config.hpp"
#include "utility.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;

class StageHandler {
public:
	shared_ptr<Config> config;
	string currentStage;
	string lastStage;
	Texture2D currentBackground;
	Texture2D currentTable;
	vector<Character> currentCharacters;
	vector<Key> currentKeys;
	map<string, Stage> stages;
	map<string, vector<int>> shortcuts;

	int frameCount = 0;

	// TO-DO: Add session data file for state saving
	StageHandler (shared_ptr<Config> configIn) {
		config = configIn;
		vector<string> stageStrs = extract_keys(config->stages);

		CacheStages(stageStrs);
		LoadStage(stageStrs[0]);
	}

	void CacheStages (vector<string> stageStrs) {
		for (string stageStr : stageStrs) {
			Stage stage = config->stages.at(stageStr);
			stages.insert({ stage.id, stage });
			shortcuts.insert({ stage.id, stage.shortcut });
		}
	}

	void LoadStage (string stageStr) {
		currentCharacters.clear();
		currentKeys.clear();

		Stage stage = stages.at(stageStr);
		if (currentStage != stage.id) lastStage = currentStage;
		currentStage = stage.id;
		currentBackground = stage.textures.at("background");
		currentTable = stage.textures.at("table");
		currentKeys = stage.keys;

		for (string stageCharacterStr : stage.characters) {
			for (string characterStr : extract_keys(config->characters)) {
				if (stageCharacterStr == characterStr) currentCharacters.push_back(config->characters.at(stageCharacterStr));
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
			DrawTexture(character.textures.at("main").at("body"), positions[i][0], positions[i][1], WHITE);
		}

		DrawTexture(currentTable, 0, 0, WHITE);

		for (int i = 0; i < characterCount; i++) {
			Character character = currentCharacters[i];
			DrawTexture(character.textures.at("main").at("instrument"), positions[i][0], positions[i][1], WHITE);
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

			if (checksPassed) DrawTexture(key.texture, positions[size][0], positions[size][1], WHITE);
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