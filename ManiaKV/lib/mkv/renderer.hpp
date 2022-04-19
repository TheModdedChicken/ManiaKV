#ifndef STAGES_HPP
#define STAGES_HPP

#include <lib/json.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "defs.hpp"
#include "key.hpp"
#include "config.hpp"
#include "stage.hpp"
#include "character.hpp"

namespace mkv {
	struct OverlayData {
		std::string type;
		std::string id;
		nlohmann::json body;
	};

	class Renderer {
	protected:
		std::shared_ptr<Config> _config;
		std::string _lastStage;
		std::string _activeScene = "none";
		Texture2D _currentBackground;
		Texture2D _currentTable;
		std::vector<std::shared_ptr<Character>> _currentCharacters;
		std::vector<Key> _currentKeys;
		std::map<std::string, Stage> _stages;
		std::map<std::string, std::vector<int>> _shortcuts;

		std::map<std::string, std::function<void(Renderer*)>> _scenes = {
			{ "none", [](Renderer* renderer) -> void {
				DrawText("Err: No scene selected", 10, renderer->config()->windowHeight / 2, 20, LIGHTGRAY);
			}}
		};

		std::map<std::string, std::function<void(Renderer*, mkv::OverlayData)>> _overlays = {};
		std::map<std::string, std::map<std::string, nlohmann::json>> _activeOverlays = {};

		int _frameCount = 0;

	public:
		std::shared_ptr<Config> const config();
		std::string const lastStage();
		std::string const currentScene();
		Texture2D const currentBackground();
		Texture2D const currentTable();
		std::vector<std::shared_ptr<Character>> const currentCharacters();
		std::vector<Key> const currentKeys();
		std::map<std::string, Stage> const stages();
		std::map<std::string, std::vector<int>> const shortcuts();

		Renderer (std::shared_ptr<Config> config);

		/* ~Scene Management */

		/*
			Get current render status of a scene
			0 = INVALID (Doesn't Exist)
			1 = INACTIVE (Not Rendering)
			2 = ACTIVE (Rendering)
		*/
		mkv::SceneRenderState GetSceneStatus (std::string id);

		// Set the current active scene
		void SetScene (std::string id);

		// Add a scene to the renderer
		void AddScene (std::string id, std::function<void(Renderer*)> func);

		// Remove a scene from the renderer
		void RemoveScene (std::string id);

		// -------------------


		/* ~Overlay Management */

		bool GetOverlayTypeStatus (std::string type);

		bool GetOverlayInstanceStatus (std::string type, std::string id);

		// Create overlay instace
		std::string InitializeOverlay (std::string type, nlohmann::json data = {});

		// Delete overlay instance
		void DestroyOverlay (std::string type, std::string id);

		// Add an overlay type to the renderer
		void AddOverlay (std::string id, std::function<void(Renderer*, mkv::OverlayData)> func);

		// Remove an overlay type from the renderer
		void RemoveOverlay (std::string type);

		// -------------------


		void CacheStages (std::vector<std::string> stageStrs);

		void LoadStage (std::string stageStr);

		void RenderData ();

		void Render ();

		void CheckHotkeys ();
	};
}

#endif // !STAGES_HPP