#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <lib/raylib.h>
#include <lib/json.hpp>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <memory>

class Character {
public:
    nlohmann::json const data();
    std::string const id();
    std::string const type();
    int const width();
    int const height();
    std::map<std::string, Texture2D> const textures();
    nlohmann::json const modifiers();

    Character ();

    void UnloadTextures ();

protected:
    nlohmann::json _data = {};
    std::string _id = "";
    std::string _type = "";
    int _width = 0;
    int _height = 0;
    std::map<std::string, Texture2D> _textures = {};
    nlohmann::json _modifiers;

    Character (nlohmann::json data, int width, int height, nlohmann::json modifiers);
};

class KeyboardCharacter : public Character {
public:
    KeyboardCharacter (nlohmann::json data, int width, int height);
    KeyboardCharacter ();

private:
    void Load();
};

// Finish pointer character class for mice and drawing tablets
class PointerCharacter : public Character {
public:
    PointerCharacter (nlohmann::json data, int width, int height);
    PointerCharacter ();

private:
    void Load ();
};

Character CreateCharacter (nlohmann::json data, int width, int height);

#endif // !CHARACTER_HPP