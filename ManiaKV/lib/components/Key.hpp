#ifndef KEY_HPP
#define KEY_HPP

#include <lib/raylib.h>
#include <vector>
#include <map>

using std::map;
using std::string;

struct Key {
	map<int, bool> types;
	Texture2D texture;
};

#endif // !KEY_HPP