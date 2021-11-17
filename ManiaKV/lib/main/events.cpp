#include <lib/json.hpp>
#include <string>
#include <map>
#include <vector>
#include <functional>

using nlohmann::json;
using std::string;
using std::map;
using std::vector;
using std::function;

namespace eventKV {
	inline map<string, json> events = {};

	void RegisterEvent(string id, function< void(void) > callback = []{}) {

	}
}