#ifndef KEY_HPP
#define KEY_HPP

#include <lib/raylib.h>
#include <vector>
#include <map>

using std::map;
using std::string;

class Key {
public:
	map<int, bool> _types() const { return types; }
    Texture2D _texture() const { return texture; }

	Key (map<int, bool> types, Texture2D texture): types(types), texture(texture) {}

private:
	map<int, bool> types;
	Texture2D texture;
};

#endif // !KEY_HPP