#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <lib/raylib.h>

#include "utility.hpp"

namespace mkv {
    // Yoinked from https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/

    std::string VectorToString (std::vector<std::string> strs, std::string split) {
        std::string out = "";
        for (auto& str : strs) {
            if (out != "") out += split;
            out += str;
        }
        return out;
    }

    std::vector<std::string> StringToVector (std::string str, std::string split) {
        std::vector<std::string> vec = {};
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(split)) != std::string::npos) {
            token = str.substr(0, pos);
            vec.push_back(token);
            str.erase(0, pos + split.length());
        }
        return vec;
    }

    std::string SplitAtFirst (std::string str, std::string split) {
        int substr = str.find_first_of(split);
        return str.substr((int)substr + 1);
    }

    std::string SplitAtLast (std::string str, std::string split) {
        int substr = str.find_last_of(split);
        return str.substr((int)substr + 1);
    }

    std::string const BoolToString(bool b) {
        return b ? "true" : "false";
    }

    std::string RandString (int length, std::string characters) {
        std::string out = "";
        for (int i = 0; i < length; i++) {
            int position = rand() % (characters.length() - 1);
            out += characters[position];
        }
        return out;
    }

    Texture2D ImageToTexture (std::string path) {
        Image image = LoadImage(path.c_str());
        ImageResize(&image, image.width, image.height);

        Texture2D texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return texture;
    }

    /*
    template<typename V>
    V FindStrPairInVector (vector<std::pair<string, V>> vec, string id) {
        return std::find(vec.begin(), vec.end(), id)
    }*/
}