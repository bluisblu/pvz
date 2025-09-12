#include "LawnApp.h"
#include "PlayerInfo.h"

bool LawnApp::CanPauseNow()
{
    if (mBoard == NULL)
        return false;

    if (mSeedChooserScreen != NULL && mSeedChooserScreen->mMouseVisible)
    {
        return false;
    }

    if (mBoard->mBoardFadeOutCounter >= 0)
        return false;

    if (mCrazyDaveState != CRAZY_DAVE_OFF)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN || mGameMode == GAMEMODE_TREE_OF_WISDOM)
        return false;

    return (bool)(GetDialogCount() <= 0);
}

void LawnApp::ReadFromRegistry()
{
    Sexy::SexyApp::ReadFromRegistry();
}

bool LawnApp::WriteCurrentUserConfig()
{
    if (this->mPlayerInfo != 0x0)
    {
        mPlayerInfo->SaveDetails();
    }
    return true;
}

void LawnApp::KillGameSelector()
{
    if (mGameSelector)
    {
        mWidgetManager->RemoveWidget(mGameSelector);
        SafeDeleteWidget(mGameSelector);
        mGameSelector = NULL;
    }
}