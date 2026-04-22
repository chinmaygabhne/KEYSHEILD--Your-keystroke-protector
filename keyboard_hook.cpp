#include <windows.h>

#include <iostream>

#include "keyboard_hook.h"

namespace {

HHOOK g_keyboardHook = nullptr;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION &&
        (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        const auto* keyInfo = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        std::cout << "VK: " << keyInfo->vkCode << std::endl;
    }

    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

}  // namespace

int RunKeyboardHookDemo() {
    g_keyboardHook = SetWindowsHookExW(
        WH_KEYBOARD_LL,
        LowLevelKeyboardProc,
        GetModuleHandleW(nullptr),
        0);

    if (g_keyboardHook == nullptr) {
        std::cerr << "Failed to install low-level keyboard hook. Error: "
                  << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Global keyboard hook installed." << std::endl;
    std::cout << "Press Ctrl+C in this console to stop." << std::endl;
    std::cout << "Press any key in Windows to see its virtual-key code." << std::endl;

    MSG msg;
    BOOL result;
    while ((result = GetMessageW(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnhookWindowsHookEx(g_keyboardHook);
    if (result == -1) {
        std::cerr << "Message loop failed. Error: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
