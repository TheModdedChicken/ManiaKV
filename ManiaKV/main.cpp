#include <raylib.h>
#include <lib/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
#include <vector>
#include <exception>

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

int main() {
    try {
        Config __config = { mkv::configPath };

        Renderer stageCtrl = { std::make_shared<Config>(__config) };
        MenuScreen currentScreen = KEYBOARD;

        int framesCounter = 0;
        bool showDataOverlay = false;

        // Toggle Variables
        bool dataOverlayShortcutIsHeld = false;
        bool screenSwitchShortcutIsHeld = false;
        bool reloadConfigShortcutIsHeld = false;

        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            // Update

            /*if (!screenSwitchShortcutIsHeld && MKVIsPressed({KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_PERIOD})) {
                if (currentScreen == KEYBOARD) {
                    currentScreen = SETTINGS;
                } else currentScreen = KEYBOARD;

                screenSwitchShortcutIsHeld = true;
            } else if (screenSwitchShortcutIsHeld && !MKVIsPressed({ KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_PERIOD })) screenSwitchShortcutIsHeld = false;*/

            // Keybind to follow mouse when window is undecorated
            if (__config.undecorated && mkv::IsKeyPressed({ mkv::keys::LEFT_ALT, mkv::keys::D })) {
                SetWindowPosition(mkv::GetGlobalCursorPos().x - (int)(__config.windowWidth / 2), mkv::GetGlobalCursorPos().y - (int)(__config.windowHeight / 2));
            }

            switch (currentScreen) {
            case KEYBOARD:
            {
                if (!dataOverlayShortcutIsHeld && mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_SHIFT, mkv::keys::COMMA })) {
                    if (showDataOverlay) {
                        showDataOverlay = false;
                    } else showDataOverlay = true;

                    dataOverlayShortcutIsHeld = true;
                } else if (dataOverlayShortcutIsHeld && !mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_SHIFT, mkv::keys::COMMA })) dataOverlayShortcutIsHeld = false;
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

            if (!reloadConfigShortcutIsHeld && mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::R })) {
                __config.Reload(mkv::configPath);

                reloadConfigShortcutIsHeld = true;
            } else if (reloadConfigShortcutIsHeld && !mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_ALT, mkv::keys::R })) reloadConfigShortcutIsHeld = false;
        }

        /* Save & Unload */
        WriteStates();
        __config.cache.RemoveAllTextures();
        CloseWindow();
    } catch ( ... ){
        SpawnErrorDialogueBox(L"Uh Oh", L"Woops! Looks like ManiaKV crashed.\nDon't hesitate to report this issue to ManiaKV's github page if you're having trouble.");
        std::terminate();
    }

    return 0;
}