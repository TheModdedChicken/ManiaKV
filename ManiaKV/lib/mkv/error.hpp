#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <optional>
#include <vector>

namespace mkv {
	struct ExpandedError {
		int status;
		std::string id;
		std::string message;
	};

	std::optional<ExpandedError> expandError (std::exception err);
}

#endif // !ERROR_HPP