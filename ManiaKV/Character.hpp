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
using std::map;
using std::string;
using std::vector;

class Character {
public:
    json characterJson;
    int keys;
    int spriteWidth;
    int spriteHeight;

    map<string, map<string, Texture2D>> textures = {
        {"main", {}},
        {"keys", {}},
    };
    string id;

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
            string body = userdataF + (string)characterJson.at("body");
            Image bodyImage = LoadImage(body.c_str());
            ImageResize(&bodyImage, spriteWidth, spriteHeight);
            Texture2D bodyTexture = LoadTextureFromImage(bodyImage);
            textures.at("main").insert({ "body", bodyTexture });

            // Load instrument image and texture
            string instrument = userdataF + (string)characterJson.at("instrument");
            Image instrumentImage = LoadImage(instrument.c_str());
            ImageResize(&instrumentImage, spriteWidth, spriteHeight);
            Texture2D instrumentTexture = LoadTextureFromImage(instrumentImage);
            textures.at("main").insert({ "instrument", instrumentTexture });

            // Load left hand images and textures
            vector<string> handKeys = { "leftIdle", "rightIdle", "key1", "key1-2", "key2", "key3", "key3-4", "key4" };
            json keyImages = characterJson.at("textures");
            for (int j = 0; j < handKeys.size(); j++) {
            
                if (keyImages.contains(handKeys[j])) {
                    Image image = LoadImage((userdataF + (string)keyImages.at(handKeys[j])).c_str());
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
        const vector<Texture2D> textureValues = extract_values(textures);
        for (const Texture2D &texture : textureValues) {
            UnloadTexture(texture);
        }
	}*/

    string userdataF = "./userdata/";
};