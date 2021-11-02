#pragma once
#include "raylib.h"
#include "json.hpp"
#include <string>
#include <map>
#include <iostream>
#include <vector>

#include "typedefs.hpp"
#include "utility.hpp"

using json = nlohmann::json;

class Character {
public:
    json characterJson;
    int keys;
    int spriteWidth;
    int spriteHeight;

    std::map<std::string, std::map<std::string, Texture2D>> textures = {
        {"main", {}},
        {"keys", {}},
    };
    std::string id;

    Character (json charJson, int width, int height) {
        characterJson = charJson;
        spriteWidth = width;
        spriteHeight = height;
        LoadCharacter();
    }

    // TO-DO: Add reload function
private:
    void LoadCharacter () {
        try {
            id = characterJson.at("id");

            keys = characterJson.at("keys");
            if (keys != 2 && keys != 4) throw "Characters can only have 2 or 4 keys";

            // Load body image and texture
            std::string body = userdataF + (std::string)characterJson.at("body");
            Image bodyImage = LoadImage(body.c_str());
            ImageResize(&bodyImage, spriteWidth, spriteHeight);
            Texture2D bodyTexture = LoadTextureFromImage(bodyImage);
            textures.at("main").insert(std::pair<std::string, Texture2D>("body", bodyTexture));

            // Load instrument image and texture
            std::string instrument = userdataF + (std::string)characterJson.at("instrument");
            Image instrumentImage = LoadImage(instrument.c_str());
            ImageResize(&instrumentImage, spriteWidth, spriteHeight);
            Texture2D instrumentTexture = LoadTextureFromImage(instrumentImage);
            textures.at("main").insert(std::pair<std::string, Texture2D>("instrument", instrumentTexture));

            // Load left hand images and textures
            std::vector<std::string> handKeys = { "leftIdle", "rightIdle", "key1", "key1-2", "key2", "key3", "key3-4", "key4" };
            json keyImages = characterJson.at("textures");
            for (int j = 0; j < handKeys.size(); j++) {
            
                if (keyImages.contains(handKeys[j])) {
                    Image image = LoadImage((userdataF + (std::string)keyImages.at(handKeys[j])).c_str());
                    ImageResize(&image, spriteWidth, spriteHeight);
                    Texture2D imageTexture = LoadTextureFromImage(image);

                    textures.at("keys").insert({handKeys[j], imageTexture});
                }
            }
        } catch (json::exception err) {
            std::cout << err.what();
            throw err;
        }
    }

	/*void UnloadCharacter() {
        const std::vector<Texture2D> textureValues = extract_values(textures);
        for (const Texture2D &texture : textureValues) {
            UnloadTexture(texture);
        }
	}*/

    std::string userdataF = "./userdata/";
};