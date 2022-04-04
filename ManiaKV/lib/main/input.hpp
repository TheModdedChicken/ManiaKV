#ifndef INPUT_HPP
#define INPUT_HPP

#include <lib/json.hpp>
#include <string>
#include <functional>
#include <vector>
#include "./defs.hpp"

namespace mkv {
	// Windows Keycodes
	// Virtual Key Code Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	// This is for US keyboards
	namespace keys {
		enum KEYCODES {
			BACKSPACE = 0x08,
			TAB = 0x09,
			SHIFT = 0x10,
			CTRL = 0x11,
			ALT = 0x12,
			ENTER = 0x0D,
			CAPSLOCK = 0x14,
			SPACE = 0x20,

			ZERO = 0x30,
			ONE = 0x31,
			TWO = 0x32,
			THREE = 0x33,
			FOUR = 0x34,
			FIVE = 0x35,
			SIX = 0x36,
			SEVEN = 0x37,
			EIGHT = 0x38,
			NINE = 0x39,
			KP_ZERO = 0x60,
			KP_ONE = 0x61,
			KP_TWO = 0x62,
			KP_THREE = 0x63,
			KP_ = 0x64,
			KP_FIVE = 0x65,
			KP_SIX = 0x66,
			KP_SEVEN = 0x67,
			KP_EIGHT = 0x68,
			KP_NINE = 0x69,

			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A,

			LEFT_SHIFT = 0xA0,
			RIGHT_SHIFT = 0xA1,
			LEFT_CTRL = 0xA2,
			RIGHT_CTRL = 0xA3,
			LEFT_ALT = 0xA4,
			RIGHT_ALT = 0xA5,

			SEMI_COLON = 0xBA,
			COLON = 0xBA,

			PLUS = 0xBB,
			COMMA = 0xBC,
			MINUS = 0xBD,
			PERIOD = 0xBE,

			SLASH = 0xBF,
			QUESTION_MARK = 0xBF,

			BACK_TICK = 0xC0,
			GRAVE = 0xC0,

			LEFT_BRACKET = 0xDB,
			LEFT_CURLY_BRACKET = 0xDB,

			BACK_SLASH = 0xDC,
			BAR = 0xDC,

			RIGHT_BRACKET = 0xDD,
			RIGHT_CURLY_BRACKET = 0xDD,

			SINGLE_QUOTE = 0xDE,
			DOUBLE_QUOTE = 0xDE,

			OEM_8 = 0xDF
		};
	}

	int KeyState (int key);

	bool IsKeyDown (int vKey);
	int IsKeyDown ();

	int GetKeyCode (std::string key);
	int GetKeyCode (char key);
	std::string GetKey (int keycode);

	void LoadKeycodes (nlohmann::json keyCodes);
	void LoadKeycodeFile (std::string fileLocation);

	bool IsKeyHeld (std::vector<int> keys, bool global = false);
	bool IsKeyPressed (std::vector<int> keys, bool global = false);
	std::vector<std::string> AreKeysPressed (bool global = false);

	mkv::COORDINATES GetGlobalCursorPos ();
}

#endif // !INPUT_HPP