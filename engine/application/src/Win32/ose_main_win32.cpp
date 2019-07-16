#include "OSE/System/FileSystem.h"
#include "OSE/System/FileDiskDevice.h"

#include <Windows.h>

//#include <io.h>
#include <iostream>

extern HINSTANCE g_hInstance;

extern int main(int argc, char** argv);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    g_hInstance = hInstance;

    #ifdef DEBUG_OSE
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    #endif

    OSE::FileDiskDevice device{ "assets", OSE::FileMode::Read };
    OSE::FileSystem::MountShared(device);

    return main(0, nullptr);
}