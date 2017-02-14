#pragma once
#include <iostream>
#include <Windows.h>
#define AMMO 9999
#define HEALTH 9999

DWORD readMem(HANDLE processHandle, LPCVOID address);
BOOL writeMem(HANDLE processHandle, LPVOID address, int writeData);
void print(bool gState, bool aState);
