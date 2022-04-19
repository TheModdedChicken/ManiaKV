#include <Windows.h>
#include <string>

using std::wstring;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
int CreateDialogueBox(LPCWSTR title, LPCWSTR message, UINT context) {
	int msgboxID = MessageBox(
		NULL,
		message,
		title,
		context
	);

	return msgboxID;
}

int SpawnErrorDialogueBox(wstring title, wstring message) {
	return CreateDialogueBox((LPCWSTR)title.c_str(), (LPCWSTR)message.c_str(), MB_ICONERROR | MB_OK | MB_DEFBUTTON2);
}