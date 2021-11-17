#ifndef STAGE_HPP
#define STAGE_HPP

#include <string>
#include <vector>
#include <ostream>

#include <lib/json.hpp>
#include "../main/Cache.hpp"
#include "Character.hpp"
#include "input.hpp"
#include "Key.hpp"
#include "utility.hpp"

using nlohmann::json;
using std::vector;
using std::string;
using std::map;

class Stage {
public:
	json stageJson;

	int stageWidth;
	int stageHeight;

	vector<int> shortcut = {};
	string id;
	vector<string> characters;
	vector<Key> keys;
	map<string, string> textures;

	Stage (Cache& cache, json stageJsonIn, map<string, Character> charactersIn, int widthIn, int heightIn) {
		characterMap = charactersIn;
		stageJson = stageJsonIn;
		stageWidth = widthIn;
		stageHeight = heightIn;
		LoadStage(cache);
	}

	// TO-DO: Add reload function
private:
	void LoadStage (Cache& cache) {
		// TO-DO: Add better checks for property presence

		try {
			for (string key : stageJson.at("shortcut")) {
				shortcut.push_back(GetKeyCode(key));
			}
		} catch (json::exception err) {
		};

		try {
			id = stageJson.at("id");
			vector<int> availableKeys;
			for (string key : stageJson.at("keys")) {
				availableKeys.push_back(GetKeyCode(key));
			}

			int availableKeyCount = (int)availableKeys.size();
			int availableKeyIndex = (int)availableKeys.size() - 1;
			int characterKeys = 0;
			int characterCount = 0;
			for (string character : stageJson.at("characters")) {
				Character characterClass = characterMap.at(character);
				characters.push_back(character);
				characterCount++;
				characterKeys += characterClass.keys;
			}

			// Logic Reminders:
			/*
				- Can only have 1 more key texture than actual keys:
					If one extra key texture is present then it will be paired with another key texture
				- Cannot have more keys than key textures
				- Can only have 2 or 4 keys per character
				- Can only have 1-2 characters
			*/
			if (characterKeys - 1 > availableKeys.size()) throw "Too many key textures used";
			bool isOdd = availableKeys.size() % 2 == 1;
			bool didSplit = false;
			int charI = 0;
			int i = 0;
			for (string character : stageJson.at("characters")) {
				Character characterClass = characterMap.at(character);

				int textureI = 0;

				for (string texture : extract_keys(characterMap.at(character).textures.at("keys"))) {
					if (texture.find("Idle") != -1) {
						map<int, bool> keyMap;

						// Temperary fix because I'm stupid and can't be bothered to properly implement it right now
						if (characterClass.keys == 2) {
							keyMap = {
								{availableKeys[texture.find("rightIdle") != -1
									? i - 1
									: i - 2
								], false},
							};
						} else {
							if (!isOdd) {
								keyMap = {
									{availableKeys[texture.find("rightIdle") != -1
										? i - 1
										: i - 3
									], false},
									{availableKeys[texture.find("rightIdle") != -1
										? i - 2
										: i - 4
									], false}
								};
							} else {
								if (availableKeyCount == 7 && charI == 0) {
									keyMap = {
										{availableKeys[texture.find("rightIdle") != -1
											? i
											: i - 2
										], false},
										{availableKeys[texture.find("rightIdle") != -1
											? i - 1
											: i - 3
										], false}
									};
								} else if (availableKeyCount == 7 && charI == 1) {
									keyMap = {
										{availableKeys[texture.find("rightIdle") != -1
											? i - 1
											: i - 3
										], false},
										{availableKeys[texture.find("rightIdle") != -1
											? i - 2
											: i - 4
										], false}
									};
								} else {
									keyMap = {
										{availableKeys[texture.find("rightIdle") != -1
											? i - 1
											: i - 2
										], false},
										{availableKeys[texture.find("rightIdle") != -1
											? i - 2
											: i - 3
										], false}
									};
								}
							}

						}

						keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
					} else if (texture.find("key1-2") != -1 || texture.find("key3-4") != -1) {
						if (availableKeyCount != 2) {
							map<int, bool> keyMap = {
								{availableKeys[i - 1], true},
								{availableKeys[i], true}
							};
							keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
						}
					} else {
						if (didSplit == false && isOdd && i == std::floor(availableKeys.size() / 2)) {
							map<int, bool> keyMap;
							if (texture.find("key1") != -1 || texture.find("key3") != -1) {
								keyMap = {
									{availableKeys[i + 1], false},
									{availableKeys[i], true}
								};
								i++;
								textureI++;
								didSplit = true;
							} else {
								keyMap = {
									{availableKeys[i - 1], false},
									{availableKeys[i], true}
								};
							}
							keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
						} else {
							map<int, bool> keyMap;

							if (characterClass.keys == 2) {
								keyMap = {
									{availableKeys[i], true}
								};
							} else {
								keyMap = {
									{availableKeys[texture.find("key1") != -1 || texture.find("key3") != -1
										? i + 1
										: i - 1
									], false},
									{availableKeys[i], true}
								};
							}

							keys.push_back({ keyMap, characterMap.at(character).textures.at("keys").at(texture) });
							i++;
							textureI++;
						}
					}
				}
				charI++;
			}

			// Load table texture
			try {
				textures.insert({ "table", cache.CacheTexture(userdataLocation + (string)stageJson.at("table")) });
			} catch (json::exception) {
			}

			// Load background texture
			try {
				textures.insert({ "background", cache.CacheTexture(userdataLocation + (string)stageJson.at("background")) });
			} catch (json::exception) {
			}
		} catch (json::exception err) {
			std::cout << err.what();
			throw err;
		}
	}

	map<string, Character> characterMap;
	string const userdataLocation = "./userdata/";
};

#endif // !STAGE_HPP
