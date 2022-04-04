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
#include "../main/utility.hpp"
#include "../main/dialogue.hpp"
//#include "../main/stages.hpp"

using nlohmann::json;
using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

class Character {
public:
    json const data() { return _data; };
    string const id() { return _id; };
    string const type() { return _type; };
    int const width() { return _width; };
    int const height() { return _height; };
    map<string, Texture2D> const textures() { return _textures; };
    json const modifiers() { return _modifiers; };

    Character () { };

    void UnloadTextures () {
        for (std::pair<string, Texture2D> characterPair : _textures) {
            UnloadTexture(characterPair.second);
        }
    }

protected:
    json _data = {};
	string _id = "";
    string _type = "";
	int _width = 0;
	int _height = 0;
	map<string, Texture2D> _textures = {};
    json _modifiers;

    Character (json data, int width, int height, json modifiers = {}): _data(data), _width(width), _height(height), _modifiers(modifiers) {}
};

class KeyboardCharacter: public Character {
public:
    KeyboardCharacter () { };
    KeyboardCharacter (json data, int width, int height) : Character(data, width, height) {
        Load();
    }

private:
	void Load() {
        try {
            _id = _data.at("id");
            _type = _data.at("type");
            _modifiers["keys"] = _data.at("keys");
            if (_modifiers["keys"] != 2 && _modifiers["keys"] != 4) throw "Characters can only have 2 or 4 keys";

            // Load body image and texture
            try {
                _textures.insert({ "body", ImageToTexture(mkv::userdataPath + (string)_data.at("textures").at("body"), _width, _height) });
            } catch (json::exception) {
            }

            // Load instrument image and texture
            try {
                _textures.insert({ "instrument", ImageToTexture(mkv::userdataPath + (string)_data.at("textures").at("instrument"), _width, _height) });
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
                        ImageToTexture( mkv::userdataPath + (string)keyImages.at( handKeys[keySet][j] ), _width, _height )
                    });
                } else _textures.insert({ handKeys[keySet][j], ImageToTexture(mkv::userdataPath + "key.png", _width, _height) });
            }
        } catch (json::exception err) {
            std::cout << err.what();
            throw err;
        }
	}
};

// Finish pointer character class for mice and drawing tablets
class PointerCharacter: public Character {
public:
    PointerCharacter() { };
    PointerCharacter (json data, int width, int height) : Character(data, width, height) {
        Load();
    }

private:
    void Load () {

    }
};

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

#endif // !CHARACTER_HPP