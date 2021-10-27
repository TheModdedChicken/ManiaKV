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

    int spriteWidth;
    int spriteHeight;

    Character (json charJson, int width, int height) {
        characterJson = charJson;
        spriteWidth = width;
        spriteHeight = height;
        LoadCharacter();
    }

    void LoadCharacter () {
        try {
            id = characterJson.at("id");
            keys = characterJson.at("keys");

            // Load body image and texture
            std::string body = userdataF + (std::string)characterJson.at("body");
            Image bodyImage = LoadImage(body.c_str());
            ImageResize(&bodyImage, spriteWidth, spriteHeight);
            Texture2D bodyTexture = LoadTextureFromImage(bodyImage);
            textures.insert(std::pair<std::string, Texture2D>("body", bodyTexture));

            // Load instrument image and texture
            std::string instrument = userdataF + (std::string)characterJson.at("instrument");
            Image instrumentImage = LoadImage(instrument.c_str());
            ImageResize(&instrumentImage, spriteWidth, spriteHeight);
            Texture2D instrumentTexture = LoadTextureFromImage(instrumentImage);
            textures.insert(std::pair<std::string, Texture2D>("instrument", instrumentTexture));

            // Load left hand images and textures
            const std::string leftHandKeys[4] = { "idle", "key1", "key2", "key1-2" };
            json leftHandImages = characterJson.at("leftHand");
            for (int j = 0; j < sizeof(leftHandKeys) / sizeof(leftHandKeys[0]); j++) {

                if (leftHandImages.contains(leftHandKeys[j])) {
                    Image image = LoadImage((userdataF + (std::string)leftHandImages.at(leftHandKeys[j])).c_str());
                    ImageResize(&image, spriteWidth, spriteHeight);
                    Texture2D imageTexture = LoadTextureFromImage(image);

                    textures.insert(
                        std::pair<std::string, Texture2D>("leftHand" + leftHandKeys[j], imageTexture)
                    );
                }
            }

            // Load right hand images and textures
            const std::string rightHandKeys[4] = { "idle", "key3", "key4", "key3-4" };
            auto rightHandImages = characterJson.at("rightHand");
            for (int j = 0; j < sizeof(rightHandKeys) / sizeof(rightHandKeys[0]); j++) {

                if (rightHandImages.contains(rightHandKeys[j])) {
                    Image image = LoadImage((userdataF + (std::string)rightHandImages.at(rightHandKeys[j])).c_str());
                    ImageResize(&image, spriteWidth, spriteHeight);
                    Texture2D imageTexture = LoadTextureFromImage(image);

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