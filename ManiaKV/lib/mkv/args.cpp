#include <string>
#include <map>
#include <functional>
#include <iostream>

#include "utility.hpp"
#include "winutil.hpp"
#include "states.hpp"

#include "args.hpp"

using std::string;
using std::map;
using std::function;

namespace mkv {
	extern map<string, function<void(void)>> args = {
		{"logops", []() {
			SetState(LOGOPS, true);
		}}
	};

	void ParseArgv (int argc, char* argv[]) {
		for (int i = 0; i < argc; ++i) {
			std::cout << "man";
			string arg = argv[i];
			size_t dashLoc = arg.find("--");
			if (dashLoc != -1) {
				string argCut = arg.substr(dashLoc+2);
				std::cout << argCut;
				if (ExistsInMap(args, argCut)) args[argCut]();
			};
		}
	}
}
