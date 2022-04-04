#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <lib/httplib.h>
#include <lib/json.hpp>
#include <string>
#include <iostream>

#include <lib/main/defs.hpp>

using nlohmann::json;

struct GitHubAppVersion {
	std::string url;
	std::string tag;
	std::string name;
};

GitHubAppVersion checkForUpdates () {
	httplib::Client cli("api.github.com");

	cli.set_follow_location(true);
	auto res = cli.Get("/repos/TheModdedChicken/ManiaKV/releases");
	res->status;
	json data = json::parse(res->body);
	GitHubAppVersion out = {};
	out.url = data[0]["html_url"];
	out.tag = data[0]["tag_name"];
	out.name = data[0]["name"];

	if (out.tag == mkv::appVersion) throw "No new updates";
	return out;
}