#ifndef __BOARD_H__
#define __BOARD_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/KeyCodes.h"
#include "SexyAppFramework/MTRand.h"

#include "Challenge.h"
#include "Coin.h"
#include "CursorObject.h"
#include "CutScene.h"
#include "DataArray.h"
#include "GridItem.h"
#include "LawnApp.h"
#include "Plant.h"
#include "Zombie.h"

class Challenge;
class Coin;
class CursorObject;
class CutScene;
class LawnApp;
class Plant;
class Zombie;
class GridItem;

enum ProjectileType : int
{
    PROJECTILE_PEA         = 0x0000,
    PROJECTILE_SNOWPEA     = 0x0001,
    PROJECTILE_CABBAGE     = 0x0002,
    PROJECTILE_MELON       = 0x0003,
    PROJECTILE_PUFF        = 0x0004,
    PROJECTILE_WINTERMELON = 0x0005,
    PROJECTILE_FIREBALL    = 0x0006,
    PROJECTILE_STAR        = 0x0007,
    PROJECTILE_SPIKE       = 0x0008,
    PROJECTILE_BASKETBALL  = 0x0009,
    PROJECTILE_KERNEL      = 0x000a,
    PROJECTILE_COBBIG      = 0x000b,
    PROJECTILE_BUTTER      = 0x000c,
    PROJECTILE_ZOMBIE_PEA  = 0x000d,
    NUM_PROJECTILES        = 0x000e,
};

enum DebugTextMode : int
{
    DEBUG_TEXT_NONE         = 0x0000,
    DEBUG_TEXT_ZOMBIE_SPAWN = 0x0001,
    DEBUG_TEXT_MUSIC        = 0x0002,
    DEBUG_TEXT_MEMORY       = 0x0003,
    DEBUG_TEXT_COLLISION    = 0x0004,
};

enum MessageStyle : int
{
    MESSAGE_STYLE_OFF                  = 0x0000,
    MESSAGE_STYLE_TUTORIAL_LEVEL1      = 0x0001,
    MESSAGE_STYLE_TUTORIAL_LEVEL1_STAY = 0x0002,
    MESSAGE_STYLE_TUTORIAL_LEVEL2      = 0x0003,
    MESSAGE_STYLE_TUTORIAL_LATER       = 0x0004,
    MESSAGE_STYLE_TUTORIAL_LATER_STAY  = 0x0005,
    MESSAGE_STYLE_HINT_LONG            = 0x0006,
    MESSAGE_STYLE_HINT_FAST            = 0x0007,
    MESSAGE_STYLE_HINT_STAY            = 0x0008,
    MESSAGE_STYLE_HINT_TALL_FAST       = 0x0009,
    MESSAGE_STYLE_HINT_TALL_10SECONDS  = 0x000a,
    MESSAGE_STYLE_HINT_TALL_8SECONDS   = 0x000b,
    MESSAGE_STYLE_HINT_TALL_LONG       = 0x000c,
    MESSAGE_STYLE_BIG_MIDDLE           = 0x000d,
    MESSAGE_STYLE_BIG_MIDDLE_FAST      = 0x000e,
    MESSAGE_STYLE_HOUSE_NAME           = 0x000f,
    MESSAGE_STYLE_HUGE_WAVE            = 0x0010,
    MESSAGE_STYLE_SLOT_MACHINE         = 0x0011,
    MESSAGE_STYLE_ZEN_GARDEN_LONG      = 0x0012,
};

enum BackgroundType : int
{
    BACKGROUND_1_DAY           = 0x0000,
    BACKGROUND_2_NIGHT         = 0x0001,
    BACKGROUND_3_POOL          = 0x0002,
    BACKGROUND_4_FOG           = 0x0003,
    BACKGROUND_5_ROOF          = 0x0004,
    BACKGROUND_6_BOSS          = 0x0005,
    BACKGROUND_MUSHROOM_GARDEN = 0x0006,
    BACKGROUND_GREENHOUSE      = 0x0007,
    BACKGROUND_ZOMBIQUARIUM    = 0x0008,
    BACKGROUND_TREE_OF_WISDOM  = 0x0009,
};

enum AdviceType : int
{
    ADVICE_NONE                          = 0xff,
    ADVICE_CLICK_ON_SUN                  = 0x0000,
    ADVICE_CLICKED_ON_SUN                = 0x0001,
    ADVICE_CLICKED_ON_COIN               = 0x0002,
    ADVICE_SEED_REFRESH                  = 0x0003,
    ADVICE_CANT_AFFORD_PLANT             = 0x0004,
    ADVICE_PLANT_GRAVEBUSTERS_ON_GRAVES  = 0x0005,
    ADVICE_PLANT_LILYPAD_ON_WATER        = 0x0006,
    ADVICE_PLANT_TANGLEKELP_ON_WATER     = 0x0007,
    ADVICE_PLANT_SEASHROOM_ON_WATER      = 0x0008,
    ADVICE_PLANT_POTATOE_MINE_ON_LILY    = 0x0009,
    ADVICE_PLANT_WRONG_ART_TYPE          = 0x000a,
    ADVICE_PLANT_NEED_POT                = 0x000b,
    ADVICE_PLANT_NOT_ON_GRAVE            = 0x000c,
    ADVICE_PLANT_NOT_ON_CRATER           = 0x000d,
    ADVICE_CANT_PLANT_THERE              = 0x000e,
    ADVICE_PLANT_NOT_ON_WATER            = 0x000f,
    ADVICE_PLANTING_NEEDS_GROUND         = 0x0010,
    ADVICE_BEGHOULED_DRAG_TO_MATCH_3     = 0x0011,
    ADVICE_BEGHOULED_MATCH_3             = 0x0012,
    ADVICE_BEGHOULED_MATCH_4             = 0x0013,
    ADVICE_BEGHOULED_SAVE_SUN            = 0x0014,
    ADVICE_BEGHOULED_USE_CRATER_1        = 0x0015,
    ADVICE_BEGHOULED_USE_CRATER_2        = 0x0016,
    ADVICE_PLANT_NOT_PASSED_LINE         = 0x0017,
    ADVICE_PLANT_ONLY_ON_REPEATERS       = 0x0018,
    ADVICE_PLANT_ONLY_ON_MELONPULT       = 0x0019,
    ADVICE_PLANT_ONLY_ON_SUNFLOWER       = 0x001a,
    ADVICE_PLANT_ONLY_ON_SPIKEWEED       = 0x001b,
    ADVICE_PLANT_ONLY_ON_KERNELPULT      = 0x001c,
    ADVICE_PLANT_ONLY_ON_MAGNETSHROOM    = 0x001d,
    ADVICE_PLANT_ONLY_ON_FUMESHROOM      = 0x001e,
    ADVICE_PLANT_ONLY_ON_LILYPAD         = 0x001f,
    ADVICE_PLANT_NEEDS_REPEATER          = 0x0020,
    ADVICE_PLANT_NEEDS_MELONPULT         = 0x0021,
    ADVICE_PLANT_NEEDS_SUNFLOWER         = 0x0022,
    ADVICE_PLANT_NEEDS_SPIKEWEED         = 0x0023,
    ADVICE_PLANT_NEEDS_KERNELPULT        = 0x0024,
    ADVICE_PLANT_NEEDS_MAGNETSHROOM      = 0x0025,
    ADVICE_PLANT_NEEDS_FUMESHROOM        = 0x0026,
    ADVICE_PLANT_NEEDS_LILYPAD           = 0x0027,
    ADVICE_SLOT_MACHINE_PULL             = 0x0028,
    ADVICE_HUGE_WAVE                     = 0x0029,
    ADVICE_SHOVEL_REFRESH                = 0x002a,
    ADVICE_PORTAL_RELOCATING             = 0x002b,
    ADVICE_SLOT_MACHINE_COLLECT_SUN      = 0x002c,
    ADVICE_DESTORY_POTS_TO_FINISIH_LEVEL = 0x002d,
    ADVICE_USE_SHOVEL_ON_POTS            = 0x002e,
    ADVICE_ALMOST_THERE                  = 0x002f,
    ADVICE_ZOMBIQUARIUM_CLICK_TROPHY     = 0x0030,
    ADVICE_ZOMBIQUARIUM_COLLECT_SUN      = 0x0031,
    ADVICE_ZOMBIQUARIUM_CLICK_TO_FEED    = 0x0032,
    ADVICE_ZOMBIQUARIUM_BUY_SNORKEL      = 0x0033,
    ADVICE_I_ZOMBIE_PLANTS_NOT_REAL      = 0x0034,
    ADVICE_I_ZOMBIE_NOT_PASSED_LINE      = 0x0035,
    ADVICE_I_ZOMBIE_LEFT_OF_LINE         = 0x0036,
    ADVICE_SLOT_MACHINE_SPIN_AGAIN       = 0x0037,
    ADVICE_I_ZOMBIE_EAT_ALL_BRAINS       = 0x0038,
    ADVICE_PEASHOOTER_DIED               = 0x0039,
    ADVICE_STINKY_SLEEPING               = 0x003a,
    ADVICE_BEGHOULED_NO_MOVES            = 0x003b,
    ADVICE_PLANT_SUNFLOWER5              = 0x003c,
    ADVICE_PLANTING_NEED_SLEEPING        = 0x003d,
    ADVICE_CLICK_TO_CONTINUE             = 0x003e,
    ADVICE_SURVIVE_FLAGS                 = 0x003f,
    ADVICE_UNLOCKED_MODE                 = 0x0040,
    NUM_ADVICE_TYPES                     = 0x0041,
};

enum RenderLayer : int
{
    RENDER_LAYER_UI_BOTTOM   = 0x000186a0,
    RENDER_LAYER_GROUND      = 0x00030d40,
    RENDER_LAYER_LAWN        = 0x000493e0,
    RENDER_LAYER_TOP         = 0x00061a80,
    RENDER_LAYER_FOG         = 0x0007a120,
    RENDER_LAYER_COIN_BANK   = 0x000927c0,
    RENDER_LAYER_UI_TOP      = 0x000aae60,
    RENDER_LAYER_ABOVE_UI    = 0x000c3500,
    RENDER_LAYER_SCREEN_FADE = 0x000dbba0,
    RENDER_LAYER_ROW_OFFSET  = 0x2710,
    RENDER_LAYER_GRAVE_STONE = 0x000497c8,
    RENDER_LAYER_PLANT       = 0x00049bb0,
    RENDER_LAYER_ZOMBIE      = 0x00049f98,
    RENDER_LAYER_PROJECTILE  = 0x0004a768,
    RENDER_LAYER_LAWN_MOWER  = 0x0004ab50,
    RENDER_LAYER_PARTICLE    = 0x0004af38,
};

class TodSmoothArray
{ /* Size=0x10 */
    /* 0x0000 */ int mItem;
    /* 0x0004 */ float mWeight;
    /* 0x0008 */ float mLastPicked;
    /* 0x000c */ float mSecondLastPicked;
};

enum TutorialState : int
{
    TUTORIAL_OFF                             = 0x0000,
    TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER      = 0x0001,
    TUTORIAL_LEVEL_1_PLANT_PEASHOOTER        = 0x0002,
    TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER      = 0x0003,
    TUTORIAL_LEVEL_1_COMPLETED               = 0x0004,
    TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER       = 0x0005,
    TUTORIAL_LEVEL_2_PLANT_SUNFLOWER         = 0x0006,
    TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER       = 0x0007,
    TUTORIAL_LEVEL_2_COMPLETED               = 0x0008,
    TUTORIAL_MORESUN_PICK_UP_SUNFLOWER       = 0x0009,
    TUTORIAL_MORESUN_PLANT_SUNFLOWER         = 0x000a,
    TUTORIAL_MORESUN_REFRESH_SUNFLOWER       = 0x000b,
    TUTORIAL_MORESUN_COMPLETED               = 0x000c,
    TUTORIAL_SLOT_MACHINE_PULL               = 0x000d,
    TUTORIAL_SLOT_MACHINE_COMPLETED          = 0x000e,
    TUTORIAL_SHOVEL_PICKUP                   = 0x000f,
    TUTORIAL_SHOVEL_DIG                      = 0x0010,
    TUTORIAL_SHOVEL_KEEP_DIGGING             = 0x0011,
    TUTORIAL_SHOVEL_COMPLETED                = 0x0012,
    TUTORIAL_ZOMBIQUARIUM_BUY_SNORKEL        = 0x0013,
    TUTORIAL_ZOMBIQUARIUM_BOUGHT_SNORKEL     = 0x0014,
    TUTORIAL_ZOMBIQUARIUM_CLICK_TROPHY       = 0x0015,
    TUTORIAL_ZEN_GARDEN_PICKUP_WATER         = 0x0016,
    TUTORIAL_ZEN_GARDEN_WATER_PLANT          = 0x0017,
    TUTORIAL_ZEN_GARDEN_KEEP_WATERING        = 0x0018,
    TUTORIAL_ZEN_GARDEN_VISIT_STORE          = 0x0019,
    TUTORIAL_ZEN_GARDEN_FERTILIZE_PLANTS     = 0x001a,
    TUTORIAL_ZEN_GARDEN_COMPLETED            = 0x001b,
    TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED = 0x001c,
    TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED        = 0x001d,
    TUTORIAL_WHACK_A_ZOMBIE_COMPLETED        = 0x001e,
};

class Board : /* 0x0000 */ public Sexy::Widget, /* 0x0088 */ public Sexy::ButtonListener
{ /* Size=0x57b0 */
  public:
    /* 0x008c */ LawnApp *mApp;
    /* 0x0090 */ DataArray<Zombie> mZombies;
    /* 0x00ac */ DataArray<Plant> mPlants;
    /* 0x00c8 */ // DataArray<Projectile> mProjectiles;
    char unk_c8[0x1c];
    /* 0x00e4 */ // DataArray<Coin> mCoins;
    char unk_e4[0x1c];
    /* 0x0100 */ // DataArray<LawnMower> mLawnMowers;
    char unk_100[0x1c];
    /* 0x011c */ // DataArray<GridItem> mGridItems;
    char unk_11c[0x1c];
    /* 0x0138 */ CursorObject *mCursorObject;
    /* 0x013c */ /* CursorPreview * */ void *mCursorPreview;
    /* 0x0140 */ /* MessageWidget * */ void *mAdvice;
    /* 0x0144 */ /* SeedBank * */ void *mSeedBank;
    /* 0x0148 */ /* GameButton * */ void *mMenuButton;
    /* 0x014c */ /* GameButton * */ void *mStoreButton;
    /* 0x0150 */ bool mIgnoreMouseUp;
    char pad_0x151[3];
    /* 0x0154 */ /* ToolTipWidget * */ void *mToolTip;
    /* 0x0158 */ Sexy::Font *mDebugFont;
    /* 0x015c */ CutScene *mCutScene;
    /* 0x0160 */ Challenge *mChallenge;
    /* 0x0164 */ bool mPaused;
    char pad_0x165[3];
    /* 0x0168 */ GridSquareType mGridSquareType[9][6];
    /* 0x0240 */ int mGridCelLook[9][6];
    /* 0x0318 */ int mGridCelOffset[9][6][2];
    /* 0x04c8 */ int mGridCelFog[9][7];
    /* 0x05c4 */ bool mEnableGraveStones;
    char pad_0x5c5[3];
    /* 0x05c8 */ int mSpecialGraveStoneX;
    /* 0x05cc */ int mSpecialGraveStoneY;
    /* 0x05d0 */ float mFogOffset;
    /* 0x05d4 */ int mFogBlownCountDown;
    /* 0x05d8 */ PlantRowType mPlantRow[6];
    /* 0x05f0 */ int mWaveRowGotLawnMowered[6];
    /* 0x0608 */ int mBonusLawnMowersRemaining;
    /* 0x060c */ int mIceMinX[6];
    /* 0x0624 */ int mIceTimer[6];
    /* 0x063c */ ParticleSystemID mIceParticleID[6];
    /* 0x0654 */ TodSmoothArray mRowPickingArray[6];
    /* 0x06b4 */ ZombieType mZombiesInWave[100][50];
    /* 0x54d4 */ bool mZombieAllowed[100];
    /* 0x5538 */ int mSunCountDown;
    /* 0x553c */ int mNumSunsFallen;
    /* 0x5540 */ int mShakeCounter;
    /* 0x5544 */ int mShakeAmountX;
    /* 0x5548 */ int mShakeAmountY;
    /* 0x554c */ BackgroundType mBackground;
    /* 0x5550 */ int mLevel;
    /* 0x5554 */ int mSodPosition;
    /* 0x5558 */ int mPrevMouseX;
    /* 0x555c */ int mPrevMouseY;
    /* 0x5560 */ int mSunMoney;
    /* 0x5564 */ int mNumWaves;
    /* 0x5568 */ int mMainCounter;
    /* 0x556c */ int mEffectCounter;
    /* 0x5570 */ int mDrawCount;
    /* 0x5574 */ int mRiseFromGraveCounter;
    /* 0x5578 */ int mOutOfMoneyCounter;
    /* 0x557c */ int mCurrentWave;
    /* 0x5580 */ int mTotalSpawnedWaves;
    /* 0x5584 */ TutorialState mTutorialState;
    /* 0x5588 */ ParticleSystemID mTutorialParticleID;
    /* 0x558c */ int mTutorialTimer;
    /* 0x5590 */ int mLastBungeeWave;
    /* 0x5594 */ int mZombieHealthToNextWave;
    /* 0x5598 */ int mZombieHealthWaveStart;
    /* 0x559c */ int mZombieCountDown;
    /* 0x55a0 */ int mZombieCountDownStart;
    /* 0x55a4 */ int mHugeWaveCountDown;
    /* 0x55a8 */ bool mHelpDisplayed[65];
    char pad_0x55e9[3];
    /* 0x55ec */ AdviceType mHelpIndex;
    /* 0x55f0 */ bool mFinalBossKilled;
    /* 0x55f1 */ bool mShowShovel;
    char pad_0x55f2[2];
    /* 0x55f4 */ int mCoinBankFadeCount;
    /* 0x55f8 */ DebugTextMode mDebugTextMode;
    /* 0x55fc */ bool mLevelComplete;
    char pad_0x55fd[3];
    /* 0x5600 */ int mBoardFadeOutCounter;
    /* 0x5604 */ int mNextSurvivalStageCounter;
    /* 0x5608 */ int mScoreNextMowerCounter;
    /* 0x560c */ bool mLevelAwardSpawned;
    char pad_0x560d[3];
    /* 0x5610 */ int mProgressMeterWidth;
    /* 0x5614 */ int mFlagRaiseCounter;
    /* 0x5618 */ int mIceTrapCounter;
    /* 0x561c */ int mBoardRandSeed;
    /* 0x5620 */ ParticleSystemID mPoolSparklyParticleID;
    /* 0x5624 */ ReanimationID mFwooshID[6][12];
    /* 0x5744 */ int mFwooshCountDown;
    /* 0x5748 */ int mTimeStopCounter;
    /* 0x574c */ bool mDroppedFirstCoin;
    char pad_0x574d[3];
    /* 0x5750 */ int mFinalWaveSoundCounter;
    /* 0x5754 */ int mCobCannonCursorDelayCounter;
    /* 0x5758 */ int mCobCannonMouseX;
    /* 0x575c */ int mCobCannonMouseY;
    /* 0x5760 */ bool mKilledYeti;
    /* 0x5761 */ bool mMustacheMode;
    /* 0x5762 */ bool mSuperMowerMode;
    /* 0x5763 */ bool mFutureMode;
    /* 0x5764 */ bool mPinataMode;
    /* 0x5765 */ bool mDaisyMode;
    /* 0x5766 */ bool mSukhbirMode;
    char pad_0x5767;
    /* 0x5768 */ BoardResult mPrevBoardResult;
    /* 0x576c */ int mTriggeredLawnMowers;
    /* 0x5770 */ int mPlayTimeActiveLevel;
    /* 0x5774 */ int mPlayTimeInactiveLevel;
    /* 0x5778 */ int mMaxSunPlants;
    /* 0x577c */ int mStartDrawTime;
    /* 0x5780 */ int mIntervalDrawTime;
    /* 0x5784 */ int mIntervalDrawCountStart;
    /* 0x5788 */ float mMinFPS;
    /* 0x578c */ int mPreloadTime;
    /* 0x5790 */ int mGameID;
    /* 0x5794 */ int mGravesCleared;
    /* 0x5798 */ int mPlantsEaten;
    /* 0x579c */ int mPlantsShoveled;
    /* 0x57a0 */ int mCoinsCollected;
    /* 0x57a4 */ int mDiamondsCollected;
    /* 0x57a8 */ int mPottedPlantsCollected;
    /* 0x57ac */ int mChocolateCollected;

  public:
    Board(const Board &);
    Board(LawnApp *);
    virtual ~Board();
    void DisposeBoard();
    int CountSunBeingCollected();
    void DrawGameObjects(/* Sexy::Graphics * */ void *);
    void ClearCursor();
    bool AreEnemyZombiesOnScreen();
    /* LawnMower * */ void *FindLawnMowerInRow(int);
    bool SyncState(/* DataSync & */ void *);
    void SaveGame(const std::string &);
    bool LoadGame(const std::string &);
    void InitLevel();
    void DisplayAdvice(const std::string &, MessageStyle, AdviceType);
    void StartLevel();
    Plant *AddPlant(int, int, SeedType, SeedType);
    /* Projectile * */ void *AddProjectile(int, int, int, int, ProjectileType);
    Coin *AddCoin(int, int, CoinType, CoinMotion);
    void RefreshSeedPacketFromCursor();
    ZombieType PickGraveRisingZombieType(int);
    ZombieType PickZombieType(int, int, /* ZombiePicker * */ void *);
    int PickRowForNewZombie(ZombieType);
    Zombie *AddZombie(ZombieType, int);
    void SpawnZombieWave();
    void RemoveAllZombies();
    void RemoveCutsceneZombies();
    void SpawnZombiesFromGraves();
    PlantingReason CanPlantAt(int, int, SeedType);
    virtual void MouseMove(int, int);
    virtual void MouseDrag(int, int);
    virtual void MouseDown(int, int, int);
    virtual void MouseUp(int, int, int);
    virtual void KeyChar(char);
    virtual void KeyUp(Sexy::KeyCode);
    virtual void KeyDown(Sexy::KeyCode);
    virtual void Update();
    void UpdateLayers();
    virtual void Draw(Sexy::Graphics *);
    void DrawBackdrop(Sexy::Graphics *);
    virtual void ButtonMouseEnter(int);
    virtual void ButtonMouseLeave(int);
    virtual void ButtonPress(int);
    void AddSunMoney(int);
    bool TakeSunMoney(int);
    bool CanTakeSunMoney(int);
    void Pause(bool);
    void MakeEasyZombieType();
    void TryToSaveGame();
    bool NeedSaveGame();
    bool RowCanHaveZombies(int);
    void ProcessDeleteQueue();
    bool ChooseSeedsOnCurrentLevel();
    int GetNumSeedsInBank();
    bool StageIsNight();
    bool StageHasPool();
    bool StageHas6Rows();
    bool StageHasFog();
    bool StageHasGraveStones();
    int PixelToGridX(int, int);
    int PixelToGridY(int, int);
    int GridToPixelX(int, int);
    int GridToPixelY(int, int);
    int PixelToGridXKeepOnBoard(int, int);
    int PixelToGridYKeepOnBoard(int, int);
    void UpdateGameObjects();
    bool MouseHitTest(int, int, HitResult *);
    void MouseDownWithPlant(int, int, int);
    void MouseDownWithTool(int, int, int, CursorType);
    void MouseDownNormal(int, int, int);
    bool CanInteractWithBoardButtons();
    void DrawProgressMeter(Sexy::Graphics *);
    void UpdateToolTip();
    Plant *GetTopPlantAt(int, int, PlantPriority);
    void GetPlantsOnLawn(int, int, /* PlantsOnLawn * */ void *);
    int CountSunFlowers();
    int GetSeedPacketPositionX(int);
    void AddGraveStones(int, int, Sexy::MTRand &);
    int GetGraveStoneCount();
    void ZombiesWon(Zombie *);
    void DrawLevel(Sexy::Graphics *);
    void DrawShovel(Sexy::Graphics *);
    void UpdateZombieSpawning();
    void UpdateSunSpawning();
    void ClearAdvice(AdviceType);
    bool RowCanHaveZombieType(int, ZombieType);
    int NumberZombiesInWave(int);
    int TotalZombiesHealthInWave(int);
    void DrawDebugText(Sexy::Graphics *);
    void DrawUICoinBank(Sexy::Graphics *);
    void ShowCoinBank();
    void FadeOutLevel();
    void DrawFadeOut(Sexy::Graphics *);
    void DrawIce(Sexy::Graphics *, int);
    bool IsIceAt(int, int);
    ZombieID ZombieGetID(Zombie *);
    Zombie *ZombieGet(ZombieID);
    Zombie *ZombieTryToGet(ZombieID);
    void DrawDebugObjectRects(Sexy::Graphics *);
    void UpdateIce();
    int GetIceZPos(int);
    bool CanAddBobSled();
    void ShakeBoard(int, int);
    int CountUntriggerLawnMowers();
    bool IterateZombies(Zombie *&);
    bool IteratePlants(Plant *&);
    bool IterateProjectiles(/* Projectile *& */ void *);
    bool IterateCoins(/* Coin *& */ void *);
    bool IterateLawnMowers(/* LawnMower *& */ void *);
    bool IterateParticles(/* TodParticleSystem *& */ void *);
    bool IterateReanimations(/* Reanimation *& */ void *);
    bool IterateGridItems(GridItem *&);
    Zombie *AddZombieInRow(ZombieType, int, int);
    bool IsPoolSquare(int, int);
    void PickZombieWaves();
    void StopAllZombieSounds();
    bool HasLevelAwardDropped();
    void UpdateProgressMeter();
    void DrawUIBottom(Sexy::Graphics *);
    void DrawUITop(Sexy::Graphics *);
    Zombie *ZombieHitTest(int, int);
    void KillAllPlantsInRadius(int, int, int);
    Plant *GetPumpkinAt(int, int);
    Plant *GetFlowerPotAt(int, int);
    bool IsZombieWaveDistributionOk();
    void PickBackground();
    void InitZombieWaves();
    void InitSurvivalStage();
    void UpdateGame();
    void InitZombieWavesForLevel(int);
    unsigned int SeedNotRecommendedForLevel(SeedType);
    void DrawTopRightUI(Sexy::Graphics *);
    void DrawFog(Sexy::Graphics *);
    void UpdateFog();
    int LeftFogColumn();
    void DropLootPiece(int, int, int);
    void UpdateLevelEndSequence();
    /* LawnMower * */ int GetBottomLawnMower();
    bool CanDropLoot();
    ZombieType GetIntroducedZombieType();
    void PickSpecialGraveStone();
    float GetPosYBasedOnRow(float, int);
    void NextWaveComing();
    bool BungeeIsTargetingCell(int, int);
    int PlantingPixelToGridX(int, int, SeedType);
    int PlantingPixelToGridY(int, int, SeedType);
    Plant *FindUmbrellaPlant(int, int);
    void SetTutorialState(TutorialState);
    void DoFwoosh(int);
    void UpdateFwoosh();
    Plant *SpecialPlantHitTest(int, int);
    void UpdateMousePosition();
    Plant *ToolHitTest(int, int);
    bool CanAddGraveStoneAt(int, int);
    void UpdateGridItems();
    GridItem *AddAGraveStone(int, int);
    int GetSurvivalFlagsCompleted();
    bool HasProgressMeter();
    void UpdateCursor();
    void UpdateTutorial();
    SeedType GetSeedTypeInCursor();
    int CountPlantByType(SeedType);
    bool PlantingRequirementsMet(SeedType);
    bool HasValidCobCannonSpot();
    bool IsValidCobCannonSpot(int, int);
    bool IsValidCobCannonSpotHelper(int, int);
    void MouseDownCobcannonFire(int, int, int);
    void KillAllZombiesInRadius(int, int, int, int, int, bool, int);
    int GetSeedBankExtraWidth();
    bool IsFlagWave(int);
    void DrawHouseDoorTop(Sexy::Graphics *);
    void DrawHouseDoorBottom(Sexy::Graphics *);
    Zombie *GetBossZombie();
    bool HasConveyorBeltSeedBank();
    bool StageHasRoof();
    void SpawnZombiesFromPool();
    void SpawnZombiesFromSky();
    void PickUpTool(GameObjectType);
    void TutorialArrowShow(int, int);
    void TutorialArrowRemove();
    int CountCoinsBeingCollected();
    void BungeeDropZombie(/* BungeeDropGrid * */ void *, ZombieType);
    void SetupBungeeDrop(/* BungeeDropGrid * */ void *);
    void PutZombieInWave(ZombieType, int, /* ZombiePicker * */ void *);
    void PutInMissingZombies(int, /* ZombiePicker * */ void *);
    Sexy::TRect<int> GetShovelButtonRect();
    Sexy::TRect<int> GetZenButtonRect(GameObjectType);
    Plant *NewPlant(int, int, SeedType, SeedType);
    void DoPlantingEffects(int, int, Plant *);
    bool IsFinalSurvivalStage();
    void SurvivalSaveScore();
    int CountZombiesOnScreen();
    int GetNumWavesPerSurvivalStage();
    int GetLevelRandSeed();
    void AddBossRenderItem(/* RenderItem * */ void *, int &, Zombie *);
    GridItem *GetCraterAt(int, int);
    GridItem *GetGraveStoneAt(int, int);
    GridItem *GetLadderAt(int, int);
    GridItem *AddALadder(int, int);
    GridItem *AddACrater(int, int);
    void InitLawnMowers();
    bool IsPlantInCursor();
    void HighlightPlantsForMouse(int, int);
    void ClearFogAroundPlant(Plant *, int);
    void RemoveParticleByType(ParticleEffect);
    GridItem *GetScaryPotAt(int, int);
    void PuzzleSaveStreak();
    void ClearAdviceImmediately();
    bool IsFinalScaryPotterStage();
    void DisplayAdviceAgain(const std::string &, MessageStyle, AdviceType);
    GridItem *GetSquirrelAt(int, int);
    GridItem *GetZenToolAt(int, int);
    bool IsPlantInGoldWateringCanRange(int, int, Plant *);
    bool StageHasZombieWalkInFromRight();
    void PlaceRake();
    GridItem *GetRake();
    bool IsScaryPotterDaveTalking();
    Zombie *GetWinningZombie();
    void ResetFPSStats();
    int CountEmptyPotsOrLilies(SeedType);
    GridItem *GetGridItemAt(GridItemType, int, int);
    bool ProgressMeterHasFlags();
    bool IsLastStandFinalStage();
    int GetNumWavesPerFlag();
    int GetCurrentPlantCost(SeedType, SeedType);
    bool PlantUsesAcceleratedPricing(SeedType);
    void FreezeEffectsForCutscene(bool);
    void LoadBackgroundImages();
    bool CanUseGameObject(GameObjectType);
    void SetMustacheMode(bool);
    int CountCoinByType(CoinType);
    void SetSuperMowerMode(bool);
    void DrawZenWheelBarrowButton(Sexy::Graphics *, int);
    void DrawZenButtons(Sexy::Graphics *);
    void OffsetYForPlanting(int &, SeedType);
    void SetFutureMode(bool);
    void SetPinataMode(bool);
    void SetDaisyMode(bool);
    void SetSukhbirMode(bool);
    bool MouseHitTestPlant(int, int, /* HitResult * */ void *);
    Board &operator=(const Board &);
    // virtual void *__vecDelDtor(unsigned int);
    static bool CanZombieSpawnOnLevel(ZombieType, int);
    static int MakeRenderOrder(RenderLayer, int, int);
    static bool IsZombieTypePoolOnly(ZombieType);
};

#endif // __BOARD_H__
