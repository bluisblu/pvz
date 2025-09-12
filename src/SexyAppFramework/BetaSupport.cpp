#include "BetaSupport.h"
#include "SexyAppBase.h"

using namespace Sexy;

bool BetaSupport::Validate()

{
    bool bVar1;

    bVar1 = GetLoginInfo();
    if (bVar1)
    {
        // SexyAppBase::DemoSyncString(this->mApp, &this->mName);
        // SexyAppBase::DemoSyncString(this->mApp, &this->mPassword);
        // std::basic_string<>::assign(&this->mApp->mUserName, &this->mName, 0, 0xffffffff);
        bVar1 = ValidateWithServer();
        if (bVar1)
        {
            WriteToRegistry();
            this->mValidated = true;
            return true;
        }
    }
    return false;
}
