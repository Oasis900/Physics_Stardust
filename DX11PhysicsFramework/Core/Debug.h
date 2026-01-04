#pragma once
#include <stdio.h>
#include <Windows.h>

// TODO (Debug) : Implemented 29/12/25

class Debug
{
public:
    static int VDebugPrintF (const char* format, va_list args);
    static int DebugPrintF (const char* format, ...);
};
