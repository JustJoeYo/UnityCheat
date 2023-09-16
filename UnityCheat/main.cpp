#include "includes.h"

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    AllocConsole();
    SetConsoleTitleA("[+] Debug Console");
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Attaching to game
        MemoryBase::GameAssembly = (UINT_PTR)GetModuleHandleA("GameAssembly.dll");
        if (MemoryBase::GameAssembly != 0) {
            Hooks::Hook();
        }

    case DLL_PROCESS_DETACH:
        // Detaching from game

        break;
    }
    return TRUE;
}