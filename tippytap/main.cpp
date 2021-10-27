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
#include "input.hpp"


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
    config.LoadStages();

    int framesCounter = 0;
    MenuScreen currentScreen = KEYBOARD;
    HandState currentLHState = IDLE;
    HandState currentRHState = IDLE;

    SetTargetFPS(60);

    Texture2D bongoCat = config.characters.at("bongoCat").textures.at("body");

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
                    if (IsKeyDownSW(GetKeyCode("D"))) DrawTextureRec(bongoCat, {0, 0, (float)bongoCat.width, (float)bongoCat.height}, {0.0f, 0.0f}, WHITE);

                    DrawText("Keyboard", 10, 5, 20, LIGHTGRAY);
                } break;
                case SETTINGS:
                {
                    DrawText("Settings", 10, 5, 20, LIGHTGRAY);
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