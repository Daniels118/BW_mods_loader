#include "ddraw.h"

#include <filesystem>
namespace fs = std::filesystem;

ddrawDll ddraw;

std::list<HMODULE> mods;

static void LoadOriginalDll() {
	char path[MAX_PATH];
	CopyMemory(path + GetSystemDirectoryA(path, MAX_PATH - 10), "\\ddraw.dll", 11); // path to original dll
	printf("Loading \"%s\"...\n", path);
	ddraw.dll = LoadLibraryA(path);
	if (ddraw.dll) {
		ddraw.AcquireDDThreadLock = GetProcAddress(ddraw.dll, "AcquireDDThreadLock");
		ddraw.CheckFullscreen = GetProcAddress(ddraw.dll, "CheckFullscreen");
		ddraw.CompleteCreateSysmemSurface = GetProcAddress(ddraw.dll, "CompleteCreateSysmemSurface");
		ddraw.D3DParseUnknownCommand = GetProcAddress(ddraw.dll, "D3DParseUnknownCommand");
		ddraw.DDGetAttachedSurfaceLcl = GetProcAddress(ddraw.dll, "DDGetAttachedSurfaceLcl");
		ddraw.DDInternalLock = GetProcAddress(ddraw.dll, "DDInternalLock");
		ddraw.DDInternalUnlock = GetProcAddress(ddraw.dll, "DDInternalUnlock");
		ddraw.DSoundHelp = GetProcAddress(ddraw.dll, "DSoundHelp");
		ddraw.DirectDrawCreateClipper = GetProcAddress(ddraw.dll, "DirectDrawCreateClipper");
		ddraw.DirectDrawCreate = GetProcAddress(ddraw.dll, "DirectDrawCreate");
		ddraw.DirectDrawCreateEx = GetProcAddress(ddraw.dll, "DirectDrawCreateEx");
		ddraw.DirectDrawEnumerateA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateA");
		ddraw.DirectDrawEnumerateExA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExA");
		ddraw.DirectDrawEnumerateExW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExW");
		ddraw.DirectDrawEnumerateW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateW");
		ddraw.GetDDSurfaceLocal = GetProcAddress(ddraw.dll, "GetDDSurfaceLocal");
		ddraw.GetOLEThunkData = GetProcAddress(ddraw.dll, "GetOLEThunkData");
		ddraw.GetSurfaceFromDC = GetProcAddress(ddraw.dll, "GetSurfaceFromDC");
		ddraw.RegisterSpecialCase = GetProcAddress(ddraw.dll, "RegisterSpecialCase");
		ddraw.ReleaseDDThreadLock = GetProcAddress(ddraw.dll, "ReleaseDDThreadLock");
		//
		printf("ddraw.dll loaded\n");
	} else {
		printf("Failed to load ddraw.dll\n");
	}
}

static void FreeOriginalDll() {
	if (ddraw.dll) {
		FreeLibrary(ddraw.dll);
	}
}

BOOL dirExists(char* dirName) {
	DWORD attr = GetFileAttributesA(dirName);
	return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool _stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpreserved) {
	FILE* t;
	char* cmd;
	char path[MAX_PATH];
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			cmd = GetCommandLineA();
			if (strstr(cmd, " /console") != NULL) {
				if (GetConsoleWindow() == NULL) {
					AllocConsole();
					t = freopen("CONOUT$", "w", stdout);
					t = freopen("CONIN$", "r", stdin);
				}
			}
			//
			LoadOriginalDll();
			//DisableThreadLibraryCalls(hModule);
			//
			GetModuleFileNameA(NULL, path, MAX_PATH);
			strcpy(strrchr(path, '\\'), "\\mods\\"); // path to mods dir
			if (dirExists(path)) {
				printf("Loading mods from \"%s\"...\n", path);
				for (const auto& entry : fs::directory_iterator(path)) {
					if (entry.path().extension() == ".dll") {
						char dllname[80];
						strcpy(dllname, entry.path().filename().string().c_str());
						printf("Loading mod %s...\n", dllname);
						HMODULE mod = LoadLibraryA(entry.path().string().c_str());
						if (mod == NULL) {
							printf("Failed to load %s\n", dllname);
						} else {
							mods.push_back(mod);
							printf("%s loaded\n", dllname);
						}
					}
				}
				printf("done.\n");
			} else {
				printf("Directory \"%s\" not found\n", path);
			}
			break;
		case DLL_PROCESS_DETACH:
			printf("Unloading mods...\n");
			for (HMODULE mod : mods) {
				GetModuleFileNameA(mod, path, MAX_PATH);
				FreeLibrary(mod);
				printf("%s unloaded\n", path);
			}
			//
			FreeOriginalDll();
			FreeConsole();
			break;
	}
	return true;
}