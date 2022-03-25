#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <vector>

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

std::string arrToStr (std::vector<std::string> strs, std::string split = "") {
    std::string out = "";
    for (auto& str : strs) {
        if (out != "") out += split;
        out += str;
    }
    return out;
}

/*
template<typename V>
V FindStrPairInVector (vector<std::pair<string, V>> vec, string id) {
    return std::find(vec.begin(), vec.end(), id)
}*/

#endif // !UTILITY_HPP
