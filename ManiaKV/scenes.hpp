#ifndef SCENES_HPP
#define SCENES_HPP

#include <string>
#include <vector>
#include <memory>

#include <lib/mkvlib.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

namespace scenes {
	namespace data {
		static bool languageInit = false;
		static int languageSelector = 0;
		static bool languageToggle = false;
	}

	void DrawMainScene (Renderer* renderer) {
		shared_ptr<Config> config = renderer->config();

		if (renderer->currentCharacters().size() < 1) {
			ClearBackground(RAYWHITE);
			DrawText("Please add characters to your scene", 10, config->windowHeight / 2, 20, LIGHTGRAY);
		} else {
			renderer->CheckHotkeys();

			int characterCount = (int)renderer->currentCharacters().size();
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

			// Draw background if exists
			try {
				DrawTexture(renderer->currentBackground(), 0, 0, WHITE);
			} catch (std::out_of_range) {
			}

			// Draw character bodies
			for (int i = 0; i < characterCount; i++) {
				try {
					shared_ptr<Character> character = renderer->currentCharacters()[i];
					DrawTexture(character->textures().at("body"), positions[i][0], positions[i][1], WHITE);
				} catch (std::out_of_range) {
				}
			}

			// Draw table if exists
			try {
				DrawTexture(renderer->currentTable(), 0, 0, WHITE);
			} catch (std::out_of_range) {
			}

			// Draw character keys
			for (int i = 0; i < characterCount; i++) {
				try {
					shared_ptr<Character> character = renderer->currentCharacters()[i];
					DrawTexture(character->textures().at("instrument"), positions[i][0], positions[i][1], WHITE);
				} catch (std::out_of_range) {
				}
			}

			// Draw Key Presses
			for (int i = 0; i < renderer->currentKeys().size(); i++) {
				Key key = renderer->currentKeys()[i];
				int size = characterCount > 1
					? i + 2 / 2 > renderer->currentKeys().size() / 2 ? 1 : 0
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

			if ((int)renderer->stages().at((string)mkv::GetState(mkv::STATES::STAGE)).data.at("keys").size() == 6) {
				ClearBackground(RAYWHITE);
				DrawText("As of right now, 6 key stages are broken :(", 10, 10, 20, RED);
			}
		}
	}

	void DrawSettings (Renderer* renderer) {
		shared_ptr<Config> config = renderer->config();

		ClearBackground(RAYWHITE);

		/*vector<string> keys = mkv::AreKeysPressed();
		if (keys.size() > 0) {
			string key = arrToStr(keys, " & ");
			DrawText(key.c_str(), __config.windowWidth / 5, __config.windowHeight / 5, 20, LIGHTGRAY);
		} else {
			DrawText("Press a key to check its keycode", __config.windowWidth / 5, __config.windowHeight / 5, 20, LIGHTGRAY);
		}*/

		GuiGroupBox({ 10, 10, (float)config->windowWidth - 20, (float)config->windowHeight - 20 }, "Settings");

		/* -Language Settings- */
		if (!data::languageInit) {
			data::languageSelector = config->GetLanguagePos(config->language);
			data::languageInit = true;
		}

		GuiDrawText("Language:", { 30, 20, 30, 25 }, 1, GRAY);
		int languageClick = GuiDropdownBox({ 80, 20, 100, 25 }, VectorToString(config->languages, ";").c_str(), &data::languageSelector, data::languageToggle);
		if (languageClick && !data::languageToggle) data::languageToggle = true;
		else if (languageClick && data::languageToggle) data::languageToggle = false;

		string languageSelected = config->languages[data::languageSelector];
		if (languageSelected != config->language) {
			config->SetLanguage(languageSelected);
		}

		if (mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::S })) {
			config->SaveConfig();
		}
		// ----------------------


		//DrawText(GetKeyPressed(), __config.windowWidth / 5, __config.windowHeight / 5, 20, LIGHTGRAY);
	}
}

#endif // !SCENES_HPP