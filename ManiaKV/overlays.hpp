#ifndef OVERLAYS_HPP
#define OVERLAYS_HPP

#include <string>
#include <vector>
#include <memory>

#include <lib/mkvlib.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

namespace overlays {
	namespace data {

	}

	void downloadDefaultConfig (OverlayData data) {
		string url = "https://maniakv.vercel.app/get-started";

		int const buttonActivity = GuiMessageBox({ 75, 100, 425, 125 }, "Config", "It seems you don't have a config file.\nClick 'GET STARTED' to learn how to make one.", "GET STARTED");
		if (buttonActivity == 1) {
			mkv::OpenWebpage(std::wstring(url.begin(), url.end()).c_str());
		}

		if (buttonActivity != 0) data.renderer->DestroyOverlay(data.type, data.id);
	}

	void updateApplication (OverlayData data) {
		string url = (string)data.body.at("url");

		int const buttonActivity = GuiMessageBox({ 75, 100, 425, 125 }, "Update", ("New update available: " + (string)data.body.at("name") + "\n" + url + "\n").c_str(), "DOWNLOAD;SKIP;CLOSE");
		if (buttonActivity == 1) {
			mkv::OpenWebpage(std::wstring(url.begin(), url.end()).c_str());
		} else if (buttonActivity == 3) {
			mkv::SetState(mkv::STATES::UPDATE_SKIP, (string)data.body.at("tag"), true);
		}

		if (buttonActivity != -1) data.renderer->DestroyOverlay(data.type, data.id);
	}
}

#endif // !OVERLAYS_HPP
