#ifndef INPUT_HPP
#define INPUT_HPP

#include <lib/json.hpp>
#include <string>
#include <functional>

bool IsKeyDownSW (int vKey);

int GetKeyCode (std::string key);
int GetKeyCode (char key);

void LoadKeycodes (nlohmann::json keyCodes);
void LoadKeycodeFile (std::string fileLocation);

#endif // !INPUT_HPP