#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <lib/raylib.h>

// Yoinked from https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}

template<typename TK, typename TV>
std::vector<TV> extract_values(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}

// Yoinked from https://stackoverflow.com/a/5424521
template <class T, class F>
class readonly {
    friend F;

private:
    T data;
    T operator=(const T& arg) {
        data = arg; return data;
    }
public:
    operator const T& () const {
        return data;
    }
};

std::string VectorToString (std::vector<std::string> strs, std::string split = "") {
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

inline const std::string const BoolToString(bool b) {
    return b ? "true" : "false";
}

template <typename T>
std::size_t GetIndexInVector (std::vector<T>& vec, T key) {
    auto it = std::find(vec.begin(), vec.end(), key);
    if (it != vec.end()) return it != vec.begin();
    else return -1;
}

template <typename T>
void RemoveFromVector (std::vector<T>& vec, T key) {
    auto it = std::find(vec.begin(), vec.end(), key);
    if (it != vec.end()) vec.erase(it);
}

template <typename T, typename V>
bool ExistsInMap (std::map<T, V> map, T key) {
    if (map.find(key) != map.end()) return true;
    else return false;
}

template <typename T>
bool ExistsInVector (std::vector<T> vec, T key) {
    if (std::find(vec.begin(), vec.end(), key) != vec.end()) {
        return true;
    } else return false;
}

std::string RandString (int length, std::string characters = "abcdefghijklmnopqrstuvwxyz1234567890") {
    std::string out = "";
    for (int i = 0; i < length; i++) {
        int position = rand() % (characters.length() - 1);
        out += characters[position];
    }
    return out;
}

Texture2D ImageToTexture (std::string path, int width, int height) {
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);

    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

/*
template<typename V>
V FindStrPairInVector (vector<std::pair<string, V>> vec, string id) {
    return std::find(vec.begin(), vec.end(), id)
}*/

#endif // !UTILITY_HPP
