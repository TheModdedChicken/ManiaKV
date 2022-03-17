#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <lib/raylib.h>
#include <lib/json.hpp>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <memory>

#include "../main/defs.hpp"
#include "../main/Cache.hpp"
#include "../main/utility.hpp"

using nlohmann::json;
using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

class Character {
public:
    json characterJson;
    int keys;
    int spriteWidth;
    int spriteHeight;

    map<string, map<string, string>> textures = {
        {"main", {}},
        {"keys", {}},
    };
    string id;

    Character (Cache& cache, json charJson, int width, int height) {
        characterJson = charJson;
        spriteWidth = width;
        spriteHeight = height;
        LoadCharacter(cache);
    }

private:
    void LoadCharacter (Cache& cache) {
        try {
            id = characterJson.at("id");

            keys = characterJson.at("keys");
            if (keys != 2 && keys != 4) throw "Characters can only have 2 or 4 keys";

            // Load body image and texture
            try {
                textures.at("main").insert({ "body", cache.CacheTexture(mkv::userdataLoc + (string)characterJson.at("textures").at("body")) });
            } catch (json::exception) {}

            // Load instrument image and texture
            try {
                textures.at("main").insert({ "instrument", cache.CacheTexture(mkv::userdataLoc + (string)characterJson.at("textures").at("instrument")) });
            } catch (json::exception) {}

            // Load key images
            vector<vector<string>> handKeys = {
                { "leftIdle", "rightIdle", "key1", "key1-2", "key2" },
                { "leftIdle", "rightIdle", "key1", "key1-2", "key2", "key3", "key3-4", "key4" }
            };
            json keyImages = characterJson.at("textures");

            int const keySet = keys == 2 ? 0 : 1;
            for (int j = 0; j < handKeys[keySet].size(); j++) {

                if (keyImages.contains(handKeys[keySet][j])) {
                    textures.at("keys").insert({
                        handKeys[keySet][j],
                        cache.CacheTexture((
                            mkv::userdataLoc + (string)keyImages.at(handKeys[keySet][j])
                        ))
                    });
                } else textures.at("keys").insert({ handKeys[keySet][j], cache.CacheTexture(mkv::userdataLoc + "key.png") });
            }
        } catch (json::exception err) {
            std::cout << err.what();
            throw err;
        }
    }
};

#endif // !CHARACTER_HPP
