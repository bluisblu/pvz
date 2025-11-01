#include <windows.h>
#include <string>
#include "LawnApp.h"
#include "SexyAppFramework/SexyAppBase.h"
//#include "TodLib/TodStringList.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // (IDA says jpeg_mem_term, probably a merged function)
    //ZenGarden::ZenGardenStart(NULL);

    // Set up string colors and global function pointers
    //TodStringListSetColors(gLawnStringFormats, 12);
    //gGetCurrentLevelName   = LawnGetCurrentLevelName;
    //gAppCloseRequest       = LawnGetCloseRequest;
    //gAppHasUsedCheatKeys   = LawnHasUsedCheatKeys;
    //gExtractResourcesByName = Sexy::ExtractResourcesByName;

    // Allocate and construct LawnApp
    LawnApp* app = new LawnApp();
    gLawnApp = app;

    // Determine which resources.xml path to use
    std::string resPath1 = "properties\\resources.xml";
    bool found = Sexy::FileExists(resPath1.c_str());

    std::string resPath2 = "..\\properties\\resources.xml";
    bool useParentDir = false;

    if (!found) {
        useParentDir = Sexy::FileExists(resPath2.c_str());
    }

    // Set app's working directory
    if (useParentDir) {
        gLawnApp->mChangeDirTo.assign("..");
    } else {
        gLawnApp->mChangeDirTo.assign(".");
    }

    // Initialize, run, and shut down
    gLawnApp->Init();
    gLawnApp->Start();
    gLawnApp->Shutdown();

    // Explicitly destroy LawnApp (matching the 'push 1' destructor call)
    if (gLawnApp) {
        gLawnApp->~LawnApp();  // MSVC may inline operator delete with 1
        gLawnApp = NULL;
    }

    // (IDA says jpeg_mem_term, probably a merged function)
    //ZenGarden::ZenGardenStart(NULL);

    return 0;
}
