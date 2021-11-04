#include "raylib.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
#include <vector>

#include "typedefs.hpp"
#include "Config.hpp"
#include "input.hpp"
#include "StageHandler.hpp"
#include "json.hpp"
#include "Key.hpp"
#include "utility.hpp"

using nlohmann::json;
using std::string;
using std::shared_ptr;


/* ~Global Variables~ */
string const userdataLocation = "./userdata/";
string const configLocation = "./userdata/config.json";

int windowWidth;
int windowHeight;


/* ~Global Functions~ */

Config loadConfig () {
    Config config = { configLocation };

    windowHeight = config.windowHeight;
    windowWidth = config.windowWidth;

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    if (config.alwaysOntop) SetConfigFlags(FLAG_WINDOW_TOPMOST);
    if (config.transparent) SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    if (config.undecorated) SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    return config;
}

Config CreateWindow () {
    Config config = loadConfig();

    SetWindowIcon(LoadImage("maniakv.ico"));
    InitWindow(windowWidth, windowHeight, "ManiaKV");
    config.PostLoad();

    return config;
}

int main() {
    Config __config = CreateWindow();
    StageHandler stageHandler = { std::make_shared<Config>(__config) };

    int framesCounter = 0;
    MenuScreen currentScreen = KEYBOARD;

    bool showData = false;

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

                if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_C)) {
                    showData = false;
                } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_D)) {
                    showData = true;
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

        ClearBackground(BLANK);

        switch (currentScreen) {
            case KEYBOARD:
            {
                stageHandler.Render();

                if (showData) stageHandler.RenderData();
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
    
    __config.cache.RemoveAllTextures();
    CloseWindow();

    return 0;
}