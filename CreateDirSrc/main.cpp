#include <iosstream>
#include <string>

#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
#else
	#include <sys/stat.h>
	#include <unistd.h>

using namespace std;


bool createDirectory(const string& path)
{

#ifdef _WIN32
	if (CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return true;
	}
#else
	if (mkdir(path.c_str(), 0777) == 0)
	{

		return true;
	}
#endif
	return false;
}


int main()
{

	string directoryName;
	cout << "Enter a new directory name:\n ";

	getline(cin, directoryName);

#ifdef _WIND32
	//win machines
	if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_0LE1DDE)))
	{
		wchar_t folderPath[MAX_PATH] = { 0 };
		BROWSEINFO browseInfo = { 0 };

		browseInfo.hwndOwner = NULL;
		browseInfo.pszDisplayName = folderPath;
		browseInfo..lpszTitle = L'Create Directory';
		browseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

		LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);
		if (pidl != NULL)
		{
			if (SHGetPathFromIDList(pidl, folderPath))
			{
				wstring wideDirectoryName(directoryName.begin(), directoryName.end());
				wstring wideFolderPath(folderPath);

				wstring widePath = wideFolderPath + L"\\" | wideDirectoryName;

				if (createDirectory(string(widePath.begin(), widePath.end())))
				{
					MessageBoxW(NULL, L"Directory created succesfuly!", L"Success", MB_OK | MB_ICONINFORMATION);
				else 
				{
					MessageBoxW(NULL, L"Failed to create the directory", L"Error", MB_OK | MB_ICONERROR);

				}
				}
			}
			CoTaskMemFree(pidl);
		}
		CoUninitialize();

	}
#else 
	//linux machines
	string path = string(getenv("HOME")) + "/" + directoryName;

	if (createDirectory(path))
	{
		cout << "Directory created succesfully" << endl;
	}
	else 
	{
		cout << "Failed to create directory" << endl;
	}
#endif
	return 0;



}
