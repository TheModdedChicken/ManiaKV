#include <string>
#include <vector>
#include <ostream>
#include "json.hpp"
#include "Character.hpp"
#include "input.hpp"
#include "Key.hpp"
#include "utility.hpp"

using json = nlohmann::json;

class Stage {
public:
	json stageJson;

	int hotkey = -1;
	int stageWidth;
	int stageHeight;

	std::string id;
	std::vector<std::string> characters;
	std::vector<Key> keys;
	std::map<std::string, Texture2D> textures;

	Stage (json stageJsonIn, std::map<std::string, Character> charactersIn, int widthIn, int heightIn) {
		characterMap = charactersIn;
		stageJson = stageJsonIn;
		stageWidth = widthIn;
		stageHeight = heightIn;
		LoadStage();
	}

	// TO-DO: Add reload function
private:
	void LoadStage () {
		// TO-DO: Add better checks for property presence

		try {
			hotkey = stageJson.at("hotkey");
		} catch (json::exception err) {
		};

		try {
			id = stageJson.at("id");
			std::vector<int> availableKeys;
			for (std::string key : stageJson.at("keys")) {
				availableKeys.push_back(GetKeyCode(key));
			}

			bool isOdd = availableKeys.size() % 2 == 1;
			bool wow = false;
			int i = 0;
			for (std::string character : stageJson.at("characters")) {
				Character characterClass = characterMap.at(character);
				characters.push_back(character);
				
				for (std::string texture : extract_keys(characterMap.at(character).textures.at("keys"))) {
					std::cout << "\n";
					std::cout << texture;
					std::cout << "\n";

					if (texture.find("idle") != -1) {
						std::map<int, bool> keyMap = {
							{availableKeys[i + 1], false},
							{availableKeys[i], false}
						};
						keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
					} else if (texture.find("key1-2") != -1 || texture.find("key3-4") != -1) {
						std::map<int, bool> keyMap = {
							{availableKeys[i - 1], true},
							{availableKeys[i], true}
						};
						keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
					} else {
						if (wow == false && isOdd && i == std::floor(availableKeys.size() / 2)) {
							std::map<int, bool> keyMap;
							if (texture.find("key1") != -1) {
								keyMap = {
									{availableKeys[i + 1], false},
									{availableKeys[i], true}
								};
								i++;
								wow = true;
							} else {
								keyMap = {
									{availableKeys[i - 1], false},
									{availableKeys[i], true}
								};
							}
							keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
						} else {
							std::map<int, bool> keyMap = {
								{availableKeys[texture.find("key1") != -1 || texture.find("key3") != -1 
									? i + 1
									: i - 1
								], false},
								{availableKeys[i], true}
							};
							keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
							i++;
						}
					}
				}
			}

			// Arrange hand textures
			// TO-DO: Add hand logic
			/*
				- Can only have 1 more key texture than actual keys:
					If one extra key texture is present then it will be paired with another key texture
				- Cannot have more keys than key textures
				- Can only have 2 or 4 keys per character
				- Can only have 1-2 characters
			*/

			// Load table texture
			std::string table = userdataF += stageJson.at("table");
			Image tableImage = LoadImage(table.c_str());
			ImageResize(&tableImage, stageWidth, stageHeight);
			Texture2D tableTexture = LoadTextureFromImage(tableImage);
			textures.insert(
				std::pair<std::string, Texture2D>("table", tableTexture)
			);

			// Load background texture
			std::string background = userdataF += stageJson.at("background");
			Image backgroundImage = LoadImage(table.c_str());
			ImageResize(&backgroundImage, stageWidth, stageHeight);
			Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
			textures.insert(
				std::pair<std::string, Texture2D>("background", backgroundTexture)
			);
		} catch (json::exception err) {
			std::cout << err.what();
			throw err;
		}
	}

	void UnloadCharacter() {
		const std::vector<Texture2D> textureValues = extract_values(textures);
		for (const Texture2D& texture : textureValues) {
			UnloadTexture(texture);
		}
	}

	std::map<std::string, Character> characterMap;
	std::string userdataF = "./userdata/";
};