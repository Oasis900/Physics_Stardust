#include <string>
#include <Core/Debug.h>

int Debug::VDebugPrintF(const char* format, va_list args)
{
    const UINT32 MAX_CHARS = 1024;
    static char s_buffer[MAX_CHARS];

    int chars_written = vsnprintf(s_buffer, MAX_CHARS, format, args);
    OutputDebugStringA(s_buffer);
    
    return chars_written;
}

int Debug::DebugPrintF(const char* format, ...)
{
    va_list arg_list;
    va_start(arg_list, format);

    int chars_written = VDebugPrintF(format, arg_list);
    va_end(arg_list);

    return chars_written;
}
