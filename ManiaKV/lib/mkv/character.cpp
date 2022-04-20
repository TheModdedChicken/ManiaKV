#include <lib/raylib.h>
#include <lib/json.hpp>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <memory>

#include "character.hpp"
#include "defs.hpp"
#include "utility.hpp"

using nlohmann::json;
using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

Character::Character () {};
Character::Character (json data, int width, int height, json modifiers = {}) : _data(data), _width(width), _height(height), _modifiers(modifiers) {}

json const Character::data() {
    return _data;
};

string const Character::id() {
    return _id;
};

string const Character::type() {
    return _type;
};

int const Character::width() {
    return _width;
};

int const Character::height() {
    return _height;
};

map<string, Texture2D> const Character::textures() {
    return _textures;
};

json const Character::modifiers() {
    return _modifiers;
};

void Character::UnloadTextures () {
    for (std::pair<string, Texture2D> characterPair : _textures) {
        UnloadTexture(characterPair.second);
    }
}

// --------------------

KeyboardCharacter::KeyboardCharacter () {};
KeyboardCharacter::KeyboardCharacter (json data, int width, int height) : Character(data, width, height) {
    Load();
}

void KeyboardCharacter::Load() {
    try {
        _id = _data.at("id");
        _type = _data.at("type");
        _modifiers["keys"] = _data.at("keys");
        if (_modifiers["keys"] != 2 && _modifiers["keys"] != 4) throw "Characters can only have 2 or 4 keys";

        // Load body image and texture
        try {
            _textures.insert({ "body", mkv::ImageToTexture(mkv::userdataPath + (string)_data.at("textures").at("body")) });
        } catch (json::exception) {
        }

        // Load instrument image and texture
        try {
            _textures.insert({ "instrument", mkv::ImageToTexture(mkv::userdataPath + (string)_data.at("textures").at("instrument")) });
        } catch (json::exception) {
        }

        // Load key images
        vector<vector<string>> handKeys = {
            { "leftIdle", "rightIdle", "key1", "key1-2", "key2" },
            { "leftIdle", "rightIdle", "key1", "key1-2", "key2", "key3", "key3-4", "key4" }
        };
        json keyImages = _data.at("textures");

        int const keySet = _modifiers["keys"] == 2 ? 0 : 1;
        for (int j = 0; j < handKeys[keySet].size(); j++) {

            if (keyImages.contains(handKeys[keySet][j])) {
                _textures.insert({
                    handKeys[keySet][j],
                    mkv::ImageToTexture(mkv::userdataPath + (string)keyImages.at(handKeys[keySet][j]))
                    });
            } else _textures.insert({ handKeys[keySet][j], mkv::ImageToTexture(mkv::userdataPath + "key.png") });
        }
    } catch (json::exception err) {
        std::cout << err.what();
        throw err;
    }
}

// ----------------------

// Finish pointer character class for mice and drawing tablets
PointerCharacter::PointerCharacter () { }
PointerCharacter::PointerCharacter (json data, int width, int height) : Character(data, width, height) {
    Load();
}

void PointerCharacter::Load () {

}

// ----------------------

Character CreateCharacter (json data, int width, int height) {
    string const type = data.at("type");

    if (type == "keyboard") {
        KeyboardCharacter character{ data, width, height };
        return character;
    } else if (type == "pointer") {
        PointerCharacter character{ data, width, height };
        return character;
    } else {
        throw "Unknown character type";
    }
}