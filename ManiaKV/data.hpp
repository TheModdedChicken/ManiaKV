#pragma once
#include "raylib.h"
#include <map>
#include <algorithm>
#include <string>
#include <random>
#include <optional>

#include "Config.hpp"
#include "StageHandler.hpp"

using std::map;
using std::string;
using std::optional;

const inline std::string userdataFolder = "./userdata/";

inline map<string, Texture2D> __textureCache;

namespace cache {
    string GenerateRandString(int length) {
        string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@$*";
        string out = "";

        for (int i = 0; i < length; i++) {
            int position = rand() % (characters.length() - 1);
            out += characters[position];
        }
        return out;
    }

    string CacheTexture(string path) {
        std::replace(path.begin(), path.end(), '\\', '/');

        string fileName = path.substr(path.rfind("/"));
        std::replace(fileName.begin(), fileName.end(), '/', '_');
        
        string id = GenerateRandString(15) + fileName;

        Image image = LoadImage(path.c_str());
        ImageResize(&image, __config.windowWidth, __config.windowHeight);
        Texture2D texture = LoadTextureFromImage(image);
        __textureCache.insert({ id, texture});

        return id;
    }
}