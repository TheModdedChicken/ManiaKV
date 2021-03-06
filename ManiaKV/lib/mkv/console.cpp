#include <iostream>
#include <string>

#include "states.hpp"

using std::string;

namespace console {
	enum LOG {
		INFO = 0,
		WARN = 1,
		ERROR = 2
	};

	void log (string message, string id, LOG type = LOG::INFO) {
		if (!mkv::GetState(mkv::LOGOPS)) return;

		string typeStr = type == LOG::INFO
			? "INFO"
			: type == LOG::WARN ? "WARN" : "ERROR";

		std::cout << "[" << typeStr << " | " << id << "]: " << message << "\n";
	}
}