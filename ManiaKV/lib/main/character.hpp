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
#include "../main/stages.hpp"

using nlohmann::json;
using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

class Character {
public:
    json _data() const { return data; }
    string _id() const { return id; }
    string _type() const { return type; }
    int _width() const { return width; }
    int _height() const { return height; }
    map<string, Texture2D> _textures() const { return textures; }

protected:
	json data;
	string id;
    string type;
	int width;
	int height;
	map<string, Texture2D> textures = {};

	Character (json data, int width, int height): data(data), width(width), height(height) {}
};

class KeyCharacter: public Character {
public:
	int keys;

    KeyCharacter (json data, int width, int height) : Character(data, width, height) {
        Load();
    }

private:
	void Load() {
        try {
            id = data.at("id");
            type = data.at("type");
            keys = data.at("keys");
            if (keys != 2 && keys != 4) throw "Characters can only have 2 or 4 keys";

            // Load body image and texture
            try {
                textures.insert({ "body", ImageToTexture(mkv::userdataLoc + (string)data.at("textures").at("body"), width, height) });
            } catch (json::exception) {
            }

            // Load instrument image and texture
            try {
                textures.insert({ "instrument", ImageToTexture(mkv::userdataLoc + (string)data.at("textures").at("instrument"), width, height) });
            } catch (json::exception) {
            }

            // Load key images
            vector<vector<string>> handKeys = {
                { "leftIdle", "rightIdle", "key1", "key1-2", "key2" },
                { "leftIdle", "rightIdle", "key1", "key1-2", "key2", "key3", "key3-4", "key4" }
            };
            json keyImages = data.at("textures");

            int const keySet = keys == 2 ? 0 : 1;
            for (int j = 0; j < handKeys[keySet].size(); j++) {

                if (keyImages.contains(handKeys[keySet][j])) {
                    textures.insert({
                        handKeys[keySet][j],
                        ImageToTexture( mkv::userdataLoc + (string)keyImages.at( handKeys[keySet][j] ), width, height )
                    });
                } else textures.insert({ handKeys[keySet][j], ImageToTexture(mkv::userdataLoc + "key.png", width, height) });
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
    PointerCharacter (json data, int width, int height) : Character(data, width, height) {
        Load();
    }

private:
    void Load () {

    }
};

auto CreateCharacter (json data, int width, int height) {
    string const type = data.at("type");

    if (type == "keys") {
        KeyCharacter character{ data, width, height };
    } else if (type == "pointer") {
        PointerCharacter character{ data, width, height };
        return character;
    } else {
        throw "Unknown character type";
    }
}

#endif // !CHARACTER_HPP