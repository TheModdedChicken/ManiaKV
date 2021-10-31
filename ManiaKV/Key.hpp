#pragma once
#include "raylib.h"
#include <vector>
#include <map>

class Key {
public:
	std::map<int, bool> types;
	Texture2D texture;

	Key (std::map<int, bool> keyTypes, Texture2D keyTexture) {
		types = keyTypes;
		texture = keyTexture;
	}
};

