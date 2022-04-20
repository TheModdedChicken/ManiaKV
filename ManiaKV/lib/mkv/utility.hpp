#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <lib/raylib.h>

namespace mkv {
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

    std::string VectorToString (std::vector<std::string> strs, std::string split = "");

    std::vector<std::string> StringToVector (std::string str, std::string split);

    std::string SplitAtFirst (std::string str, std::string split);

    std::string SplitAtLast (std::string str, std::string split);

    std::string const BoolToString(bool b);

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

    std::string RandString (int length, std::string characters = "abcdefghijklmnopqrstuvwxyz1234567890");

    Texture2D ImageToTexture (std::string path);
}

#endif // !UTILITY_HPP
