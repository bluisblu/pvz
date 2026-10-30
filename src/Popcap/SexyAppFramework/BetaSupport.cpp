#include "BetaSupport.h"
#include "SexyAppBase.h"

using namespace Sexy;

bool BetaSupport::Validate()

{
    bool bVar1;

    bVar1 = GetLoginInfo();
    if (bVar1)
    {
        // SexyAppBase::DemoSyncString(mApp, &mName);
        // SexyAppBase::DemoSyncString(mApp, &mPassword);
        // std::basic_string<>::assign(&mApp->mUserName, &mName, 0, 0xffffffff);
        bVar1 = ValidateWithServer();
        if (bVar1)
        {
            WriteToRegistry();
            mValidated = true;
            return true;
        }
    }
    return false;
}
