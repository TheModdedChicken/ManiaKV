#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
#include <vector>
#include <exception>

#include <lib/uniraylib.hpp>
#include <lib/json.hpp>
#include <lib/mkvlib.hpp>
//#undef RAYGUI_IMPLEMENTATION

#include "./scenes.hpp"
#include "./overlays.hpp"

using nlohmann::json;
using std::string;
using std::shared_ptr;


/* ~Variables~ */


/* ~Functions~ */
void app() {
    shared_ptr<Config> __config = std::make_shared<Config>((Config)(mkv::configPath));

    Renderer renderer = { __config };
    renderer.AddScene("main", scenes::DrawMainScene);
    renderer.AddScene("settings", scenes::DrawSettings);
    renderer.AddOverlay("updateApplication", overlays::updateApplication);
    renderer.AddOverlay("downloadDefaultConfig", overlays::downloadDefaultConfig);
    renderer.SetScene("main");

    if (__config->failedToLoad) renderer.InitializeOverlay("downloadDefaultConfig");

    int framesCounter = 0;
    bool showDataOverlay = false;

    // Toggle Variables
    bool dataOverlayShortcutIsHeld = false;
    bool screenSwitchShortcutIsHeld = false;
    bool reloadConfigShortcutIsHeld = false;
    bool checkedUpdateStatus = false;
    GitHubAppVersion updateData;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Update

        if (!checkedUpdateStatus) {
            try {
                updateData = checkForUpdates();
                bool stateCheck = true;
                try {
                    stateCheck = (updateData.tag != mkv::GetState(mkv::STATES::UPDATE_SKIP));
                } catch ( ... ) { }

                if (stateCheck) renderer.InitializeOverlay("updateApplication", { {"name", updateData.name}, {"url", updateData.url}, {"tag", updateData.tag} });
            } catch (...) {

            }

            checkedUpdateStatus = true;
        }

        if (mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_SHIFT, mkv::keys::PERIOD })) {
            if (renderer.currentScene() == "main") {
                renderer.SetScene("settings");
            } else renderer.SetScene("main");
        }

        // Keybind to follow mouse when window is undecorated
        if (__config->undecorated && mkv::IsKeyHeld({ mkv::keys::LEFT_ALT, mkv::keys::D })) {
            SetWindowPosition(mkv::GetGlobalCursorPos().x - (int)(__config->windowWidth / 2), mkv::GetGlobalCursorPos().y - (int)(__config->windowHeight / 2));
        }

        if (renderer.currentScene() == "main") if (!dataOverlayShortcutIsHeld && mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_SHIFT, mkv::keys::COMMA })) {
            if (showDataOverlay) {
                showDataOverlay = false;
            } else showDataOverlay = true;

            dataOverlayShortcutIsHeld = true;
        } else if (dataOverlayShortcutIsHeld && !mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::LEFT_SHIFT, mkv::keys::COMMA })) dataOverlayShortcutIsHeld = false;
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(BLANK);

            renderer.Render();
            if (renderer.currentScene() == "main" && showDataOverlay) renderer.RenderData();

        EndDrawing();
        //----------------------------------------------------------------------------------

        if (!reloadConfigShortcutIsHeld && mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::R })) {
            __config->Reload(mkv::configPath);

            reloadConfigShortcutIsHeld = true;
        } else if (reloadConfigShortcutIsHeld && !mkv::IsKeyPressed({ mkv::keys::LEFT_CTRL, mkv::keys::R })) reloadConfigShortcutIsHeld = false;
    }

    /* Save & Unload */
    mkv::WriteStates();
    __config->SaveConfig();
    CloseWindow();
}

int main(int argc, char* argv[]) {
    mkv::SetState(mkv::LOGOPS, true);

    if (mkv::GetState(mkv::LOGOPS)) {
        app();
    } else {
        try {
            app();
        } catch (std::exception err) {
            SpawnErrorDialogueBox(L"Uh Oh", L"Woops! Looks like ManiaKV crashed.\nDon't hesitate to report this issue to ManiaKV's github page if you're having trouble.");
            std::terminate();
        }
    }

    return 0;
}