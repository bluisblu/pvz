
#include "Board.h"
#include "Challenge.h"
#include "LawnApp.h"

bool Board::NeedSaveGame()
{
    GameMode mode = mApp->mGameMode;
    if (mode == GAMEMODE_CHALLENGE_ICE || mode == GAMEMODE_CHALLENGE_ZEN_GARDEN || mode == GAMEMODE_TREE_OF_WISDOM)
    {
        return false;
    }
    if (mApp->mGameScene == SCENE_PLAYING)
    {
        return true;
    }

    return false;
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

bool Board::IsFlagWave(int theWaveNumber)
{
    if (mApp->IsFirstTimeAdventureMode() && mLevel == 1)
    {
        return false;
    }

    int mNumWaves;
    if (!mApp->IsFirstTimeAdventureMode() || (mNumWaves = this->mNumWaves, mNumWaves > 10))
    {
        mNumWaves = 10;
    }
    return theWaveNumber % mNumWaves == mNumWaves + -1;
}

int Board::GetLevelRandSeed()
{
    int v3; // edi

    v3 = mBoardRandSeed + mApp->mPlayerInfo->mId;
    if (mApp->IsAdventureMode())
    {
        return mLevel + 101 * mApp->mPlayerInfo->mFinishedAdventure + v3;
    }
    else
    {
        return mApp->mGameMode + 101 * mChallenge->mSurvivalStage;
    }
}

bool Board::IsPlantInCursor()
{
    CursorType mCursorType; // eax

    mCursorType = mCursorObject->mCursorType;
    if (mCursorType == CURSOR_TYPE_PLANT_FROM_BANK || mCursorType == CURSOR_TYPE_PLANT_FROM_USABLE_COIN ||
        mCursorType == CURSOR_TYPE_PLANT_FROM_GLOVE || mCursorType == CURSOR_TYPE_PLANT_FROM_DUPLICATOR ||
        mCursorType == CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW)
    {
        return true;
    }
    return false;
}

SeedType Board::GetSeedTypeInCursor()
{
    SeedType result;             // eax
    CursorObject *mCursorObject; // esi
    CursorType mCursorType;      // eax

    if (this->mCursorObject->mCursorType == CURSOR_TYPE_WHEEELBARROW && mApp->mZenGarden->GetPottedPlantInWheelbarrow())
    {
        return mApp->mZenGarden->GetPottedPlantInWheelbarrow()->mSeedType;
    }
    mCursorObject = this->mCursorObject;
    mCursorType = mCursorObject->mCursorType;
    if (mCursorType != CURSOR_TYPE_PLANT_FROM_BANK && mCursorType != CURSOR_TYPE_PLANT_FROM_USABLE_COIN &&
        mCursorType != CURSOR_TYPE_PLANT_FROM_GLOVE && mCursorType != CURSOR_TYPE_PLANT_FROM_DUPLICATOR &&
        mCursorType != CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW)
    {
        return SEED_NONE;
    }
    result = mCursorObject->mType;
    if (result == SEED_IMITATER)
        return mCursorObject->mImitaterType;
    return result;
}

bool Board::IsPoolSquare(int theGridX, int theGridY)
{
    if (theGridX < 0 || theGridY < 0)
    {
        return false;
    }

    if (mGridSquareType[theGridX][theGridY] == GRIDSQUARE_POOL)
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

bool Board::CanInteractWithBoardButtons()
{
    CursorType mCursorType; // eax
    bool result;            // al

    if (!this->mPaused && mApp->GetDialogCount() <= 0 &&
        (mCursorType = this->mCursorObject->mCursorType, mCursorType != CURSOR_TYPE_PLANT_FROM_BANK) &&
        mCursorType != CURSOR_TYPE_PLANT_FROM_USABLE_COIN && mCursorType != CURSOR_TYPE_PLANT_FROM_GLOVE &&
        mCursorType != CURSOR_TYPE_PLANT_FROM_DUPLICATOR && mCursorType != CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW &&
        mCursorType != CURSOR_TYPE_SHOVEL && mCursorType != CURSOR_TYPE_WATERING_CAN &&
        mCursorType != CURSOR_TYPE_FERTILIZER && mCursorType != CURSOR_TYPE_BUG_SPRAY &&
        mCursorType != CURSOR_TYPE_PHONOGRAPH && mCursorType != CURSOR_TYPE_CHOCOLATE &&
        mCursorType != CURSOR_TYPE_GLOVE && mCursorType != CURSOR_TYPE_MONEY_SIGN &&
        mCursorType != CURSOR_TYPE_WHEEELBARROW && mCursorType != CURSOR_TYPE_TREE_FOOD && mBoardFadeOutCounter < 0 &&
        mChallenge->mChallengeState != STATECHALLENGE_ZEN_FADING && mApp->mCrazyDaveState == CRAZY_DAVE_OFF)
    {
        return true;
    }
    return false;
}

void Board::MouseMove(int x, int y)
{
    MouseDrag(x, y);
    mChallenge->MouseMove(x, y);
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

bool Board::IsFinalScaryPotterStage()
{
    if (!mApp->IsScaryPotterLevel())
    {
        return false;
    }

    if (mApp->IsAdventureMode())
    {
        return mChallenge->mSurvivalStage == 2;
    }

    if (!mApp->IsEndlessScaryPotter(mApp->mGameMode))
    {
        return true;
    }

    return false;
}

bool Board::IsLastStandFinalStage()
{
    if (mApp->mGameMode != GAMEMODE_CHALLENGE_LAST_STAND)
    {
        return false;
    }
    if (mChallenge->mSurvivalStage != 4)
    {
        return false;
    }
    return true;
}

bool Board::HasLevelAwardDropped()
{
    if (mLevelAwardSpawned || mNextSurvivalStageCounter > 0 || mBoardFadeOutCounter >= 0)
    {
        return true;
    }
    return false;
}

bool Board::RowCanHaveZombies(int theRow)
{
    if (theRow > 5U)
        return false;
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_RESODDED && theRow <= 4)
        return true;
    if (mPlantRow[theRow] != PLANTROW_DIRT)
    {
        return true;
    }
    return false;
}

bool Board::HasProgressMeter()
{
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED || mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST ||
        mApp->IsFinalBossLevel() || mApp->IsSlotMachineLevel() || mApp->IsSquirrelLevel() || mApp->IsIZombieLevel())
    {
        return true;
    }

    if (mProgressMeterWidth == 0)
    {
        return false;
    }

    if (mApp->IsContinuousChallenge() || mApp->mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN ||
        mApp->mGameMode == GAMEMODE_TREE_OF_WISDOM || mApp->IsScaryPotterLevel())
    {
        return false;
    }

    return true;
}

bool Board::ProgressMeterHasFlags()
{
    if (mApp->IsFirstTimeAdventureMode() && mLevel == 1)
        return false;

    if (mApp->IsWhackAZombieLevel() || mApp->IsFinalBossLevel() || mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED ||
        mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST || mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIQUARIUM ||
        mApp->IsSlotMachineLevel() || mApp->IsSquirrelLevel() || mApp->IsIZombieLevel())
        return false;

    return true;
}

bool Board::IsScaryPotterDaveTalking()
{
    if (mApp->IsScaryPotterLevel() && this->mNextSurvivalStageCounter > 0 && this->mApp->mCrazyDaveState)
    {
        return true;
    }
    return false;
}

void Board::SetPinataMode(bool theEnablePinata)
{
    mApp->PlayFoley(FOLEY_JUICY);
    mPinataMode = theEnablePinata;
    mApp->mPinataMode = theEnablePinata;
}

/*void Board::SetDaisyMode(bool theEnableDaisy)
{
    mApp->PlaySample(Sexy::SOUND_LOADINGBAR_FLOWER);
    mDaisyMode = theEnableDaisy;
    mApp->mDaisyMode = theEnableDaisy;
}*/

/*void Board::SetSukhbirMode(bool theEnableSukhbir)
{
    mApp->PlaySample(Sexy::SOUND_SUKHBIR);
    mSukhbirMode = theEnableSukhbir;
    mApp->mSukhbirMode = theEnableSukhbir;
}*/

void Board::AddSunMoney(int theAmount)
{
    mSunMoney += theAmount;
    if (mSunMoney > 9990)
        mSunMoney = 9990;
}

bool Board::HasConveyorBeltSeedBank()
{
    if (!mApp->IsFinalBossLevel() && !mApp->IsMiniBossLevel() && !mApp->IsShovelLevel() &&
        !mApp->IsWallnutBowlingLevel() && !mApp->IsLittleTroubleLevel() && !mApp->IsStormyNightLevel() &&
        !mApp->IsBungeeBlitzLevel())
    {
        GameMode mode = mApp->mGameMode;
        if (mode != GAMEMODE_CHALLENGE_PORTAL_COMBAT && mode != GAMEMODE_CHALLENGE_COLUMN &&
            mode != GAMEMODE_CHALLENGE_INVISIGHOUL)
        {
            return false;
        }
    }

    return true;
}

int Board::GetNumSeedsInBank()
{
    if (mApp->IsScaryPotterLevel())
    {
        return 1;
    }
    if (mApp->IsWhackAZombieLevel())
    {
        return 3;
    }
    if (mApp->IsChallengeWithoutSeedBank())
    {
        return 0;
    }
    if (HasConveyorBeltSeedBank())
    {
        return 10;
    }
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ICE)
    {
        return 6;
    }
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED || mApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST)
    {
        return 0;
    }
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIQUARIUM)
    {
        return 2;
    }
    if (mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_1 || mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_2 ||
        mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_3 || mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_4)
    {
        return 3;
    }
    if (mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_5 || mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_6 ||
        mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_7)
    {
        return 4;
    }
    if (mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_8)
    {
        return 6;
    }
    if (mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_9)
    {
        return 8;
    }
    if (mApp->mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS)
    {
        return 9;
    }
    if (mApp->IsSlotMachineLevel())
    {
        return 3;
    }

    int aNumSeeds = mApp->mPlayerInfo->mPurchases[21] + 6;
    int aSeedsAvailable = mApp->GetSeedsAvailable();
    return min(aNumSeeds, aSeedsAvailable);
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

int Board::GetSeedPacketPositionX(int theIndex)
{
    int mNumPackets; // edi

    // TODO: Implement SeedBank
    // mNumPackets = this->mSeedBank->mNumPackets;
    if (mApp->IsSlotMachineLevel())
        return 59 * theIndex + 247;
    if (Board::HasConveyorBeltSeedBank())
        return 50 * theIndex + 91;
    if (mNumPackets < 8)
        return 59 * theIndex + 85;
    if (mNumPackets == 8)
        return 54 * theIndex + 81;
    if (mNumPackets == 9)
        return 52 * theIndex + 80;
    return 51 * theIndex + 79;
}

int Board::GetSeedBankExtraWidth()
{
    int mNumPackets; // eax

    // mNumPackets = this->mSeedBank->mNumPackets;
    if (mNumPackets <= 6)
        return 0;
    if (mNumPackets == 7)
        return 60;
    if (mNumPackets == 8)
        return 76;
    return mNumPackets != 9 ? 153 : 112;
}

int Board::PixelToGridX(int theX, int theY)
{
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN &&
        (mBackground == BACKGROUND_MUSHROOM_GARDEN || mBackground == BACKGROUND_ZOMBIQUARIUM ||
         mBackground == BACKGROUND_GREENHOUSE))
    {
        return mApp->mZenGarden->PixelToGridX(theX, theY);
    }

    if (theX < 40)
    {
        return -1;
    }

    if (((theX - 40) / 80) <= 0)
    {
        return 0;
    }
    if (((theX - 40) / 80) >= 8)
    {
        return 8;
    }

    return (theX - 40) / 80;
}

int Board::PixelToGridXKeepOnBoard(int theX, int theY)
{
    if (PixelToGridX(theX, theY) > 0)
    {
        return PixelToGridX(theX, theY);
    }
    return 0;
}

int Board::PixelToGridY(int theX, int theY)
{
    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN)
    {
        if (mBackground == BACKGROUND_MUSHROOM_GARDEN || mBackground == BACKGROUND_ZOMBIQUARIUM ||
            mBackground == BACKGROUND_GREENHOUSE)
        {
            return mApp->mZenGarden->PixelToGridY(theX, theY);
        }
    }

    int gridX = PixelToGridX(theX, theY);
    if (gridX == -1 || theY < 80)
        return -1;

    if (StageHasRoof())
    {
        int yOffset = (gridX < 5) ? 20 * (4 - gridX) : 0;
        int gridY = (theY - yOffset - 80) / 85;
        if (gridY <= 0)
            return 0;
        if (gridY >= 4)
            return 4;
        return gridY;
    }

    else if (mBackground == BACKGROUND_3_POOL || mBackground == BACKGROUND_4_FOG)
    {
        int gridY = (theY - 80) / 85;
        if (gridY <= 0)
            return 0;
        if (gridY >= 5)
            return 5;
        return gridY;
    }

    else
    {
        int gridY = (theY - 80) / 100;
        if (gridY <= 0)
            return 0;
        if (gridY >= 4)
            return 4;
        return gridY;
    }
}

int Board::PixelToGridYKeepOnBoard(int theX, int theY)
{
    if (theX <= 40)
    {
        theX = 40;
    }

    if (PixelToGridY(theX, theY) > 0)
    {
        return PixelToGridY(theX, theY);
    }

    return 0;
}

void Board::ShakeBoard(int theShakeAmountX, int theShakeAmountY)
{
    mShakeCounter = 12;
    mShakeAmountX = theShakeAmountX;
    mShakeAmountY = theShakeAmountY;
}

int Board::MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset)
{
    return theRow * 10000 + theRenderLayer + theLayerOffset;
}

unsigned int Board::SeedNotRecommendedForLevel(SeedType theSeedType)
{
    unsigned int flags = 0;

    if (Plant::IsNocturnal(theSeedType))
    {
        if (mBackground != BACKGROUND_2_NIGHT && mBackground != BACKGROUND_4_FOG && mBackground != BACKGROUND_6_BOSS &&
            mBackground != BACKGROUND_MUSHROOM_GARDEN && mBackground != BACKGROUND_ZOMBIQUARIUM)
        {
            flags |= 1;
        }
    }

    if (theSeedType == SEED_INSTANT_COFFEE &&
        (mBackground == BACKGROUND_2_NIGHT || mBackground == BACKGROUND_4_FOG || mBackground == BACKGROUND_6_BOSS ||
         mBackground == BACKGROUND_MUSHROOM_GARDEN || mBackground == BACKGROUND_ZOMBIQUARIUM))
    {
        flags |= 0x80u;
    }

    if (theSeedType == SEED_GRAVEBUSTER && !StageHasGraveStones())
    {
        flags |= 4u;
    }

    if (theSeedType == SEED_PLANTERN &&
        (mApp->IsStormyNightLevel() || mApp->mGameMode == GAMEMODE_CHALLENGE_INVISIGHOUL ||
         mBackground != BACKGROUND_4_FOG))
    {
        flags |= 8u;
    }

    if (theSeedType == SEED_FLOWERPOT && mBackground != BACKGROUND_5_ROOF && mBackground != BACKGROUND_6_BOSS)
    {
        flags |= 0x10u;
    }

    if ((mBackground == BACKGROUND_5_ROOF || mBackground == BACKGROUND_6_BOSS) &&
        (theSeedType == SEED_SPIKEWEED || theSeedType == SEED_SPIKEROCK))
    {
        flags |= 0x20u;
    }

    if (mBackground != BACKGROUND_3_POOL && mBackground != BACKGROUND_4_FOG &&
        (theSeedType == SEED_LILYPAD || theSeedType == SEED_TANGLEKELP || theSeedType == SEED_SEASHROOM ||
         theSeedType == SEED_CATTAIL))
    {
        flags |= 2u;
    }

    return flags;
}

bool Board::CanDropLoot()
{
    if (mApp->IsFirstTimeAdventureMode() && this->mLevel < 11)
    {
        return false;
    }

    return true;
}

bool Board::PlantUsesAcceleratedPricing(SeedType theSeedType)
{
    if (!Plant::IsUpgrade(theSeedType))
    {
        return false;
    }
    if (!mApp->IsSurvivalEndless(mApp->mGameMode))
    {
        return false;
    }
    return true;
}

void Board::InitZombieWavesForLevel(int aForLevel)
{
    if ((mApp->IsWhackAZombieLevel() || mApp->IsWallnutBowlingLevel()) && !mApp->IsFirstTimeAdventureMode())
    {
        mChallenge->InitZombieWaves();
    }
    else
    {
        for (int i = ZOMBIE_NORMAL; i < NUM_ZOMBIE_TYPES; i++)
        {
            this->mZombieAllowed[i] = Board::CanZombieSpawnOnLevel((ZombieType)i, aForLevel);
        }
    }
}

/*ZombieID Board::ZombieGetID(Zombie *theZombie)
{
    // return mZombies.DataArrayGetID(theZombie); // TODO: Implement DataArray
}*/