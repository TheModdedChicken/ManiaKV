#ifndef STAGES_HPP
#define STAGES_HPP

#include <lib/raylib.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <optional>

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

class Renderer;

struct OverlayData {
	Renderer* renderer;
	std::string type;
	std::string id;
	json body;
};

//static map<int, vector< function<void(void)> >> renderFuncs;
class Renderer {
protected:
	shared_ptr<Config> _config;
	string _lastStage;
	string _activeScene = "none";
	Texture2D _currentBackground;
	Texture2D _currentTable;
	vector<shared_ptr<Character>> _currentCharacters;
	vector<Key> _currentKeys;
	map<string, Stage> _stages;
	map<string, vector<int>> _shortcuts;

	map<string, function<void(Renderer*)>> _scenes = {
		{ "none", [](Renderer *renderer) -> void {
			DrawText("Err: No scene selected", 10, renderer->config()->windowHeight / 2, 20, LIGHTGRAY);
		}}
	};

	map<string, function<void(OverlayData)>> _overlays = {};
	map<string, map<string, json>> _activeOverlays = {};

	int _frameCount = 0;

public:
	shared_ptr<Config> const config() { return _config; }
	string const lastStage() { return _lastStage; }
	string const currentScene() { return _activeScene; }
	Texture2D const currentBackground() { return _currentBackground; }
	Texture2D const currentTable() { return _currentTable; }
	vector<shared_ptr<Character>> const currentCharacters() { return _currentCharacters; }
	vector<Key> const currentKeys() { return _currentKeys; }
	map<string, Stage> const stages() { return _stages; }
	map<string, vector<int>> const shortcuts() { return _shortcuts; }

	Renderer (shared_ptr<Config> config): _config(config) {
		vector<string> stageStrs = extract_keys(_config->stages);
		if (stageStrs.empty()) return;

		CacheStages(stageStrs);
		try {
			LoadStage(mkv::GetState(mkv::STAGE));
		} catch (...) {
			LoadStage(stageStrs[0]);
		}
	}

	/* ~Scene Management */

	/*
		Get current render status of a scene
		0 = INVALID (Doesn't Exist)
		1 = INACTIVE (Not Rendering)
		2 = ACTIVE (Rendering)
	*/
	mkv::SceneRenderState GetSceneStatus (string id) {
		if (!ExistsInMap(_scenes, id)) return mkv::SceneRenderState::INVALID;
		if (id != _activeScene) return mkv::SceneRenderState::INACTIVE;
		else return mkv::SceneRenderState::ACTIVE;
	}

	// Set the current active scene
	void SetScene (string id) {
		if (!ExistsInMap(_scenes, id)) throw new mkv::Error("Scene doesn't exist", "invalid_scene_id");
		_activeScene = id;
	}

	// Add a scene to the renderer
	void AddScene (string id, function<void(Renderer*)> func) {
		if (ExistsInMap(_scenes, id)) throw new mkv::Error("Scene already exists", "scene_exists");
		_scenes[id] = func;
	}

	// Remove a scene from the renderer
	void RemoveScene (string id) {
		if (!ExistsInMap(_scenes, id)) throw new mkv::Error("Scene doesn't exist", "invalid_scene_id");
		_scenes.erase(id);
	}

	// -------------------


	/* ~Overlay Management */

	bool GetOverlayTypeStatus (string type) {
		if (!ExistsInMap(_overlays, type)) return false;
		else return true;
	}

	bool GetOverlayInstanceStatus (string type, string id) {
		if (!ExistsInMap(_overlays, type)) return false;
		if (!ExistsInMap(_activeOverlays[type], id)) return false;
		else return true;
	}

	// Create overlay instace
	string InitializeOverlay (string type, json data = {}) {
		if (!ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		string id = RandString(15);
		_activeOverlays[type].insert({ id, data });
		return id;
	}

	// Delete overlay instance
	void DestroyOverlay (string type, string id) {
		if (!ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		if (!ExistsInMap(_activeOverlays.at(type), id)) throw new mkv::Error("Overlay id doesn't exist", "invalid_overlay_id");
		_activeOverlays[type].erase(id);
	}

	// Add an overlay type to the renderer
	void AddOverlay (string id, function<void(OverlayData)> func) {
		if (ExistsInMap(_overlays, id)) throw new mkv::Error("Overlay type already exists", "overlay_type_exists");
		_overlays[id] = func;
	}

	// Remove an overlay type from the renderer
	void RemoveOverlay (string type) {
		if (!ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		_overlays.erase(type);
		_activeOverlays.erase(type);
	}

	// -------------------


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
		// Render Scene
		try {
			_scenes[_activeScene](this);
		} catch (...) {}

		// Render Overlays
		for (std::pair<string, map<string, json>> activeOverlayType : _activeOverlays) {
			for (std::pair<string, json> activeOverlayInstance : activeOverlayType.second) {
				_overlays[activeOverlayType.first]({ 
					this, 
					activeOverlayType.first,
					activeOverlayInstance.first, 
					activeOverlayInstance.second 
				});
			}
		}

		if (_frameCount > 60) _frameCount = 0;
		else _frameCount++;
	}

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