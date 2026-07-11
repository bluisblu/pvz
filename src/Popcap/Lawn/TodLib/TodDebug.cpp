#include "TodDebug.h"

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
