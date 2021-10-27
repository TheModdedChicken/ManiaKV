#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "json.hpp"
#include "typedefs.hpp"

using json = nlohmann::json;

class Character {
public:
    json characterJson;
	std::map<std::string, Texture2D> textures;
	std::string id;
    int keys;

    Character (json characterIniJson) {
        characterJson = characterIniJson;
        LoadCharacter();
    }

    void LoadCharacter () {
        try {
            id = characterJson.at("id");
            keys = characterJson.at("keys");

            std::string body = userdataF + (std::string)characterJson.at("body");
            Texture2D bodyTexture = LoadTexture(body.c_str());
            textures.insert(std::pair<std::string, Texture2D>("body", bodyTexture));

            std::string instrument = userdataF + (std::string)characterJson.at("instrument");
            Texture2D instrumentTexture = LoadTexture(instrument.c_str());
            textures.insert(std::pair<std::string, Texture2D>("instrument", instrumentTexture));

            const std::string leftHandKeys[4] = { "idle", "key1", "key2", "key1-2" };
            json leftHandImages = characterJson.at("leftHand");
            for (int j = 0; j < sizeof(leftHandKeys) / sizeof(leftHandKeys[0]); j++) {
                if (leftHandImages.contains(leftHandKeys[j])) {
                    Texture2D imageTexture = LoadTexture((userdataF + (std::string)leftHandImages.at(leftHandKeys[j])).c_str());
                    textures.insert(
                        std::pair<std::string, Texture2D>("leftHand" + leftHandKeys[j], imageTexture)
                    );
                }
            }

            const std::string rightHandKeys[4] = { "idle", "key3", "key4", "key3-4" };
            auto rightHandImages = characterJson.at("rightHand");
            for (int j = 0; j < sizeof(rightHandKeys) / sizeof(rightHandKeys[0]); j++) {
                if (rightHandImages.contains(rightHandKeys[j])) {
                    Texture2D imageTexture = LoadTexture((userdataF + (std::string)rightHandImages.at(rightHandKeys[j])).c_str());
                    textures.insert(
                        std::pair<std::string, Texture2D>("rightHand" + rightHandKeys[j], imageTexture)
                    );
                }
            }
        } catch (json::exception err) {
            std::cout << err.what();
            throw err;
        }
    }

	void UnloadCharacter() {
        const std::vector<Texture2D> textureValues = extract_values(textures);
        for (const Texture2D &texture : textureValues) {
            UnloadTexture(texture);
        }
	}

private:
    std::string userdataF = "./userdata/";
};