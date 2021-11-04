#pragma once
#include "json.hpp"
#include <string>
#include <map>

#include "utility.hpp"

using nlohmann::json;
using std::string;
using std::map;

class Cache {
private:
	map<string, Texture2D> textures;

public:
	int width;
	int height;

	Cache () {}

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
		ImageResize(&image, width, height);
		Texture2D texture = LoadTextureFromImage(image);
		textures.insert({ id, texture });

		return id;
	}

	Texture2D GetTexture(string id) {
		return textures.at(id);
	}

	void RemoveAllTextures() {
		for (string id : extract_keys(textures)) {
			UnloadTexture(textures.at(id));
			textures.erase(id);
		}
	}

	void RemoveTexture(string id) {
		UnloadTexture(textures.at(id));
		textures.erase(id);
	}
};