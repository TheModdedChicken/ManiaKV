#pragma once
#include "raylib.h"
#include <vector>
#include <map>

using std::map;

class Key {
public:
	map<int, bool> types;
	Texture2D texture;

	Key (map<int, bool> keyTypes, Texture2D keyTexture) {
		types = keyTypes;
		texture = keyTexture;
	}
};

