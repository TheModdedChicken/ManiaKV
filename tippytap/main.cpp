#include "raylib.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>


/* ~Global Variables~ */

using json = nlohmann::json;

json config;
std::string dataFolder = "./userdata/";

int windowWidth;
int windowHeight;

typedef enum MenuScreen {
    KEYBOARD, SETTINGS
} MenuScreen;


/* ~Global Functions~ */

void loadConfig() {
    std::ifstream i(dataFolder + "config.json");
    i >> config;

    try {
        windowWidth = config.at("windowWidth");
        windowHeight = config.at("windowHeight");
    } catch (json::exception err) {
        windowWidth = 1189;
        windowHeight = 669;
    }
}

std::map<std::string, Texture2D> loadTextures() {
    std::map<std::string, std::map<std::string, Texture2D>> textures;
    const std::regex handImageRegex{ R"~((idle|key(([1-4]){1,2}|(1-2)|(3-4)).png)$)~" };
    const std::string handKeys[7] = { "idle", "key1", "key2", "key3", "key4", "key1-2", "key3-4" };

    for (int i = 0; i < sizeof(config["characters"]) / sizeof(config["characters"][0]); i++) {
        std::map<std::string, Texture2D> characterTextures;
        textures.insert(std::pair<std::string, std::map<std::string, Texture2D>>(config["characters"][i], characterTextures));

        try {
            std::string id = config["characters"][i].at("id");

            std::string body = dataFolder + (std::string)config["characters"][i].at("body");
            Texture2D bodyTexture = LoadTexture(body.c_str());
            characterTextures.insert(std::pair<std::string, Texture2D>("body", bodyTexture));

            std::string instrument = dataFolder + (std::string)config["characters"][i].at("instrument");
            Texture2D instrumentTexture = LoadTexture(instrument.c_str());
            characterTextures.insert(std::pair<std::string, Texture2D>("instrument", instrumentTexture));

            std::string keys = dataFolder + (std::string)config["characters"][i].at("keys");
            Texture2D keysTexture = LoadTexture(keys.c_str());

            // Change to map of string, Texture2D
            json leftHandTextures;
            auto leftHandImages = config["characters"][i].at("leftHand");
            for (int p = 0; p < sizeof(leftHandImages) / sizeof(leftHandImages[0]); p++) {
                std::string lhImage = leftHandImages[p];
                for (int j = 0; j < sizeof(handKeys) / sizeof(handKeys[0]); j++) {
                    if (lhImage.find(handKeys[j] + ".png")) {
                        leftHandTextures[handKeys[j]] = lhImage;
                    }
                }
            }
            characterTextures["leftHandTextures"] = leftHandTextures;

            json rightHandTextures;
            auto rightHandImages = config["characters"][i].at("rightHand");
            for (int p = 0; p < sizeof(rightHandImages) / sizeof(rightHandImages[0]); p++) {
                std::string rhImage = rightHandImages[p];
                for (int j = 0; j < sizeof(handKeys) / sizeof(handKeys[0]); j++) {
                    if (rhImage.find(handKeys[j] + ".png")) {
                        rightHandTextures[handKeys[j]] = rhImage;
                    }
                }
            }
            characterTextures["rightHandTextures"] = rightHandTextures;


        } catch (json::exception err) {

        }
    }

    return textures;
}

int main() {
    loadConfig();
    //const json setups = loadSetups();

    InitWindow(windowWidth, windowHeight, "tippytap");

    const json textures = loadTextures();

    int framesCounter = 0;
    MenuScreen currentScreen = KEYBOARD;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        switch (currentScreen) {
            case KEYBOARD:
            {
                if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_PERIOD)) {
                    currentScreen = SETTINGS;
                }
            } break;
            case SETTINGS:
            {
                if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_COMMA)) {
                    currentScreen = KEYBOARD;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (currentScreen) {
                case KEYBOARD:
                {
                    DrawText("Keyboard", windowWidth / 2, windowHeight / 2, 20, LIGHTGRAY);
                } break;
                case SETTINGS:
                {
                    DrawText("Settings", windowWidth / 2, windowHeight / 2, 20, LIGHTGRAY);
                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }


    // Unload all loaded data

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}