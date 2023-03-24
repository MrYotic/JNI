#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;

BOOL __stdcall DllMain(HINSTANCE handle, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			HMODULE module = GetModuleHandleW(L"Sample");
			if (module == 0)
			{
				HMODULE baseModule = GetModuleHandleW(L"Wrapper");
				TCHAR filenameBuff[MAX_PATH];
				GetModuleFileNameW(baseModule, filenameBuff, _countof(filenameBuff));
				wstring filenameTemp(&filenameBuff[0]);
				string filename(filenameTemp.begin(), filenameTemp.end());

				string directory = ((string)filename).substr(0, ((string)filename).find_last_of("/\\"));			

				string minecraftESPPath = directory.append("\\Sample.dll");
				module = LoadLibraryW(wstring(minecraftESPPath.begin(), minecraftESPPath.end()).c_str());
			}

			void* loadFuncPtr = GetProcAddress(module, "Load");
			((void(*)(void))loadFuncPtr)();
		}
		case DLL_PROCESS_DETACH:
		{
			HMODULE module = GetModuleHandleW(L"Sample");
			void* unloadFuncPtr = GetProcAddress(module, "Unload");
			((void(*)(void))unloadFuncPtr)();
		}
		break;
	}
	return TRUE;
}