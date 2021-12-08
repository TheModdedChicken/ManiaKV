#include <raylib.h>
#include <lib/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
#include <vector>

#include <lib/mkvlib.hpp>

using nlohmann::json;
using std::string;
using std::shared_ptr;


/* ~Global Variables~ */

int windowWidth;
int windowHeight;

typedef enum MenuScreen {
    KEYBOARD, SETTINGS
} MenuScreen;


/* ~Global Functions~ */

Config loadConfig () {
    Config config = { mkvdefs::configLoc };

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
    StageController stageCtrl = { std::make_shared<Config>(__config) };
    MenuScreen currentScreen = KEYBOARD;

    int framesCounter = 0;
    bool showDataOverlay = false;
    bool dataOverlayShortcutIsHeld = false;
    bool screenSwitchShortcutIsHeld = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        
        if (!screenSwitchShortcutIsHeld && MKVIsPressed({ KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_PERIOD })) {
            if (currentScreen == KEYBOARD) {
                currentScreen = SETTINGS;
            } else currentScreen = KEYBOARD;

            screenSwitchShortcutIsHeld = true;
        } else if (screenSwitchShortcutIsHeld && !MKVIsPressed({ KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_PERIOD })) screenSwitchShortcutIsHeld = false;

        switch (currentScreen) {
            case KEYBOARD:
            {
                if (!dataOverlayShortcutIsHeld && MKVIsPressed({ KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_COMMA })) {
                    if (showDataOverlay) {
                        showDataOverlay = false;
                    } else showDataOverlay = true;

                    dataOverlayShortcutIsHeld = true;
                } else if (dataOverlayShortcutIsHeld && !MKVIsPressed({ KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_COMMA })) dataOverlayShortcutIsHeld = false;
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

                stageCtrl.Render();
                if (showDataOverlay) stageCtrl.RenderData();
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
    
    /* Save & Unload */
    WriteStates();
    __config.cache.RemoveAllTextures();
    CloseWindow();

    return 0;
}