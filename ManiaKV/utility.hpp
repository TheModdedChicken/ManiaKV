#pragma once
#include <string>
#include <vector>

bool ContainsAnyString (std::string string, std::vector<std::string> strings) {
	bool passed = false;
	for (std::string testString : strings) if (string.find(testString) != -1) passed = true;
	return passed;
}