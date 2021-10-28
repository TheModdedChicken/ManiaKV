#pragma once
#include <vector>
#include <map>
#include "raylib.h"

class Key {
public:
	std::map<int, bool> types;
	Texture2D texture;

	Key (std::map<int, bool> keyTypes, Texture2D keyTexture) {
		types = keyTypes;
		texture = keyTexture;
	}
};

