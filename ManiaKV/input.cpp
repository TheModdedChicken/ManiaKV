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

// Virtual Key Code Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// This is for US keyboards
map<string, int> keyCodes = {
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
	{"TILDE", 0xC0},

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

int GetKeyCode (string key) {
	return keyCodes.at(key);
}

int GetKeyCode (char key) {
	return VkKeyScan(TCHAR(key));
}