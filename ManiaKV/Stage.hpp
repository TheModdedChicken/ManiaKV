#include <string>
#include <vector>
#include <ostream>
#include "json.hpp"
#include "Character.hpp"
#include "input.hpp"
#include "Key.hpp"

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
			int reservedKeys = 0;
			std::vector<int> availableKeys;

			for (std::string key : stageJson.at("keys")) {
				availableKeys.push_back(GetKeyCode(key));
			}
			
			// Fix key loading
			for (std::string character : stageJson.at("characters")) {
				Character characterClass = characterMap.at(character);
				if (reservedKeys >= availableKeys.size()) break;

				int i = 0;
				for (std::string texture : extract_keys(characterClass.textures)) {
					switch (characterClass.keys) {
						case 2:
						{
							if (texture.find("key1-2") > -1) {
								std::map<int, bool> keyMap = {
									{availableKeys[i - 1], true},
									{availableKeys[i], true}
								};

								Key key = { keyMap, characterClass.textures.at(texture) };
								keys.push_back(key);
							} else if (texture.find("body") == -1 && texture.find("instrument") == -1 && texture.find("idle") == -1) {
								std::map<int, bool> keyMap = {
									{availableKeys[i == 1 ? i - 1 : i + 1], false},
									{availableKeys[i], true}
								};

								Key key = { keyMap, characterClass.textures.at(texture) };
								keys.push_back(key);
								i++;
							}
						} break;
						case 4:
						{
							if (texture.find("key1-2") > -1 || texture.find("key3-4") > -1) {
								std::map<int, bool> keyMap = {
									{availableKeys[i - 1], true},
									{availableKeys[i], true}
								};

								Key key = { keyMap, characterClass.textures.at(texture) };
								keys.push_back(key);
							} else if (texture.find("body") == -1 && texture.find("instrument") == -1 && texture.find("idle") == -1) {
								std::map<int, bool> keyMap = {
									{availableKeys[i == 1 || i == 3 ? i - 1 : i + 1], false},
									{availableKeys[i], true}
								};

								Key key = { keyMap, characterClass.textures.at(texture) };
								keys.push_back(key);
								i++;
							}
						} break;
						default: break;
					}
				}
			}

			// Arrange hand textures
			// TO-DO: Add hand logic

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

	std::map<std::string, Character> characterMap;
	std::string userdataF = "./userdata/";
};

/*{
	  "id": "7k",
	  "keys": [ "A", "S", "D", "SPACE", "L", "SEMI_COLON", "SINGLE_QUOTE" ],
	  "characters": [ "bongoCat", "bongoCat" ],
	  "hotkey": 7,
	  "background": "bongoCat/background.png",
	  "table": "bongoCat/table.png"
	}*/