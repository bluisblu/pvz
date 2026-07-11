// Precompile.cpp - Source file to generate precompiled header
#include "Precompile.h"

#ifdef BETA_BUILD

// Global variable for bad_alloc message (referenced in PDB)
const char *_bad_alloc_Message = "bad allocation";

// Exception filter for beta builds
int TodExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
    // Log exception information here if needed
    return EXCEPTION_EXECUTE_HANDLER;
}

// Assertion failure handler
void TodAssertFailed(const char *file, const char *function, int line, const char *message, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, message);
    _vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    // Display message box or log to file
    char fullMessage[8192];
    sprintf(fullMessage,
            "Assertion Failed!\n\n"
            "File: %s\n"
            "Function: %s\n"
            "Line: %d\n\n"
            "Expression: %s",
            file, function, line, buffer);

    MessageBoxA(NULL, fullMessage, "PvZ Assertion", MB_OK | MB_ICONERROR);
}

// Function that doesn't return - used after assertion failures
void DoesntReturnStub(void)
{
    // Terminate the application
    ExitProcess(1);
}

#endif // BETA_BUILD
