#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <lib/raylib.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "../main/states.hpp"
#include "../main/config.hpp"
#include "../main/utility.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;
using std::function;

static map<int, vector< function<void(void)> >> renderFuncs;

/*
	- Handle rendering
	- 
*/

class Renderer {
	Renderer () {

	}
};

void renderFunction (function<void(void)> func, int layer) {
	int index = layer | 0;

	if (renderFuncs.find(index) == renderFuncs.end()) {
		renderFuncs.insert({ index, { func } });
	} else {
		renderFuncs[index].push_back(func);
	}
}

#endif // !RENDERER_HPP