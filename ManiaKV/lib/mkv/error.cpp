#include <string>
#include <optional>
#include <vector>

#include "error.hpp"
#include "utility.hpp"

using std::optional;
using std::string;
using std::vector;

namespace mkv {
	optional<ExpandedError> expandError (std::exception err) {
		string const msg = err.what();

		if (msg.find("mkv::") != string::npos) {
			vector<string> parts = StringToVector(msg, "::");
			ExpandedError out{
				std::stoi(parts[1]), // Status
				parts[2], // ID
				parts.size() >= 4 ? parts[3] : "Error Message Undefined"  // Message
			};
			return out;
		} else return std::nullopt;
	}
}