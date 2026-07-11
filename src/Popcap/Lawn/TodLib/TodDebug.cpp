#include "TodDebug.h"
#include "TodCommon.h"

#include <cstdarg>
#include <cstdio>

void TodGetExeDirectory(char *theExePath)
{
    char aDir[256];
    char aFilepath[260];
    char aExt[256];
    char aName[260];

    GetModuleFileNameA(0, &aFilepath[4], 0x104u);
    _splitpath(&aFilepath[4], aDir, &aDir[4], &aName[4], &aExt[4]);
    _makepath(theExePath, aDir, &aDir[4], 0, 0);
}

bool gInAssert = false;

inline void TodVsnprintfEnsureNewLine(char *theBuffer, int theSize, char const *theFormat,
                                      char *theArgList)
{
    int aLen = TodVsnprintf(theBuffer, theSize, theFormat, theArgList);

    if (theBuffer[aLen - 1] != '\n')
    {
        if (aLen + 1 < theSize)
        {
            theBuffer[aLen]     = '\n';
            theBuffer[aLen + 1] = 0;
        }
        else
        {
            theBuffer[aLen - 1] = '\n';
        }
    }
}

void TodAssertFailed(const char *theCondition, const char *theFile, int theLine, const char *theMsg,
                     ...)
{
    __try
    {
        char aMsgBuffer[0x400];

        va_list aArgs;
        va_start(aArgs, theMsg);
        TodVsnprintfEnsureNewLine(aMsgBuffer, sizeof(aMsgBuffer), theMsg, aArgs);
        va_end(aArgs);

        char aBuffer[0x400];

        if (*theCondition)
        {
            TodSnprintf(aBuffer, sizeof(aBuffer), "\n%s(%d)\nassertion failed: '%s'\n%s\n", theFile,
                        theLine, theCondition, aMsgBuffer);
        }
        else
        {
            TodSnprintf(aBuffer, sizeof(aBuffer), "\n%s(%d)\nassertion failed: %s\n", theFile,
                        theLine, aMsgBuffer);
        }

        TodTrace("%s", aBuffer);

        if (IsDebuggerPresent())
        {
            return;
        }

        if (gInAssert)
        {
            TodLog("Assert during exception processing.\n");
            exit(0);
        }

        gInAssert = true;

        RaiseException(0xC0000025, 0, 0, NULL);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}
