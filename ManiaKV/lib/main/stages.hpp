#ifndef STAGES_HPP
#define STAGES_HPP

#include <lib/raylib.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "../main/states.hpp"
#include "../main/config.hpp"
#include "../main/utility.hpp"
#include "../main/character.hpp"
#include "../components/Key.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;
using std::function;


//static map<int, vector< function<void(void)> >> renderFuncs;

class Renderer {
protected:
	shared_ptr<Config> _config;
	string _lastStage;
	Texture2D _currentBackground;
	Texture2D _currentTable;
	vector<shared_ptr<Character>> _currentCharacters;
	vector<Key> _currentKeys;
	map<string, Stage> _stages;
	map<string, vector<int>> _shortcuts;

	int _frameCount = 0;

public:
	Renderer (shared_ptr<Config> config): _config(config) {
		vector<string> stageStrs = extract_keys(_config->stages);

		CacheStages(stageStrs);
		try {
			LoadStage(mkv::GetState(mkv::STAGE));
		} catch ( ... ) {
			LoadStage(stageStrs[0]);
		}
	}

	void CacheStages (vector<string> stageStrs) {
		for (string stageStr : stageStrs) {
			Stage stage = _config->stages.at(stageStr);
			_stages.insert({ stage.id, stage });
			_shortcuts.insert({ stage.id, stage.shortcut });
		}
	}

	void LoadStage (string stageStr) {
		_currentCharacters.clear();
		_currentKeys.clear();

		Stage stage = _stages.at(stageStr);
		try {
			if (mkv::GetState(mkv::STAGE) != stage.id) _lastStage = mkv::GetState(mkv::STAGE);
		} catch (std::exception) {
			_lastStage = stage.id;
		}
		mkv::SetState(mkv::STAGE, stage.id);
		_currentBackground = stage.textures["background"];
		_currentTable = stage.textures["table"];
		_currentKeys = stage.keys;

		for (string character : stage.characters) {
			_currentCharacters.push_back(std::make_shared<Character>(_config->characters.at(character)));

			/*for (string characterStr : extract_keys(_config->characters)) {
				if (character.first == characterStr) _currentCharacters.push_back(_config->characters.at(character.first));
			}*/
		}
	}

	void RenderData () {
		DrawText(("Cur. Stage: " + (string)mkv::GetState(mkv::STAGE)).c_str(), 10, 5, 20, LIGHTGRAY);
		DrawText(("Last Stage: " + _lastStage).c_str(), 10, 25, 20, LIGHTGRAY);
		DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 45, 20, LIGHTGRAY);
	}

	void Render () {
		if (_currentCharacters.size() < 1) {
			ClearBackground(RAYWHITE);
			DrawText("Please add characters to your scene", 10, _config->windowHeight / 2, 20, LIGHTGRAY);
		} else {
			CheckHotkeys();

			int characterCount = (int)_currentCharacters.size();
			if (characterCount > 2) {
				DrawText("Scenes cannot have more than two characters", 10, 30, 20, LIGHTGRAY);
			}

			// Controlls sprite position
			vector<vector<int>> positions = {
				{
					characterCount > 1 ? -(_config->windowWidth * 20 / 100) : -(_config->windowWidth * 5 / 100),
					characterCount > 1 ? -((_config->windowHeight + 25) * 8 / 100) : -((_config->windowHeight + 25) * 2 / 100)
				},
				{
					_config->windowWidth * 20 / 100,
					(_config->windowHeight - 25) * 9 / 100
				}
			};

			// Draw background if exists
			try {
				DrawTexture(_currentBackground, 0, 0, WHITE);
			} catch (std::out_of_range) {
			}

			// Draw character bodies
			for (int i = 0; i < characterCount; i++) {
				try {
					shared_ptr<Character> character = _currentCharacters[i];
					DrawTexture(character->textures().at("body"), positions[i][0], positions[i][1], WHITE);
				} catch (std::out_of_range) {
				}
			}

			// Draw table if exists
			try {
				DrawTexture(_currentTable, 0, 0, WHITE);
			} catch (std::out_of_range) {
			}

			// Draw character keys
			for (int i = 0; i < characterCount; i++) {
				try {
					shared_ptr<Character> character = _currentCharacters[i];
					DrawTexture(character->textures().at("instrument"), positions[i][0], positions[i][1], WHITE);
				} catch (std::out_of_range) {
				}
			}

			// Draw Key Presses
			for (int i = 0; i < _currentKeys.size(); i++) {
				Key key = _currentKeys[i];
				int size = characterCount > 1
					? i + 2 / 2 > _currentKeys.size() / 2 ? 1 : 0
					: 0;

				bool checksPassed = true;

				for (int keyID : extract_keys(key.types)) {
					if (key.types.find(keyID) != key.types.end() && mkv::IsKeyDown(keyID) != key.types.at(keyID)) checksPassed = false;
				}

				try {
					if (checksPassed) DrawTexture(key.texture, positions[size][0], positions[size][1], WHITE);
				} catch (std::out_of_range) {
				}
			}
		}

		if (_frameCount > 60) _frameCount = 0;
		else _frameCount++;
	}

private:
	void CheckHotkeys () {
		for (string stage : extract_keys(_shortcuts)) {
			bool isPressed = true;

			for (int key : _shortcuts.at(stage)) {
				if (!mkv::IsKeyDown(key)) isPressed = false;
			}

			if (isPressed) LoadStage(stage);
		}
	}
};

#endif // !STAGES_HPP