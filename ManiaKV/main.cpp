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

    InitWindow(windowWidth, windowHeight, "ManiaKV");
    config.PostLoad();

    return config;
}

int main() {
    Config __config = CreateWindow();
    StageHandler stageHandler = { std::make_shared<Config>(__config) };
    MenuScreen currentScreen = KEYBOARD;

    int framesCounter = 0;
    bool showDataOverlay = false;
    bool dataOverlayShortcutIsHeld = false;
    bool screenSwitchShortcutIsHeld = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        
        /*
        if (!screenSwitchShortcutIsHeld && IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_PERIOD)) {
            if (currentScreen == KEYBOARD) {
                currentScreen = SETTINGS;
            } else currentScreen = KEYBOARD;

            screenSwitchShortcutIsHeld = true;
        } else if (screenSwitchShortcutIsHeld && (IsKeyUp(KEY_LEFT_CONTROL) || IsKeyUp(KEY_LEFT_SHIFT) || IsKeyUp(KEY_PERIOD))) screenSwitchShortcutIsHeld = false;
        */

        switch (currentScreen) {
            case KEYBOARD:
            {
                if (!dataOverlayShortcutIsHeld && IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_COMMA)) {
                    if (showDataOverlay) {
                        showDataOverlay = false;
                    } else showDataOverlay = true;

                    dataOverlayShortcutIsHeld = true;
                } else if (dataOverlayShortcutIsHeld && (IsKeyUp(KEY_LEFT_CONTROL) || IsKeyUp(KEY_LEFT_SHIFT) || IsKeyUp(KEY_COMMA))) dataOverlayShortcutIsHeld = false;
            } break;
            case SETTINGS:
            {

            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

        switch (currentScreen) {
            case KEYBOARD:
            {
                ClearBackground(BLANK);

                stageHandler.Render();
                if (showDataOverlay) stageHandler.RenderData();
            } break;
            case SETTINGS:
            {
                ClearBackground(RAYWHITE);

                DrawText("Press a key to check its keycode", __config.windowWidth / 5, __config.windowHeight / 5, 20, LIGHTGRAY);

                //DrawText(GetKeyPressed(), __config.windowWidth / 5, __config.windowHeight / 5, 20, LIGHTGRAY);
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