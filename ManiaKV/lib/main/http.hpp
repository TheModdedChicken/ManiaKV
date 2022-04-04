#ifndef HTTP_HPP
#define HTTP_HPP

struct GitHubAppVersion {
	std::string url;
	std::string tag;
	std::string name;
};

GitHubAppVersion checkForUpdates ();

#endif // !HTTP_HPP
