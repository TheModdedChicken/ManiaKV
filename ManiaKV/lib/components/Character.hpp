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
        
    }
};

#endif // !CHARACTER_HPP
