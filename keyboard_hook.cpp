// Global low-level keyboard hook console application
// Prints virtual-key codes for all key presses system-wide.

#ifndef _WIN32
#error This project is Windows-only and requires _WIN32.
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

HHOOK g_hHook = nullptr;

// Low-level keyboard hook callback
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKB = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

        // React on keydown events (you can also log keyup if desired)
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            std::cout << "VK Code: " << pKB->vkCode << std::endl;
        }
    }

    // Pass the event to the next hook in the chain
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

int main()
{
    // Install the global low-level keyboard hook
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    g_hHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,        // low-level keyboard hook
        LowLevelKeyboardProc,  // callback
        hInstance,             // handle to DLL/module (current exe)
        0                      // hook all threads (system-wide)
    );

    if (!g_hHook)
    {
        std::cerr << "Failed to install hook. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Global keyboard hook installed. Press keys to see VK codes." << std::endl;
    std::cout << "Press Ctrl+C in this console to exit." << std::endl;

    // Standard Windows message loop to keep the hook active
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Uninstall the hook before exiting
    if (g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = nullptr;
    }

    return 0;
}
