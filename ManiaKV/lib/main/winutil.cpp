#include <windows.h>
#include <shellapi.h>
#include <wchar.h>

namespace mkv {
	void OpenWebpage (const wchar_t* url) {
		ShellExecute(0, 0, url, 0, 0, SW_SHOW);
	}
}