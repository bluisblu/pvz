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

    if (GetDialogCount() <= 0)
    {
        return true;
    }

    return false;
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

void LawnApp::KillAwardScreen()
{
    if (mAwardScreen)
    {
        mWidgetManager->RemoveWidget(mAwardScreen);
        SafeDeleteWidget(mAwardScreen);
        mAwardScreen = NULL;
    }
}

void LawnApp::KillSeedChooserScreen()
{
    if (mSeedChooserScreen)
    {
        mWidgetManager->RemoveWidget(mSeedChooserScreen);
        SafeDeleteWidget(mSeedChooserScreen);
        mSeedChooserScreen = NULL;
    }
}

void LawnApp::ShowResourceError(bool doExit)
{
    SexyAppBase::ShowResourceError(doExit);
}

void LawnApp::Start()
{
    if (mLoadingFailed)
    {
        return;
    }

    SexyAppBase::Start();
}

bool LawnApp::DebugKeyDown(int theKey)
{
    if (SexyAppBase::DebugKeyDown(theKey))
    {
        return true;
    }
    return false;
}

void LawnApp::PreDisplayHook()
{
    SexyApp::PreDisplayHook();
}

int LawnApp::GetCurrentChallengeIndex()
{
    return mGameMode - GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
}

bool LawnApp::IsAdventureMode()
{
    if (mGameMode == GAMEMODE_ADVENTURE)
        return true;

    return false;
}

bool LawnApp::IsSurvivalMode()
{
    if (mGameMode >= GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && mGameMode <= GAMEMODE_SURVIVAL_ENDLESS_STAGE_5)
        return true;

    return false;
}

bool LawnApp::IsPuzzleMode()
{
    if (mGameMode >= GAMEMODE_SCARY_POTTER_1 && mGameMode <= GAMEMODE_SCARY_POTTER_ENDLESS)
        return true;

    if (mGameMode >= GAMEMODE_PUZZLE_I_ZOMBIE_1 && mGameMode <= GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS)
        return true;

    return false;
}

bool LawnApp::IsChallengeMode()
{
    if (!IsAdventureMode() && !IsPuzzleMode() && !IsSurvivalMode())
        return true;

    return false;
}

bool LawnApp::IsArtChallenge()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_ART_CHALLENGE_1 || mGameMode == GAMEMODE_CHALLENGE_ART_CHALLENGE_2 ||
        mGameMode == GAMEMODE_CHALLENGE_SEEING_STARS)
        return true;

    return false;
}

bool LawnApp::IsSquirrelLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_SQUIRREL)
        return true;

    return false;
}

bool LawnApp::IsIZombieLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_1 || mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_2 ||
        mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_3 || mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_4 ||
        mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_5 || mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_6 ||
        mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_7 || mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_8 ||
        mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_9 || mGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS)
        return true;

    return false;
}

bool LawnApp::IsShovelLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_SHOVEL)
        return true;

    return false;
}

bool LawnApp::IsWallnutBowlingLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING || mGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 5)
        return true;

    return false;
}

bool LawnApp::IsSlotMachineLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_SLOT_MACHINE)
        return true;

    return false;
}

bool LawnApp::IsWhackAZombieLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 15)
        return true;

    return false;
}

bool LawnApp::IsLittleTroubleLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_LITTLE_TROUBLE)
        return true;

    if (mGameMode == GAMEMODE_ADVENTURE && mPlayerInfo->mLevel == 25)
        return true;

    return false;
}

bool LawnApp::IsScaryPotterLevel()
{
    if (mGameMode >= GAMEMODE_SCARY_POTTER_1 && mGameMode <= GAMEMODE_SCARY_POTTER_ENDLESS)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 35)
        return true;

    return false;
}

bool LawnApp::IsStormyNightLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_STORMY_NIGHT)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 40)
        return true;

    return false;
}

bool LawnApp::IsBungeeBlitzLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_BUNGEE_BLITZ)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 45)
        return true;

    return false;
}

bool LawnApp::IsMiniBossLevel()
{
    if (mBoard == NULL)
        return false;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 10)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 20)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 30)
        return true;

    return false;
}

bool LawnApp::IsFinalBossLevel()
{
    if (mBoard == NULL)
        return false;

    if (mGameMode == GAMEMODE_CHALLENGE_FINAL_BOSS)
        return true;

    if (IsAdventureMode() && mPlayerInfo->mLevel == 50)
        return true;

    return false;
}

bool LawnApp::IsChallengeWithoutSeedBank()
{
    if (mGameMode == GAMEMODE_CHALLENGE_RAINING_SEEDS)
        return true;

    if (IsWhackAZombieLevel() || IsSquirrelLevel() || IsScaryPotterLevel())
        return true;

    if (mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN || mGameMode == GAMEMODE_TREE_OF_WISDOM)
        return true;

    return false;
}

bool LawnApp::UpdateApp()
{
    if (mCloseRequest)
    {
        Shutdown();
        return false;
    }

    if (mLoadingThreadCompleted)
        SexyAppBase::PreDDInterfaceInitHook();

    bool updated = SexyAppBase::UpdateApp();

    if (mLoadingThreadCompleted && !mExitToTop)
        SexyAppBase::PreDDInterfaceInitHook();

    return updated;
}

SeedType LawnApp::GetAwardSeedForLevel(int theLevel)
{
    int aArea = (theLevel - 1) / 10 + 1; // Determine the "area" (group of 10 levels)
    int aSub = (theLevel - 1) % 10 + 1;  // Determine the "sub-level" within that area
    int aSeedsHasGot = (aArea - 1) * 8 + aSub;
    // Generally, each area gives 8 new seeds, each sub-level gives 1 seed

    if (aSub >= 10)
        aSeedsHasGot -= 2; // On the 10th sub-level, 2 rewards in this area are not new seeds

    else if (aSub >= 5)
        aSeedsHasGot -= 1; // On the 5th sub-level, 1 reward in this area is not a new seed

    if (aSeedsHasGot > 40)
        aSeedsHasGot = 40; // Maximum seed type is capped at 40

    return (SeedType)aSeedsHasGot;
}

bool LawnApp::IsNight()
{
    if (mPlayerInfo == NULL)
        return false;

    if (mPlayerInfo->mLevel >= 11 && mPlayerInfo->mLevel <= 20)
        return true;

    if (mPlayerInfo->mLevel >= 31 && mPlayerInfo->mLevel <= 40)
        return true;

    if (mPlayerInfo->mLevel == 50)
        return true;

    return false;
}

bool LawnApp::IsSurvivalNormal(GameMode theGameMode)
{
    int aLevel = theGameMode - GAMEMODE_SURVIVAL_NORMAL_STAGE_1;

    if (aLevel >= 0 && aLevel <= 4)
        return true;

    return false;
}

bool LawnApp::IsSurvivalHard(GameMode theGameMode)
{
    int aLevel = theGameMode - GAMEMODE_SURVIVAL_HARD_STAGE_1;

    if (aLevel >= 0 && aLevel <= 4)
        return true;

    return false;
}

bool LawnApp::IsSurvivalEndless(GameMode theGameMode)
{
    int aLevel = theGameMode - GAMEMODE_SURVIVAL_ENDLESS_STAGE_1;

    if (aLevel >= 0 && aLevel <= 4)
        return true;

    return false;
}

bool LawnApp::IsEndlessScaryPotter(GameMode theGameMode)
{
    if (theGameMode == GAMEMODE_SCARY_POTTER_ENDLESS)
        return true;

    return false;
}

bool LawnApp::IsEndlessIZombie(GameMode theGameMode)
{
    if (theGameMode == GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS)
        return true;

    return false;
}

bool LawnApp::HasFinishedAdventure()
{
    if (mPlayerInfo && mPlayerInfo->mFinishedAdventure > 0)
        return true;

    return false;
}

bool LawnApp::IsFirstTimeAdventureMode()
{
    if (IsAdventureMode() && !HasFinishedAdventure())
        return true;

    return false;
}

int LawnApp::TrophiesNeedForGoldSunflower()
{
    return (10 - GetNumTrophies(CHALLENGE_PAGE_SURVIVAL)) + (20 - GetNumTrophies(CHALLENGE_PAGE_CHALLENGE)) +
           (18 - GetNumTrophies(CHALLENGE_PAGE_PUZZLE));
}

void LawnApp::InitHook()
{
    mDRM = NULL;
}

void LawnApp::StartPlaying()
{
    KillSeedChooserScreen();
    mBoard->StartLevel();
    mGameScene = SCENE_PLAYING;
}

bool LawnApp::IsContinuousChallenge()
{
    if (IsArtChallenge() || IsSlotMachineLevel() || IsFinalBossLevel())
        return true;
    if (mGameMode == GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST)
        return true;
    return false;
}

int LawnApp::GetSeedsAvailable()
{
    int aLevel = mPlayerInfo->GetLevel();
    int maxPlants = 49;

    if (HasFinishedAdventure() || aLevel > 50)
    {
        if (mTodCheatKeys || mDebugKeysEnabled)
            maxPlants += NUM_SEEDS_IN_CHOOSER - SEED_IMITATER - 1;
        return maxPlants;
    }

    SeedType aSeedTypeMax = GetAwardSeedForLevel(aLevel);
    return min(maxPlants, aSeedTypeMax);
}

bool LawnApp::CanShowAlmanac()
{
    if (mPlayerInfo == NULL)
        return false;

    if (HasFinishedAdventure())
        return true;

    return mPlayerInfo->mLevel >= 15;
}

bool LawnApp::CanShowStore()
{
    if (mPlayerInfo == NULL)
        return false;

    if (HasFinishedAdventure())
        return true;

    return mPlayerInfo->mLevel >= 25;
}

bool LawnApp::CanShowZenGarden()
{
    if (mPlayerInfo == NULL)
        return false;

    if (HasFinishedAdventure())
        return true;

    return mPlayerInfo->mLevel >= 45;
}

void LawnApp::HandleCmdLineParam(const std::string &theParamName, const std::string &theParamValue)
{
    if (theParamName == "-tod")
    {
        mTodCheatKeys = true;
        mDebugKeysEnabled = true;
    }
    else
    {
        SexyApp::HandleCmdLineParam(theParamName, theParamValue);
    }
}

void LawnApp::CloseRequestAsync()
{
    mDeferredMessages.clear();
    mExitToTop = true;
    mCloseRequest = true;
}

SexyString LawnApp::GetMoneyString(int theAmount)
{
    int aValue = theAmount * 10;
    if (aValue > 999999)
    {
        return Sexy::StrFormat(_S("$%d,%03d,%03d"), aValue / 1000000, (aValue - aValue / 1000000 * 1000000) / 1000,
                               aValue - aValue / 1000 * 1000);
    }
    else if (aValue > 9999)
    {
        return Sexy::StrFormat(_S("$%d,%03d"), aValue / 1000, aValue - aValue / 1000 * 1000);
    }
    else
    {
        return Sexy::StrFormat(_S("$%d"), aValue);
    }
}

void LawnApp::ModalOpen()
{
    if (mBoard && NeedPauseGame())
    {
        mBoard->Pause(true);
    }
}

void LawnApp::KillBoard()
{
    KillSeedChooserScreen();
    if (mBoard)
    {
        BetaRecordLevelStats();
        mBoard->DisposeBoard();
        mWidgetManager->RemoveWidget(mBoard);
        SafeDeleteWidget(mBoard);
        mBoard = NULL;
    }

    SetCursor(Sexy::CURSOR_POINTER);
}

void LawnApp::MakeNewBoard()
{
    KillBoard();
    mBoard = new Board(this);
    mBoard->Resize(0, 0, mWidth, mHeight);

    mWidgetManager->AddWidget(mBoard);
    mWidgetManager->BringToBack(mBoard);
    mWidgetManager->SetFocus(mBoard);
}

void LawnApp::NewGame()
{
    mFirstTimeGameSelector = false;

    MakeNewBoard();
    // Not in 0.9.9:
    // if (!mBoard)
    //     return;
    mBoard->InitLevel();
    mBoardResult = BOARDRESULT_NONE;
    mGameScene = SCENE_LEVEL_INTRO;

    ShowSeedChooserScreen();
    mBoard->mCutScene->StartLevelIntro();
}

void LawnApp::EndLevel()
{
    KillBoard();
    if (IsAdventureMode())
    {
        NewGame();
    }

    mFirstTimeGameSelector = false; // true in Stable-Decompile

    MakeNewBoard();
    mBoard->InitLevel();
    mBoardResult = BOARDRESULT_NONE;
    mGameScene = SCENE_LEVEL_INTRO;
    ShowSeedChooserScreen();
    mBoard->mCutScene->StartLevelIntro();
}

void LawnApp::CrazyDaveTalkIndex(int theMessageIndex)
{
    mCrazyDaveMessageIndex = theMessageIndex;
    SexyString aMessageText = GetCrazyDaveText(theMessageIndex);
    CrazyDaveTalkMessage(aMessageText);
}

void LawnApp::LostFocus()
{
    if (!mTodCheatKeys && CanPauseNow() && !IsIZombieLevel())
    {
        DoPauseDialog();
    }
}

void LawnApp::ShowGameSelector()
{
    KillBoard();
    if (mGameSelector)
    {
        mWidgetManager->RemoveWidget(mGameSelector);
        SafeDeleteWidget(mGameSelector);
    }

    mGameScene = SCENE_MENU;
    mGameSelector = new GameSelector(this);
    mGameSelector->Resize(0, 0, mWidth, mHeight);
    mWidgetManager->AddWidget(mGameSelector);
    mWidgetManager->BringToBack(mGameSelector);
    mWidgetManager->SetFocus(mGameSelector);
}

void LawnApp::PreNewGame(GameMode theGameMode, bool theLookForSavedGame)
{
    // if (NeedRegister())
    //{
    //	ShowGameSelector();
    //	return;
    // }

    mGameMode = theGameMode;
    if (theLookForSavedGame && TryLoadGame())
        return;

    // SexyString aFileName = GetSavedGameName(mGameMode, mPlayerInfo->mId);
    // EraseFile(aFileName);
    NewGame();
}
