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
				parts[1], // Status
				parts[2], // ID
				parts[3]  // Message
			};
			return out;
		} else return std::nullopt;
	}
}