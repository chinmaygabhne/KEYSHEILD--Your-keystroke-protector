#include "Analyst.h"

#include <iostream>

std::map<DWORD, ProcessThreat> processMonitor;

int CalculateThreatScore(DWORD processID) {
    int score = 0;
    auto& p = processMonitor[processID];

    if (p.hookCount > 0) score += 40;       // Hooking detected
    if (p.pollingRate > 1000) score += 50;  // High frequency polling
    if (!p.isSigned) score += 20;           // Unsigned binary

    return score;
}

void AlertUser(DWORD pid, int score) {
    if (score > 70) {
        std::cout << "[!] HIGH THREAT: Process " << pid << " Score: " << score << "\n";
    }
}

void SeedDemoProcesses() {
    processMonitor.clear();
    processMonitor[4042] = {0, 60, true};
    processMonitor[8120] = {1, 2400, false};
    processMonitor[9216] = {0, 750, false};
}

void RunThreatAnalysisDemo() {
    for (const auto& entry : processMonitor) {
        const DWORD pid = entry.first;
        const int threatScore = CalculateThreatScore(pid);

        std::cout << "Process " << pid << " threat score: " << threatScore << "\n";
        AlertUser(pid, threatScore);
    }
}
