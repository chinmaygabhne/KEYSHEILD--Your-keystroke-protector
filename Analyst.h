#pragma once

#include <windows.h>

#include <map>

struct ProcessThreat {
    int hookCount = 0;
    int pollingRate = 0;
    bool isSigned = false;
};

extern std::map<DWORD, ProcessThreat> processMonitor;

int CalculateThreatScore(DWORD processID);
void AlertUser(DWORD pid, int score);
void SeedDemoProcesses();
void RunThreatAnalysisDemo();
