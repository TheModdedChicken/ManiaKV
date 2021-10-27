#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
#include <vector>

#include "raylib.h"
#include "json.hpp"
#include "typedefs.hpp"
#include "Config.hpp"


/* ~Global Variables~ */

using json = nlohmann::json;

json config;
std::string userdataFolder = "./userdata/";

int windowWidth;
int windowHeight;


/* ~Global Functions~ */
Config loadConfig () {
    Config config = { userdataFolder + "config.json" };

    windowHeight = config.windowHeight;
    windowWidth = config.windowWidth;

    return config;
}

int main() {
    Config config = loadConfig();

    InitWindow(windowWidth, windowHeight, "tippytap");
    config.LoadCharacters();

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

                    // Add custom loading
                    // Add character class with handlers for textures
                    DrawTexture(config.characters.at("bongoCat").textures.at("body"), 0, 0, WHITE);
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

    // Fix unload data ranged for loop
    // Unload all loaded data

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}