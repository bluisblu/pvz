
#include "Board.h"
#include "LawnApp.h"

bool Board::NeedSaveGame()
{
    GameMode mode = mApp->mGameMode;
    if (mode == GAMEMODE_CHALLENGE_ICE || mode == GAMEMODE_CHALLENGE_ZEN_GARDEN || mode == GAMEMODE_TREE_OF_WISDOM)
    {
        return false;
    }
    return mApp->mGameScene == SCENE_PLAYING;
}

int Board::GetNumWavesPerFlag()
{
    bool b = mApp->IsFirstTimeAdventureMode();
    int i;
    if ((!b) || (i = mNumWaves, i >= 10))
    {
        i = 10;
    }
    return i;
}

bool Board::IsFlagWave(int param_1)
{
    int iVar2;

    if (mApp->IsFirstTimeAdventureMode() && mLevel == 1)
    {
        return false;
    }

    if (!mApp->IsFirstTimeAdventureMode() || (iVar2 = mNumWaves, 9 < iVar2))
    {
        iVar2 = 10;
    }
    return param_1 % iVar2 == iVar2 + -1;
}

int Board::GetLevelRandSeed()
{
    int iVar2 = mBoardRandSeed;

    if (mApp->IsAdventureMode())
    {
        return iVar2 + mApp->mPlayerInfo->mId + mApp->mPlayerInfo->mFinishedAdventure * 0x65 + mLevel;
    }
    return mChallenge->mSurvivalStage * 0x65 + mApp->mGameMode;
}

bool Board::IsPoolSquare(int x, int y)
{
    if (x < 0 || y < 0)
    {
        return false;
    }

    if (mGridSquareType[x][y] == GRIDSQUARE_POOL)
    {
        return true;
    }

    return false;
}

bool Board::IsZombieTypePoolOnly(ZombieType param_1)
{
    if (param_1 != ZOMBIE_SNORKEL && param_1 != ZOMBIE_DOLPHIN_RIDER)
    {
        return false;
    }
    return true;
}

bool Board::CanAddBobSled()
{
    for (int i = 0; i < 6; ++i)
    {
        if (mIceMinX[i + 6] > 0 && mIceMinX[i] < 700)
        {
            return true;
        }
    }
    return false;
}

void Board::ShowCoinBank()
{
    mCoinBankFadeCount = 1000;
    return;
}

void Board::PuzzleSaveStreak()
{
    if (mApp->IsEndlessScaryPotter(mApp->mGameMode) || mApp->IsEndlessIZombie(mApp->mGameMode))
    {
        int iVar3 = mChallenge->mSurvivalStage + 1;
        int iVar2 = mApp->GetCurrentChallengeIndex();
        if (iVar3 > mApp->mPlayerInfo->mChallengeRecords[iVar2])
        {
            mApp->mPlayerInfo->mChallengeRecords[iVar2] = iVar3;
            mApp->WriteCurrentUserConfig();
            return;
        }
    }
    return;
}

bool Board::StageIsNight()
{
    if (mBackground == BACKGROUND_2_NIGHT || mBackground == BACKGROUND_4_FOG || mBackground == BACKGROUND_6_BOSS ||
        mBackground == BACKGROUND_MUSHROOM_GARDEN || mBackground == BACKGROUND_ZOMBIQUARIUM)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::StageHasGraveStones()
{
    if (mApp->IsWallnutBowlingLevel())
        return false;

    if (mApp->mGameMode == GAMEMODE_CHALLENGE_POGO_PARTY || mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED ||
        mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST || mApp->mGameMode == GAMEMODE_CHALLENGE_PORTAL_COMBAT ||
        mApp->mGameMode == GAMEMODE_CHALLENGE_LAST_STAND)
        return false;

    if (mApp->IsIZombieLevel() || mApp->IsScaryPotterLevel())
        return false;

    if (mBackground == BACKGROUND_2_NIGHT)
    {
        return true;
    }
    else
    {
        return false;
    };
}

bool Board::StageHasPool()
{
    if ((mBackground != BACKGROUND_3_POOL) && (mBackground != BACKGROUND_4_FOG))
    {
        return false;
    }
    return true;
}

bool Board::StageHasRoof()
{
    if ((mBackground != BACKGROUND_5_ROOF) && (mBackground != BACKGROUND_6_BOSS))
    {
        return false;
    }
    return true;
}

bool Board::StageHasZombieWalkInFromRight()
{
    if (mApp->IsWhackAZombieLevel())
        return false;

    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ICE || mApp->mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN ||
        mApp->mGameMode == GAMEMODE_TREE_OF_WISDOM || mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIQUARIUM)
        return false;

    if (mApp->IsFinalBossLevel() || mApp->IsIZombieLevel() || mApp->IsSquirrelLevel() || mApp->IsScaryPotterLevel())
        return false;

    return true;
}

bool Board::StageHasFog()
{
    if (!mApp->IsStormyNightLevel() && (mApp->mGameMode != GAMEMODE_CHALLENGE_INVISIGHOUL))
    {
        if (mBackground == BACKGROUND_4_FOG)
            return true;
        else
            return false;
    }
    return false;
}

int Board::MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset)
{
    return theRow * 10000 + theRenderLayer + theLayerOffset;
}

/*ZombieID Board::ZombieGetID(Zombie *theZombie)
{
    // return mZombies.DataArrayGetID(theZombie); // TODO: Implement DataArray
}*/