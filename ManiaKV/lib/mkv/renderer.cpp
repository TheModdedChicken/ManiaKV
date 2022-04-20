#include <lib/raylib.h>
#include <lib/json.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "renderer.hpp"
#include "defs.hpp"
#include "input.hpp"
#include "states.hpp"
#include "config.hpp"
#include "utility.hpp"
#include "character.hpp"
#include "key.hpp"
#include "stage.hpp"

using nlohmann::json;
using std::string;
using std::shared_ptr;
using std::vector;
using std::map;
using std::function;

namespace mkv {
	shared_ptr<Config> const Renderer::config() {
		return _config;
	}
	string const Renderer::lastStage() {
		return _lastStage;
	}
	string const Renderer::currentScene() {
		return _activeScene;
	}
	Texture2D const Renderer::currentBackground() {
		return _currentBackground;
	}
	Texture2D const Renderer::currentTable() {
		return _currentTable;
	}
	vector<shared_ptr<Character>> const Renderer::currentCharacters() {
		return _currentCharacters;
	}
	vector<Key> const Renderer::currentKeys() {
		return _currentKeys;
	}
	map<string, Stage> const Renderer::stages() {
		return _stages;
	}
	map<string, vector<int>> const Renderer::shortcuts() {
		return _shortcuts;
	}

	Renderer::Renderer (shared_ptr<Config> config) : _config(config) {
		vector<string> stageStrs = mkv::extract_keys(_config->stages);
		if (stageStrs.empty()) throw "mkv::1::no_stages";

		CacheStages(stageStrs);
		auto stage = mkv::GetState(mkv::STAGE);
		if (stage != std::nullopt) LoadStage(stage.value());
		else LoadStage(stageStrs[0]);
	}

	/* ~Scene Management */

	/*
		Get current render status of a scene
		0 = INVALID (Doesn't Exist)
		1 = INACTIVE (Not Rendering)
		2 = ACTIVE (Rendering)
	*/
	mkv::SceneRenderState Renderer::GetSceneStatus (string id) {
		if (!mkv::ExistsInMap(_scenes, id)) return mkv::SceneRenderState::INVALID;
		if (id != _activeScene) return mkv::SceneRenderState::INACTIVE;
		else return mkv::SceneRenderState::ACTIVE;
	}

	// Set the current active scene
	void Renderer::SetScene (string id) {
		if (!mkv::ExistsInMap(_scenes, id)) throw new mkv::Error("Scene doesn't exist", "invalid_scene_id");
		_activeScene = id;
	}

	// Add a scene to the renderer
	void Renderer::AddScene (string id, function<void(Renderer*)> func) {
		if (mkv::ExistsInMap(_scenes, id)) throw new mkv::Error("Scene already exists", "scene_exists");
		_scenes[id] = func;
	}

	// Remove a scene from the renderer
	void Renderer::RemoveScene (string id) {
		if (!mkv::ExistsInMap(_scenes, id)) throw new mkv::Error("Scene doesn't exist", "invalid_scene_id");
		_scenes.erase(id);
	}

	// -------------------


	/* ~Overlay Management */

	bool Renderer::GetOverlayTypeStatus (string type) {
		if (!mkv::ExistsInMap(_overlays, type)) return false;
		else return true;
	}

	bool Renderer::GetOverlayInstanceStatus (string type, string id) {
		if (!mkv::ExistsInMap(_overlays, type)) return false;
		if (!mkv::ExistsInMap(_activeOverlays[type], id)) return false;
		else return true;
	}

	// Create overlay instace
	string Renderer::InitializeOverlay (string type, json data) {
		if (!mkv::ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		string id = mkv::RandString(15);
		_activeOverlays[type].insert({ id, data });
		return id;
	}

	// Delete overlay instance
	void Renderer::DestroyOverlay (string type, string id) {
		if (!mkv::ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		if (!mkv::ExistsInMap(_activeOverlays.at(type), id)) throw new mkv::Error("Overlay id doesn't exist", "invalid_overlay_id");
		_activeOverlays[type].erase(id);
	}

	// Add an overlay type to the renderer
	void Renderer::AddOverlay (string id, function<void(Renderer*, OverlayData)> func) {
		if (mkv::ExistsInMap(_overlays, id)) throw new mkv::Error("Overlay type already exists", "overlay_type_exists");
		_overlays[id] = func;
	}

	// Remove an overlay type from the renderer
	void Renderer::RemoveOverlay (string type) {
		if (!mkv::ExistsInMap(_overlays, type)) throw new mkv::Error("Overlay type doesn't exist", "invalid_overlay_type");
		_overlays.erase(type);
		_activeOverlays.erase(type);
	}

	// -------------------


	void Renderer::CacheStages (vector<string> stageStrs) {
		for (string stageStr : stageStrs) {
			Stage stage = _config->stages.at(stageStr);
			_stages.insert({ stage.id, stage });
			_shortcuts.insert({ stage.id, stage.shortcut });
		}
	}

	void Renderer::LoadStage (string stageStr) {
		_currentCharacters.clear();
		_currentKeys.clear();

		Stage stage = _stages.at(stageStr);
		try {
			if (mkv::GetState(mkv::STAGE) != stage.id) _lastStage = mkv::GetState(mkv::STAGE).value();
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

	void Renderer::RenderData () {
		DrawText(("Cur. Stage: " + (string)mkv::GetState(mkv::STAGE).value()).c_str(), 10, 5, 20, LIGHTGRAY);
		DrawText(("Last Stage: " + _lastStage).c_str(), 10, 25, 20, LIGHTGRAY);
		DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 45, 20, LIGHTGRAY);
	}

	void Renderer::Render () {
		// Render Scene
		try {
			_scenes[_activeScene](this);
		} catch (...) {
		}

		// Render Overlays
		for (std::pair<string, map<string, json>> activeOverlayType : _activeOverlays) {
			for (std::pair<string, json> activeOverlayInstance : activeOverlayType.second) {
				_overlays[activeOverlayType.first](this, {
					activeOverlayType.first,
					activeOverlayInstance.first,
					activeOverlayInstance.second
					});
			}
		}

		if (_frameCount > 60) _frameCount = 0;
		else _frameCount++;
	}

	void Renderer::CheckHotkeys () {
		for (string stage : mkv::extract_keys(_shortcuts)) {
			bool isPressed = true;

			for (int key : _shortcuts.at(stage)) {
				if (!mkv::IsKeyDown(key)) isPressed = false;
			}

			if (isPressed) LoadStage(stage);
		}
	}
}