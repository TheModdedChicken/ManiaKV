#ifndef STAGE_HPP
#define STAGE_HPP

#include <lib/json.hpp>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <map>

#include "key.hpp"
#include "character.hpp"

class Stage {
public:
	nlohmann::json data;

	std::shared_ptr<std::map<std::string, Character>> characterImport;
	std::vector<int> shortcut = {};
	std::string id;
	std::vector<std::string> characters = {};
	std::vector<Key> keys;
	std::map<std::string, Texture2D> textures;

	Stage (nlohmann::json data, std::shared_ptr<std::map<std::string, Character>> characters);

	void UnloadTextures ();

private:
	void Load ();
};

#endif // !STAGE_HPP
