#ifndef DEFS_HPP
#define DEFS_HPP

#include <string>

#define __THISFILE__ SplitAtLast(__FILE__, "\\")

namespace mkv {
	std::string const appVersion = "v0.1.1-lynx";

	std::string const userdataPath = "./userdata/";
	std::string const configPath = userdataPath + "config.json";
	std::string const backupConfigPath = userdataPath + "config.backup.json";
	std::string const statesPath = userdataPath + "states.json";

	typedef struct COORDINATES {
		int x;
		int y;
	} COORDINATES;

	enum class SceneRenderState {
		INVALID = 0,
		INACTIVE = 1,
		ACTIVE = 2
	};

	enum class OverlayRenderState {
		INVALID = 0,
		ACTIVE = 1
	};

	class Error {
	public:
		std::string message;
		std::string id;
		int status;

		Error (std::string message, std::string id, int status = 1) : message(message), id(id), status(status) {}
	};
}

#endif // !DEFS_HPP
