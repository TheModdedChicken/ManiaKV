#include <lib/json.hpp>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <map>

#include "key.hpp"
#include "defs.hpp"
#include "utility.hpp"
#include "input.hpp"
#include "console.hpp"
#include "character.hpp"

#include "stage.hpp"

using nlohmann::json;
using std::vector;
using std::string;
using std::map;
using std::shared_ptr;

Stage::Stage (json data, shared_ptr<map<string, Character>> characters) : data(data), characterImport(characters) {
	Load();
}

void Stage::UnloadTextures () {
	for (std::pair<string, Texture2D> texture : textures) {
		UnloadTexture(texture.second);
	}
}

void Stage::Load () {
	// TO-DO: Add better checks for property presence

	for (string characterName : data.at("characters")) {
		console::log(characterName, "Stage.hpp");
		characters.push_back(characterImport->at(characterName).id());
	}
	if (characters.size() < 1) return;

	try {
		id = data.at("id");

		for (string key : data.at("shortcut")) {
			shortcut.push_back(mkv::GetKeyCode(key));
		}
	} catch (json::exception err) {
	};

	try {
		vector<string> keyCharacters = {};
		vector<string> pointerCharacters = {};

		// Finish key assigner
		vector<int> availableKeys;
		int availableKeyCount = 0;
		for (string key : data.at("keys")) {
			availableKeys.push_back(mkv::GetKeyCode(key));
			availableKeyCount++;
		}

		int totalCharacterKeys = 0;
		for (string character : characters) {
			if (characterImport->at(character).type() == "keyboard") {

				keyCharacters.push_back(characterImport->at(character).id());
				totalCharacterKeys += characterImport->at(character).modifiers()["keys"];

			} else if (characterImport->at(character).type() == "pointer") {
				pointerCharacters.push_back(characterImport->at(character).id());
			}
		}

		int keyOffset = 0;
		int lastSplit = -1;
		if (availableKeys.size() < totalCharacterKeys - 2 || availableKeys.size() > totalCharacterKeys) throw "Stage cannot support the current amount of character keys";

		for (string character : keyCharacters) {
			int characterKeys = characterImport->at(character).modifiers()["keys"];
			int currentKey = (0 + keyOffset);

			// Load Pattern: key1 -> key1-2 -> key2 -> key3 -> key3-4 -> key4 -> leftIdle -> rightIdle
			for (std::pair<string, Texture2D> texture : characterImport->at(character).textures()) {
				string const textureName = texture.first;
				Texture2D const textureData = texture.second;
				map<int, bool> keyMap;

				// I still couldn't figure out how to efficiently do this so enjoy jank :) - TheModdedChicken
				if (textureName.find("Idle") != -1) {
					console::log(textureName, "Stage.hpp");

					if (characterKeys == 2) {
						keyMap = {
							{availableKeys[textureName.find("leftIdle") != -1
								? currentKey - 2
								: currentKey - 1
							], false},
						};
					} else {
						if (id == "7k") {
							console::log("found", __THISFILE__);
						}

						if (availableKeyCount != (totalCharacterKeys - 1) && availableKeyCount != (characterKeys - 1)) {
							keyMap = {
								{availableKeys[textureName.find("leftIdle") != -1
									? currentKey - 4
									: currentKey - 2
								], false},
								{availableKeys[textureName.find("leftIdle") != -1
									? currentKey - 3
									: currentKey - 1
								], false},
							};
						} else if (availableKeyCount == 7) {
							if (currentKey == 3) {
								keyMap = {
									{availableKeys[textureName.find("leftIdle") != -1
										? currentKey - 3
										: currentKey - 1
									], false},
									{availableKeys[textureName.find("leftIdle") != -1
										? currentKey - 2
										: currentKey
									], false},
								};
							} else {
								keyMap = {
									{availableKeys[textureName.find("leftIdle") != -1
										? currentKey - 4
										: currentKey - 2
									], false},
									{availableKeys[textureName.find("leftIdle") != -1
										? currentKey - 3
										: currentKey - 1
									], false},
								};
							}
						} else {
							keyMap = {
								{availableKeys[textureName.find("leftIdle") != -1
									? currentKey - 3
									: currentKey - 2
								], false},
								{availableKeys[textureName.find("leftIdle") != -1
									? currentKey - 2
									: currentKey - 1
								], false},
							};
						}
					}

					keys.push_back({ keyMap, characterImport->at(character).textures().at(textureName) });
				} else if (textureName.find("key1-2") != -1 || textureName.find("key3-4") != -1) {
					console::log(textureName, "Stage.hpp");

					if (availableKeyCount != 2) {
						keys.push_back({
							{
								{availableKeys[currentKey - 1], true},
								{availableKeys[currentKey], true}
							},
							characterImport->at(character).textures().at(textureName)
							});
					}
				} else if (textureName.find("key") != -1) {
					console::log(textureName, "Stage.hpp");

					// Fix odd number of keys edge case
					if (availableKeyCount == (totalCharacterKeys - 1) && (currentKey == (availableKeyCount / 2) || lastSplit != -1) && lastSplit != -2) {
						keys.push_back({
							{
								{availableKeys[currentKey], true},
								{availableKeys[lastSplit == -1
									? currentKey - 1
									: currentKey + 1
								], false},
							},
							characterImport->at(character).textures().at(textureName)
							});
						if (lastSplit != -1) {
							currentKey++;
							lastSplit = -2;
						}
						if (lastSplit == -1) lastSplit = currentKey;
					} else {
						if (characterKeys == 2) {
							keys.push_back({
								{
									{availableKeys[currentKey], true}
								},
								characterImport->at(character).textures().at(textureName)
								});
						} else {
							keys.push_back({
								{
									{availableKeys[currentKey], true},
									{availableKeys[textureName.find("2") != -1 || textureName.find("4") != -1
										? currentKey - 1
										: currentKey + 1
									], false},
								},
								characterImport->at(character).textures().at(textureName)
								});
						}

						currentKey++;
					}
				}
			}

			keyOffset += currentKey;
		}

		for (string character : pointerCharacters) {

		}

		for (string character : data.at("characters")) {

		}

		try {
			textures.insert({ "table", mkv::ImageToTexture(mkv::userdataPath + (string)data.at("table")) });
		} catch (json::exception) {
		}

		try {
			textures.insert({ "background", mkv::ImageToTexture(mkv::userdataPath + (string)data.at("background")) });
		} catch (json::exception) {
		}
	} catch (json::exception err) {
		std::cout << err.what();
		throw err;
	}
}