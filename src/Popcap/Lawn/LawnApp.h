#ifndef __LAWNAPP_H__
#define __LAWNAPP_H__

#include "SexyAppFramework/SexyApp.h"

#include "TodLib/Reanimator.h"
#include "TodLib/TodStringFile.h"

#include "AwardScreen.h"
#include "Board.h"
#include "GameSelector.h"
#include "PlayerInfo.h"
#include "SeedChooserScreen.h"
#include "ZenGarden.h"

class AwardScreen;
class Board;
class GameSelector;
class SeedChooserScreen;

extern TodStringListFormat gLawnStringFormats[12];

class LawnApp : public Sexy::SexyApp
{ /* Size=0x8c0 */
  public:
    /* 0x0000: fields for Sexy::SexyApp */
    // char unk_0[8];
    /* 0x0768 */ Board *mBoard;
    /* 0x076c */ /* TitleScreen * */ void *mTitleScreen;
    /* 0x0770 */ GameSelector *mGameSelector;
    /* 0x0774 */ SeedChooserScreen *mSeedChooserScreen;
    /* 0x0778 */ AwardScreen *mAwardScreen;
    /* 0x077c */ /* CreditScreen * */ void *mCreditScreen;
    /* 0x0780 */ /* ChallengeScreen * */ void *mChallengeScreen;
    /* 0x0784 */ /* TodFoley * */ void *mSoundSystem;
    /* 0x0788 */ // std::list<Sexy::ButtonWidget *, std::allocator<Sexy::ButtonWidget *>>
                 // mControlButtonList;
    char unk_788[0xc];
    /* 0x0794 */ // std::list<Sexy::Image *, std::allocator<Sexy::Image *>> mCreatedImageList;
    char unk_794[0xc];
    /* 0x07a0 */ std::string mReferId;
    /* 0x07bc */ std::string mRegisterLink;
    /* 0x07d8 */ std::string mMod;
    /* 0x07f4 */ bool mRegisterResourcesLoaded;
    /* 0x07f5 */ bool mTodCheatKeys;
    char pad_0x7f6[2];
    /* 0x07f8 */ GameMode mGameMode;
    /* 0x07fc */ GameScenes mGameScene;
    /* 0x0800 */ bool mLoadingZombiesThreadCompleted;
    /* 0x0801 */ bool mFirstTimeGameSelector;
    char pad_0x802[2];
    /* 0x0804 */ int mGamesPlayed;
    /* 0x0808 */ int mMaxExecutions;
    /* 0x080c */ int mMaxPlays;
    /* 0x0810 */ int mMaxTime;
    /* 0x0814 */ bool mEasyPlantingCheat;
    char pad_0x815[3];
    /* 0x0818 */ /* PoolEffect * */ void *mPoolEffect;
    /* 0x081c */ ZenGarden *mZenGarden;
    /* 0x0820 */ /* EffectSystem * */ void *mEffectSystem;
    /* 0x0824 */ /* ReanimatorCache * */ void *mReanimatorCache;
    /* 0x0828 */ /* ProfileMgr * */ void *mProfileMgr;
    /* 0x082c */ PlayerInfo *mPlayerInfo;
    /* 0x0830 */ /* LevelStats * */ void *mLastLevelStats;
    /* 0x0834 */ bool mCloseRequest;
    char pad_0x835[3];
    /* 0x0838 */ int mAppCounter;
    /* 0x083c */ /* Music * */ void *mMusic;
    /* 0x0840 */ ReanimationID mCrazyDaveReanimID;
    /* 0x0844 */ CrazyDaveState mCrazyDaveState;
    /* 0x0848 */ int mCrazyDaveBlinkCounter;
    /* 0x084c */ ReanimationID mCrazyDaveBlinkReanimID;
    /* 0x0850 */ int mCrazyDaveMessageIndex;
    /* 0x0854 */ std::string mCrazyDaveMessageText;
    /* 0x0870 */ int mAppRandSeed;
    /* 0x0874 */ /* HICON__ * */ void *mBigArrowCursor;
    /* 0x0878 */ /* PopDRMComm * */ void *mDRM;
    /* 0x087c */ int mSessionID;
    /* 0x0880 */ int mPlayTimeActiveSession;
    /* 0x0884 */ int mPlayTimeInactiveSession;
    /* 0x0888 */ BoardResult mBoardResult;
    /* 0x088c */ bool mKilledYetiAndRestarted;
    char pad_0x88d[3];
    /* 0x0890 */ /* TypingCheck * */ int mKonamiCheck;
    /* 0x0894 */ /* TypingCheck * */ int mMustacheCheck;
    /* 0x0898 */ /* TypingCheck * */ int mMoustacheCheck;
    /* 0x089c */ /* TypingCheck * */ int mSuperMowerCheck;
    /* 0x08a0 */ /* TypingCheck * */ int mSuperMowerCheck2;
    /* 0x08a4 */ /* TypingCheck * */ int mFutureCheck;
    /* 0x08a8 */ /* TypingCheck * */ int mPinataCheck;
    /* 0x08ac */ /* TypingCheck * */ int mDaisyCheck;
    /* 0x08b0 */ /* TypingCheck * */ int mSukhbirCheck;
    /* 0x08b4 */ bool mMustacheMode;
    /* 0x08b5 */ bool mSuperMowerMode;
    /* 0x08b6 */ bool mFutureMode;
    /* 0x08b7 */ bool mPinataMode;
    /* 0x08b8 */ bool mDaisyMode;
    /* 0x08b9 */ bool mSukhbirMode;
    char pad_0x8ba[6];

  public:
    LawnApp(const LawnApp &);
    LawnApp();
    virtual ~LawnApp();
    bool KillNewOptionsDialog();
    virtual void GotFocus();
    virtual void LostFocus();
    virtual void InitHook();
    virtual void WriteToRegistry();
    virtual void ReadFromRegistry();
    virtual void LoadingThreadProc();
    virtual void LoadingCompleted();
    virtual void LoadingThreadCompleted();
    virtual void URLOpenFailed(const std::string &);
    virtual void URLOpenSucceeded(const std::string &);
    virtual bool OpenURL(const std::string &, bool);
    virtual bool DebugKeyDown(int);
    virtual void HandleCmdLineParam(const std::string &, const std::string &);
    void ConfirmQuit();
    void ConfirmCheckForUpdates();
    void CheckForUpdates();
    void DoUserDialog();
    void FinishUserDialog(bool);
    void DoCreateUserDialog();
    void DoCheatDialog();
    void FinishCheatDialog(bool);
    void FinishCreateUserDialog(bool);
    void DoConfirmDeleteUserDialog(const std::string &);
    void FinishConfirmDeleteUserDialog(bool);
    void DoRenameUserDialog(const std::string &);
    void FinishRenameUserDialog(bool);
    void FinishNameError(int);
    void FinishRestartConfirmDialog();
    void DoConfirmSellDialog(const std::string &);
    void DoConfirmPurchaseDialog(const std::string &);
    void FinishTimesUpDialog();
    void KillBoard();
    void MakeNewBoard();
    void StartPlaying();
    bool TryLoadGame();
    void NewGame();
    void PreNewGame(GameMode, bool);
    void ShowGameSelector();
    void KillGameSelector();
    void ShowAwardScreen(AwardType);
    void KillAwardScreen();
    void ShowSeedChooserScreen();
    void KillSeedChooserScreen();
    void DoHighScoreDialog();
    void DoBackToMain();
    void DoConfirmBackToMain();
    void DoNewOptions(bool);
    void DoRegister();
    void DoRegisterError();
    bool CanDoRegisterDialog();
    bool WriteCurrentUserConfig();
    void DoNeedRegisterDialog();
    void DoContinueDialog();
    void DoPauseDialog();
    void FinishModelessDialogs();
    virtual Sexy::Dialog *DoDialog(int, bool, const std::string &, const std::string &,
                                   const std::string &, int);
    Sexy::Dialog *DoDialogDelay(int, bool, const std::string &, const std::string &,
                                const std::string &, int);
    virtual void Shutdown();
    virtual void Init();
    virtual void Start();
    virtual Sexy::Dialog *NewDialog(int, bool, const std::string &, const std::string &,
                                    const std::string &, int);
    virtual bool KillDialog(int);
    virtual void ModalOpen();
    virtual void ModalClose();
    virtual void PreDisplayHook();
    virtual bool ChangeDirHook(const char *);
    bool NeedRegister();
    void UpdateRegisterInfo();
    virtual void ButtonPress(int);
    virtual void ButtonDepress(int);
    virtual void UpdateFrames();
    virtual bool UpdateApp();
    bool IsAdventureMode();
    bool IsSurvivalMode();
    bool IsContinuousChallenge();
    bool IsArtChallenge();
    bool NeedPauseGame();
    virtual void ShowResourceError(bool);
    void ToggleSlowMo();
    void ToggleFastMo();
    void PlayFoley(FoleyType);
    void FastLoad(GameMode);
    std::string GetStageString(int);
    void KillChallengeScreen();
    void ShowChallengeScreen(ChallengePage);
    const /* ChallengeDefinition & */ void *GetCurrentChallengeDef();
    void CheckForGameEnd();
    virtual void CloseRequestAsync();
    bool IsChallengeWithoutSeedBank();
    /* AlmanacDialog * */ void *DoAlmanacDialog(SeedType, ZombieType);
    bool KillAlmanacDialog();
    int GetSeedsAvailable();
    Reanimation *AddReanimation(float, float, int, ReanimationType);
    /* TodParticleSystem * */ void *AddTodParticle(float, float, int, ParticleEffect);
    /* ParticleSystemID */ void *ParticleGetID(/* TodParticleSystem * */ void *);
    /* TodParticleSystem * */ void *ParticleGet(/* ParticleSystemID */ void *);
    /* TodParticleSystem * */ void *ParticleTryToGet(/* ParticleSystemID */ void *);
    ReanimationID ReanimationGetID(Reanimation *);
    Reanimation *ReanimationGet(ReanimationID);
    Reanimation *ReanimationTryToGet(ReanimationID);
    void RemoveReanimation(ReanimationID);
    void RemoveParticle(ParticleSystemID);
    /* StoreScreen * */ void *ShowStoreScreen();
    void KillStoreScreen();
    bool HasSeedType(SeedType);
    void EndLevel();
    bool IsIceDemo();
    bool IsShovelLevel();
    bool IsWallnutBowlingLevel();
    bool IsMiniBossLevel();
    bool IsSlotMachineLevel();
    bool IsLittleTroubleLevel();
    bool IsStormyNightLevel();
    bool IsFinalBossLevel();
    bool IsBungeeBlitzLevel();
    SeedType GetAwardSeedForLevel(int);
    std::string GetCrazyDaveText(int);
    bool CanShowAlmanac();
    bool IsNight();
    bool CanShowStore();
    bool HasBeatenChallenge(GameMode);
    PottedPlant *GetPottedPlantByIndex(int);
    bool IsSurvivalNormal(GameMode);
    bool IsSurvivalHard(GameMode);
    bool IsSurvivalEndless(GameMode);
    bool HasFinishedAdventure();
    bool IsFirstTimeAdventureMode();
    bool CanSpawnYetis();
    void CrazyDaveEnter();
    void UpdateCrazyDave();
    void CrazyDaveTalkIndex(int);
    void CrazyDaveTalkMessage(const std::string &);
    void CrazyDaveLeave();
    void DrawCrazyDave(/* Sexy::Graphics * */ void *);
    void CrazyDaveDie();
    void CrazyDaveStopTalking();
    void PreloadForUser();
    int GetNumPreloadingTasks();
    int LawnMessageBox(int, const char *, const char *, const char *, const char *, int);
    virtual void EnforceCursor();
    void ShowCreditScreen();
    void KillCreditScreen();
    std::string Pluralize(int, const char *, const char *);
    int GetNumTrophies(ChallengePage);
    bool EarnedGoldTrophy();
    bool IsRegistered();
    bool IsExpired();
    bool IsDRMConnected();
    bool IsScaryPotterLevel();
    bool IsEndlessScaryPotter(GameMode);
    bool IsSquirrelLevel();
    bool IsIZombieLevel();
    bool CanShowZenGarden();
    std::string GetMoneyString(int);
    bool AdvanceCrazyDaveText();
    bool IsWhackAZombieLevel();
    void BetaSubmit(bool);
    void BetaRecordLevelStats();
    void UpdatePlayTimeStats();
    void BetaAddFile(std::list<std::string, std::allocator<std::string>> &, std::string,
                     std::string);
    bool CanPauseNow();
    bool IsPuzzleMode();
    bool IsChallengeMode();
    bool IsEndlessIZombie(GameMode);
    void CrazyDaveDoneHanding();
    std::string GetCurrentLevelName();
    int TrophiesNeedForGoldSunflower();
    int GetCurrentChallengeIndex();
    void LoadGroup(const char *, const int);
    void TraceLoadGroup(const char *, int, int, int);
    void CrazyDaveStopSound();
    LawnApp &operator=(const LawnApp &);
};

LawnApp *gLawnApp;

#endif // __LAWNAPP_H__
