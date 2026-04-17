#include "Analyst.h"
#include "keyboard_hook.h"

#include <iostream>
#include <string>

namespace {

void PrintUsage() {
    std::cout << "KeyShield demo application\n\n";
    std::cout << "Usage:\n";
    std::cout << "  KeyShield.exe analyze   Run the process threat scoring demo\n";
    std::cout << "  KeyShield.exe hook      Run the low-level keyboard hook demo\n";
    std::cout << "  KeyShield.exe help      Show this help text\n\n";
    std::cout << "If no command is provided, the analysis demo runs by default.\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string command = argc > 1 ? argv[1] : "analyze";

    if (command == "analyze") {
        SeedDemoProcesses();
        RunThreatAnalysisDemo();
        return 0;
    }

    if (command == "hook") {
        return RunKeyboardHookDemo();
    }

    if (command == "help" || command == "--help" || command == "-h") {
        PrintUsage();
        return 0;
    }

    std::cerr << "Unknown command: " << command << "\n\n";
    PrintUsage();
    return 1;
}
