#pragma once
#include <stdio.h>
#include <Windows.h>

class Debug
{
public:
    static int VDebugPrintF (const char* format, va_list args);
    static int DebugPrintF (const char* format, ...);
};
