#ifndef KEY_HPP
#define KEY_HPP

#include "raylib.h"
#include <vector>
#include <map>

using std::map;
using std::string;

class Key {
public:
	map<int, bool> types;
	string texture;

	Key (map<int, bool> keyTypes, string keyTexture) {
		types = keyTypes;
		texture = keyTexture;
	}
};

#endif // !KEY_HPP