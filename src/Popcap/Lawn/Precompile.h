// Precompile.h - Precompiled header for PvZ
#ifndef __PRECOMPILE_H__
#define __PRECOMPILE_H__

// Windows and standard includes
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Ensure IsDebuggerPresent is available (may not be in older SDK headers)
#ifndef IsDebuggerPresent
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
#endif

// DirectX includes
#include <d3d9.h>
#include <d3dx9.h>

// C++ Standard Library
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

#ifdef BETA_BUILD

// Exception filter that handles assertions in beta builds
extern int TodExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS *ep);

// Assertion function
extern void TodAssertFailed(const char *file, const char *function, int line, const char *message,
                            ...);

// Function that doesn't return (for assertion failures)
extern void DoesntReturnStub(void);

// SEH wrapper macros for beta builds
#define TOD_FUNCTION_PROLOG                                                                        \
    __try                                                                                          \
    {

#define TOD_FUNCTION_EPILOG                                                                        \
    }                                                                                              \
    __except (EXCEPTION_EXECUTE_HANDLER)                                                           \
    {                                                                                              \
        TodAssertFailed(__FILE__, __FUNCTION__, __LINE__, "Exception caught");                     \
        DoesntReturnStub();                                                                        \
    }

// Helper macro for assertions
#define TOD_ASSERT(condition)                                                                      \
    do                                                                                             \
    {                                                                                              \
        if (!(condition))                                                                          \
        {                                                                                          \
            TodAssertFailed(__FILE__, __FUNCTION__, __LINE__, #condition);                         \
            if (IsDebuggerPresent())                                                               \
            {                                                                                      \
                __debugbreak();                                                                    \
            }                                                                                      \
            DoesntReturnStub();                                                                    \
        }                                                                                          \
    } while (0)

#else

// Release builds - no SEH wrappers
#define TOD_FUNCTION_PROLOG
#define TOD_FUNCTION_EPILOG
#define TOD_ASSERT(condition) ((void)0)

#endif // BETA_BUILD

#endif // __PRECOMPILE_H__
