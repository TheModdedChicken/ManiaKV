#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <string>

namespace console {
	enum LOG {
		INFO = 0,
		WARN = 1,
		ERROR = 2
	};

	void log (std::string message, std::string id, LOG type = LOG::INFO);
}

#endif // !CONSOLE_HPP
