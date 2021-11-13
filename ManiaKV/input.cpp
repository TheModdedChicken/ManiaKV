#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

// Yoinked from https://stackoverflow.com/questions/8640208/what-is-the-fastest-way-to-determine-a-key-press-and-key-holding-in-win32
bool IsKeyDownSW (int vKey) {
	SHORT tabKeyState = GetAsyncKeyState(vKey);
	if ((1 << 15) & tabKeyState) {
		return true;
	} else return false;
}

// Windows Keycodes
// Virtual Key Code Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// This is for US keyboards
map<string, int> keyCodesWIN = {
	{"BACKSPACE", 0x08},
	{"TAB", 0x09},
	{"SHIFT", 0x10},
	{"CTRL", 0x11},
	{"ENTER", 0x0D},
	{"CAPSLOCK", 0x14},
	{"SPACE", 0x20},

	{"0", 0x30},
	{"1", 0x31},
	{"2", 0x32},
	{"3", 0x33},
	{"4", 0x34},
	{"5", 0x35},
	{"6", 0x36},
	{"7", 0x37},
	{"8", 0x38},
	{"9", 0x39},
	{"KP0", 0x60},
	{"KP1", 0x61},
	{"KP2", 0x62},
	{"KP3", 0x63},
	{"KP4", 0x64},
	{"KP5", 0x65},
	{"KP6", 0x66},
	{"KP7", 0x67},
	{"KP8", 0x68},
	{"KP9", 0x69},

	{"A", 0x41},
	{"B", 0x42},
	{"C", 0x43},
	{"D", 0x44},
	{"E", 0x45},
	{"F", 0x46},
	{"G", 0x47},
	{"H", 0x48},
	{"I", 0x49},
	{"J", 0x4A},
	{"K", 0x4B},
	{"L", 0x4C},
	{"M", 0x4D},
	{"N", 0x4E},
	{"O", 0x4F},
	{"P", 0x50},
	{"Q", 0x51},
	{"R", 0x52},
	{"S", 0x53},
	{"T", 0x54},
	{"U", 0x55},
	{"V", 0x56},
	{"W", 0x57},
	{"X", 0x58},
	{"Y", 0x59},
	{"Z", 0x5A},

	{"LEFT_SHIFT", 0xA0},
	{"RIGHT_SHIFT", 0xA1},
	{"LEFT_CTRL", 0xA3},
	{"RIGHT_CTRL", 0xA4},

	{"SEMI_COLON", 0xBA},
	{"COLON", 0xBA},

	{"PLUS", 0xBB},
	{"COMMA", 0xBC},
	{"MINUS", 0xBD},
	{"PERIOD", 0xBE},

	{"SLASH", 0xBF},
	{"QUESTION_MARK", 0xBF},

	{"BACK_TICK", 0xC0},
	{"GRAVE", 0xC0},

	{"LEFT_BRACKET", 0xDB},
	{"LEFT_CURLY_BRACKET", 0xDB},

	{"BACK_SLASH", 0xDC},
	{"BAR", 0xDC},

	{"RIGHT_BRACKET", 0xDD},
	{"RIGHT_CURLY_BRACKET", 0xDD},

	{"SINGLE_QUOTE", 0xDE},
	{"DOUBLE_QUOTE", 0xDE},

	{"OEM_8", 0xDF}
};

// Raylib Keycodes
map<string, int> keyCodesRAY = {
	{"KEY_NULL", 0},

	// Alphanumeric keys
	{"KEY_APOSTROPHE", 39},
	{"KEY_COMMA", 44},
	{"KEY_MINUS", 45},
	{"KEY_PERIOD", 46},
	{"KEY_SLASH", 47},
	{"0", 48},
	{"1", 49},
	{"2", 50},
	{"3", 51},
	{"4", 52},
	{"5", 53},
	{"6", 54},
	{"7", 55},
	{"8", 56},
	{"9", 57},
	{"KEY_SEMICOLON", 59},
	{"KEY_EQUAL", 61},
	{"A", 65},
	{"B", 66},
	{"C", 67},
	{"D", 68},
	{"E", 69},
	{"F", 70},
	{"G", 71},
	{"H", 72},
	{"I", 73},
	{"J", 74},
	{"K", 75},
	{"L", 76},
	{"M", 77},
	{"N", 78},
	{"O", 79},
	{"P", 80},
	{"Q", 81},
	{"R", 82},
	{"S", 83},
	{"T", 84},
	{"U", 85},
	{"V", 86},
	{"W", 87},
	{"X", 88},
	{"Y", 89},
	{"Z", 90},
	{"LEFT_BRACKET", 91},
	{"BACKSLASH", 88},
	{"RIGHT_BRACKET", 89},
	{"GRAVE", 90},

	// Keypad Keys
	{"KP_0", 320},
	{"KP_1", 321},
	{"KP_2", 322},
	{"KP_3", 323},
	{"KP_4", 324},
	{"KP_5", 325},
	{"KP_6", 326},
	{"KP_7", 327},
	{"KP_8", 328},
	{"KP_9", 329},
	{"KP_DECIMAL", 330},
	{"KP_DIVIDE", 331},
	{"KP_MULTIPLY", 332},
	{"KP_SUBTRACT", 333},
	{"KP_ADD", 334},
	{"KP_ENTER", 335},
	{"KP_EQUAL", 336},

	// Function keys
	{"SPACE", 32},
	{"ESCAPE", 256},
	{"ENTER", 257},
	{"TAB", 258},
	{"BACKSPACE", 259},
	{"INSERT", 260},
	{"DELETE", 261},
	{"RIGHT", 262},
	{"LEFT", 263},
	{"DOWN", 264},
	{"UP", 265},
	{"PAGE_UP", 266},
	{"PAGE_DOWN", 267},
	{"HOME", 268},
	{"END", 269},
	{"CAPS_LOCK", 280},
	{"SCROLL_LOCK", 281},
	{"NUM_LOCK", 282},
	{"PRINT_SCREEN", 283},
	{"PAUSE", 284},
	{"F1", 290},
	{"F2", 291},
	{"F3", 292},
	{"F4", 293},
	{"F5", 294},
	{"F6", 295},
	{"F7", 296},
	{"F8", 297},
	{"F9", 298},
	{"F10", 299},
	{"F11", 300},
	{"F12", 301},
	{"LEFT_SHIFT", 340},
	{"LEFT_CONTROL", 341},
	{"LEFT_ALT", 342},
	{"LEFT_SUPER", 343},
	{"RIGHT_SHIFT", 344},
	{"RIGHT_CONTROL", 345},
	{"RIGHT_ALT", 346},
	{"RIGHT_SUPER", 347},
	{"KB_MENU", 348},
};

int GetKeyCode (string key) {
	return keyCodesWIN.at(key);
}

int GetKeyCode (char key) {
	return VkKeyScan(TCHAR(key));
}

/*int KConvertRAYtoWIN (int key) {
	keyCodesRAY.
}*/