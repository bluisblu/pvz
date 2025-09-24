#pragma once

#ifndef __CHALLENGE_H__
#define __CHALLENGE_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/Graphics.h"

#include "Board.h"
#include "LawnApp.h"
#include "Plant.h"
#include "Zombie.h"

class Board;
class LawnApp;
class Plant;
class Zombie;

#ifndef E_GRID_ITEM_STATE
#define E_GRID_ITEM_STATE
enum GridItemState : int
{
    GRIDITEM_STATE_NORMAL = 0x0000,
    GRIDITEM_STATE_GRAVESTONE_SPECIAL = 0x0001,
    GRIDITEM_STATE_PORTAL_CLOSED = 0x0002,
    GRIDITEM_STATE_SCARY_POT_QUESTION = 0x0003,
    GRIDITEM_STATE_SCARY_POT_LEAF = 0x0004,
    GRIDITEM_STATE_SCARY_POT_ZOMBIE = 0x0005,
    GRIDITEM_STATE_SQUIRREL_WAITING = 0x0006,
    GRIDITEM_STATE_SQUIRREL_PEEKING = 0x0007,
    GRIDITEM_STATE_SQUIRREL_RUNNING_UP = 0x0008,
    GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN = 0x0009,
    GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT = 0x000a,
    GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT = 0x000b,
    GRIDITEM_STATE_SQUIRREL_CAUGHT = 0x000c,
    GRIDITEM_STATE_SQUIRREL_ZOMBIE = 0x000d,
    GRIDITEM_STATE_ZEN_TOOL_WATERING_CAN = 0x000e,
    GRIDITEM_STATE_ZEN_TOOL_FERTILIZER = 0x000f,
    GRIDITEM_STATE_ZEN_TOOL_BUG_SPRAY = 0x0010,
    GRIDITEM_STATE_ZEN_TOOL_PHONOGRAPH = 0x0011,
    GRIDITEM_STATE_ZEN_TOOL_GOLD_WATERING_CAN = 0x0012,
    GRIDITEM_STINKY_WALKING_LEFT = 0x0013,
    GRIDITEM_STINKY_TURNING_LEFT = 0x0014,
    GRIDITEM_STINKY_WALKING_RIGHT = 0x0015,
    GRIDITEM_STINKY_TURNING_RIGHT = 0x0016,
    GRIDITEM_STINKY_SLEEPING = 0x0017,
    GRIDITEM_STINKY_FALLING_ASLEEP = 0x0018,
    GRIDITEM_STINKY_WAKING_UP = 0x0019,
    GRIDITEM_STATE_RAKE_ATTRACTING = 0x001a,
    GRIDITEM_STATE_RAKE_WAITING = 0x001b,
    GRIDITEM_STATE_RAKE_TRIGGERED = 0x001c,
    GRIDITEM_STATE_BRAIN_SQUISHED = 0x001d,
};
#endif

enum ChallengeState : int
{
    STATECHALLENGE_NORMAL = 0x0000,
    STATECHALLENGE_BEGHOULED_MOVING = 0x0001,
    STATECHALLENGE_BEGHOULED_FALLING = 0x0002,
    STATECHALLENGE_BEGHOULED_NO_MATCHES = 0x0003,
    STATECHALLENGE_SLOT_MACHINE_ROLLING = 0x0004,
    STATECHALLENGE_STORM_FLASH_1 = 0x0005,
    STATECHALLENGE_STORM_FLASH_2 = 0x0006,
    STATECHALLENGE_STORM_FLASH_3 = 0x0007,
    STATECHALLENGE_ZEN_FADING = 0x0008,
    STATECHALLENGE_SCARY_POTTER_MALLETING = 0x0009,
    STATECHALLENGE_LAST_STAND_ONSLAUGHT = 0x000a,
    STATECHALLENGE_TREE_JUST_GREW = 0x000b,
    STATECHALLENGE_TREE_GIVE_WISDOM = 0x000c,
    STATECHALLENGE_TREE_WAITING_TO_BABBLE = 0x000d,
    STATECHALLENGE_TREE_BABBLING = 0x000e,
};

enum ScaryPotType : int
{
    SCARYPOT_NONE = 0x0000,
    SCARYPOT_SEED = 0x0001,
    SCARYPOT_ZOMBIE = 0x0002,
    SCARYPOT_SUN = 0x0003,
};

#ifndef E_PLANTING_REASON
#define E_PLANTING_REASON
enum PlantingReason : int
{
    PLANTING_OK = 0x0000,
    PLANTING_NOT_HERE = 0x0001,
    PLANTING_ONLY_ON_GRAVES = 0x0002,
    PLANTING_ONLY_IN_POOL = 0x0003,
    PLANTING_ONLY_ON_GROUND = 0x0004,
    PLANTING_NEEDS_POT = 0x0005,
    PLANTING_NOT_ON_ART = 0x0006,
    PLANTING_NOT_PASSED_LINE = 0x0007,
    PLANTING_NEEDS_UPGRADE = 0x0008,
    PLANTING_NOT_ON_GRAVE = 0x0009,
    PLANTING_NOT_ON_CRATER = 0x000a,
    PLANTING_NOT_ON_WATER = 0x000b,
    PLANTING_NEEDS_GROUND = 0x000c,
    PLANTING_NEEDS_SLEEPING = 0x000d,
};
#endif

#ifndef E_ZOMBIE_TYPE
#define E_ZOMBIE_TYPE
enum ZombieType : int
{
    ZOMBIE_INVALID = -1,
    ZOMBIE_NORMAL = 0x0000,
    ZOMBIE_FLAG = 0x0001,
    ZOMBIE_TRAFFIC_CONE = 0x0002,
    ZOMBIE_POLEVAULTER = 0x0003,
    ZOMBIE_PAIL = 0x0004,
    ZOMBIE_NEWSPAPER = 0x0005,
    ZOMBIE_DOOR = 0x0006,
    ZOMBIE_FOOTBALL = 0x0007,
    ZOMBIE_DANCER = 0x0008,
    ZOMBIE_BACKUP_DANCER = 0x0009,
    ZOMBIE_DUCKY_TUBE = 0x000a,
    ZOMBIE_SNORKEL = 0x000b,
    ZOMBIE_ZAMBONI = 0x000c,
    ZOMBIE_BOBSLED = 0x000d,
    ZOMBIE_DOLPHIN_RIDER = 0x000e,
    ZOMBIE_JACK_IN_THE_BOX = 0x000f,
    ZOMBIE_BALLOON = 0x0010,
    ZOMBIE_DIGGER = 0x0011,
    ZOMBIE_POGO = 0x0012,
    ZOMBIE_YETI = 0x0013,
    ZOMBIE_BUNGEE = 0x0014,
    ZOMBIE_LADDER = 0x0015,
    ZOMBIE_CATAPULT = 0x0016,
    ZOMBIE_GARGANTUAR = 0x0017,
    ZOMBIE_IMP = 0x0018,
    ZOMBIE_BOSS = 0x0019,
    ZOMBIE_PEA_HEAD = 0x001a,
    ZOMBIE_WALLNUT_HEAD = 0x001b,
    ZOMBIE_JALAPENO_HEAD = 0x001c,
    ZOMBIE_GATLING_HEAD = 0x001d,
    ZOMBIE_SQUASH_HEAD = 0x001e,
    ZOMBIE_TALLNUT_HEAD = 0x001f,
    ZOMBIE_REDEYE_GARGANTUAR = 0x0020,
    NUM_ZOMBIE_TYPES = 0x0021,
};
#endif

#ifndef E_FILTER_EFFECT
#define E_FILTER_EFFECT
enum FilterEffect : int
{
    FILTER_EFFECT_NONE = 0xff,
    FILTER_EFFECT_WASHED_OUT = 0x0000,
    FILTER_EFFECT_LESS_WASHED_OUT = 0x0001,
    FILTER_EFFECT_WHITE = 0x0002,
    NUM_FILTER_EFFECTS = 0x0003,
};
#endif

class Challenge
{ /* Size=0xbc */
  /* 0x0000 */ public:
    LawnApp *mApp;
  /* 0x0004 */ public:
    Board *mBoard;
  /* 0x0008 */ public:
    bool mBeghouledMouseCapture;
  /* 0x000c */ public:
    int mBeghouledMouseDownX;
  /* 0x0010 */ public:
    int mBeghouledMouseDownY;
  /* 0x0014 */ public:
    bool mBeghouledEated[9][6];
  /* 0x004a */ public:
    bool mBeghouledPurcasedUpgrade[3];
  /* 0x0050 */ public:
    int mBeghouledMatchesThisMove;
  /* 0x0054 */ public:
    ChallengeState mChallengeState;
  /* 0x0058 */ public:
    int mChallengeStateCounter;
  /* 0x005c */ public:
    int mConveyorBeltCounter;
  /* 0x0060 */ public:
    int mChallengeScore;
  /* 0x0064 */ public:
    bool mShowBowlingLine;
  /* 0x0068 */ public:
    SeedType mLastConveyorSeedType;
  /* 0x006c */ public:
    int mSurvivalStage;
  /* 0x0070 */ public:
    int mSlotMachineRollCount;
  /* 0x0074 */ public:
    ReanimationID mReanimChallenge;
  /* 0x0078 */ public:
    ReanimationID mReanimCloud[6];
  /* 0x0090 */ public:
    int mCloudCounter[6];
  /* 0x00a8 */ public:
    int mChallengeGridX;
  /* 0x00ac */ public:
    int mChallengeGridY;
  /* 0x00b0 */ public:
    int mScaryPotterPots;
  /* 0x00b4 */ public:
    int mRainCounter;
  /* 0x00b8 */ public:
    int mTreeOfWisdomTalkIndex;

  public:
    Challenge();

  public:
    void StartLevel();

  public:
    void BeghouledPopulateBoard();

  public:
    void LoadBeghouledBoardState(/* BeghouledBoardState * */ int);

  public:
    SeedType BeghouledPickSeed(int, int, /* BeghouledBoardState * */ int, bool);

  public:
    bool BeghouledBoardHasMatch(/* BeghouledBoardState * */ int);

  public:
    SeedType BeghouledGetPlantAt(int, int, /* BeghouledBoardState * */ int);

  public:
    int BeghouledVerticalMatchLength(int, int, /* BeghouledBoardState * */ int);

  public:
    int BeghouledHorizontalMatchLength(int, int, /* BeghouledBoardState * */ int);

  public:
    void BeghouledDragStart(int, int);

  public:
    void BeghouledDragUpdate(int, int);

  public:
    void BeghouledDragCancel();

  public:
    bool MouseMove(int, int);

  public:
    bool MouseDown(int, int, int, /* HitResult * */ int);

  public:
    bool MouseUp(int, int);

  public:
    void ClearCursor();

  public:
    void BeghouledRemoveHorizontalMatch(int, int, /* BeghouledBoardState * */ int);

  public:
    void BeghouledRemoveVerticalMatch(int, int, /* BeghouledBoardState * */ int);

  public:
    void BeghouledRemoveMatches(/* BeghouledBoardState * */ int);

  public:
    void Update();

  public:
    void UpdateBeghouled();

  public:
    bool UpdateBeghouledPlant(Plant *);

  public:
    void BeghouledFallIntoSquare(int, int, /* BeghouledBoardState * */ int);

  public:
    void BeghouledMakePlantsFall(/* BeghouledBoardState * */ int);

  public:
    void ZombieAtePlant(Zombie *, Plant *);

  public:
    void DrawBackdrop(Sexy::Graphics *);

  public:
    void DrawArtChallenge(Sexy::Graphics *);

  public:
    void CheckForCompleteArtChallenge(int, int);

  public:
    SeedType GetArtChallengeSeed(int, int);

  public:
    void PlantAdded(Plant *);

  public:
    PlantingReason CanPlantAt(int, int, SeedType);

  public:
    void DrawBeghouled(Sexy::Graphics *);

  public:
    bool BeghouledIsValidMove(int, int, int, int, /* BeghouledBoardState * */ int);

  public:
    bool BeghouledCheckForPossibleMoves(/* BeghouledBoardState * */ int);

  public:
    void BeghouledCheckStuckState();

  public:
    void InitZombieWavesSurvival();

  public:
    void InitZombieWavesFromList(ZombieType *, int);

  public:
    void InitZombieWaves();

  public:
    Sexy::TRect<int> ShotMachineGetHandleRect();

  public:
    void UpdateSlotMachine();

  public:
    void DrawSlotMachine(Sexy::Graphics *);

  public:
    bool UpdateToolTip(int, int);

  public:
    void WhackAZombieSpawning();

  public:
    bool UpdateZombieSpawning();

  public:
    void BeghouledClearCrater(int);

  public:
    void MouseDownWhackAZombie(int, int);

  public:
    void DrawStormNight(Sexy::Graphics *);

  public:
    void UpdateStormyNight();

  public:
    void InitLevel();

  public:
    void SpawnZombieWave();

  public:
    void GraveDangerSpawnRandomGrave();

  public:
    void GraveDangerSpawnGraveAt(int, int);

  public:
    void SpawnLevelAward(int, int);

  public:
    void BeghouledScore(int, int, int, bool);

  public:
    void DrawStormFlash(Sexy::Graphics *, int, int);

  public:
    void UpdateRainingSeeds();

  public:
    void PlayBossEnter();

  public:
    void UpdateConveyorBelt();

  public:
    void PortalStart();

  public:
    void UpdatePortalCombat();

  public:
    /* GridItem * */ int GetOtherPortal(/* GridItem * */ int);

  public:
    void UpdatePortal(/* GridItem * */ int);

  public:
    float PortalCombatRowSpawnWeight(int);

  public:
    bool CanTargetZombieWithPortals(Plant *, Zombie *);

  public:
    /* GridItem * */ int GetPortalToRight(int, int);

  public:
    /* GridItem * */ int GetPortalAt(int, int);

  public:
    void MoveAPortal();

  public:
    int GetPortalDistanceToMower(int);

  public:
    /* GridItem * */ int GetPortalToLeft(int, int);

  public:
    void BeghouledPacketClicked(/* SeedPacket * */ int);

  public:
    void BeghouledShuffle();

  public:
    bool BeghouledCanClearCrater();

  public:
    void BeghouledUpdateCraters();

  public:
    Zombie *ZombiquariumSpawnSnorkle();

  public:
    void ZombiquariumPacketClicked(/* SeedPacket * */ int);

  public:
    void ZombiquariumMouseDown(int, int);

  public:
    void ZombiquariumDropBrain(int, int);

  public:
    void ZombiquariumUpdate();

  public:
    void ShovelAddWallnuts();

  public:
    void ScaryPotterPlacePot(ScaryPotType, ZombieType, SeedType, int, /* TodWeightedGridArray * */ int, int);

  public:
    void ScaryPotterStart();

  public:
    void ScaryPotterUpdate();

  public:
    void ScaryPotterOpenPot(/* GridItem * */ int);

  public:
    void ScaryPotterJackExplode(int, int);

  public:
    bool ScaryPotterIsCompleted();

  public:
    void ScaryPotterChangePotType(GridItemState, int);

  public:
    void ScaryPotterPopulate();

  public:
    void ScaryPotterDontPlaceInCol(int, /* TodWeightedGridArray * */ int, int);

  public:
    void ScaryPotterFillColumnWithPlant(int, SeedType, /* TodWeightedGridArray * */ int, int);

  public:
    void PuzzleNextStageClear();

  public:
    void ScaryPotterMalletPot(/* GridItem * */ int);

  public:
    void IZombieMouseDownWithZombie(int, int, int);

  public:
    void IZombieStart();

  public:
    void IZombiePlacePlants(SeedType, int, int);

  public:
    void IZombieUpdate();

  public:
    void IZombieDrawPlant(Sexy::Graphics *, Plant *);

  public:
    void IZombieSetPlantFilterEffect(Plant *, FilterEffect);

  public:
    int ScaryPotterCountSunInPot(/* GridItem * */ int);

  public:
    int ScaryPotterCountPots();

  public:
    void IZombieInitLevel();

  public:
    void DrawRain(Sexy::Graphics *);

  public:
    void DrawWeather(Sexy::Graphics *);

  public:
    void SquirrelUpdate();

  public:
    int SquirrelCountUncaught();

  public:
    void SquirrelStart();

  public:
    void SquirrelFound(/* GridItem * */ int);

  public:
    void SquirrelPeek(/* GridItem * */ int);

  public:
    void SquirrelChew(/* GridItem * */ int);

  public:
    void SquirrelUpdateOne(/* GridItem * */ int);

  public:
    void IZombieSetupPlant(Plant *);

  public:
    void UpdateRain();

  public:
    bool IZombieEatBrain(Zombie *);

  public:
    /* GridItem * */ int IZombieGetBrainTarget(Zombie *);

  public:
    void IZombiePlacePlantInSquare(SeedType, int, int);

  public:
    void AdvanceCrazyDaveDialog();

  public:
    void BeghouledFlashPlant(int, int, int, int, int, int);

  public:
    void BeghouledFlashAMatch();

  public:
    bool BeghouledFlashFromBoardState(/* BeghouledBoardState * */ int, int, int, int, int);

  public:
    void IZombiePlantDropRemainingSun(Plant *);

  public:
    void IZombieSquishBrain(/* GridItem * */ int);

  public:
    void IZombieScoreBrain(/* GridItem * */ int);

  public:
    void LastStandUpate();

  public:
    void WhackAZombiePlaceGraves(int);

  public:
    bool BeghouledTwistSquareFromMouse(int, int, int &, int &);

  public:
    bool BeghouledTwistValidMove(int, int, /* BeghouledBoardState * */ int);

  public:
    void BeghouledTwistMouseDown(int, int);

  public:
    bool BeghouledTwistMoveCausesMatch(int, int, /* BeghouledBoardState * */ int);

  public:
    bool BeghouledTwistFlashMatch(/* BeghouledBoardState * */ int, int, int);

  public:
    void BeghouledCancelMatchFlashing();

  public:
    void BeghouledStartFalling(ChallengeState);

  public:
    void BeghouledFillHoles(/* BeghouledBoardState * */ int, bool);

  public:
    void BeghouledMakeStartBoard();

  public:
    void BeghouledCreatePlants(/* BeghouledBoardState * */ int, /* BeghouledBoardState * */ int);

  public:
    void PuzzlePhaseComplete(int, int);

  public:
    void IZombiePlaceZombie(ZombieType, int, int);

  public:
    void WhackAZombieUpdate();

  public:
    void LastStandCompletedStage();

  public:
    void TreeOfWisdomUpdate();

  public:
    void TreeOfWisdomFertilize();

  public:
    void TreeOfWisdomInit();

  public:
    int TreeOfWisdomGetSize();

  public:
    void TreeOfWisdomDraw(Sexy::Graphics *);

  public:
    void TreeOfWisdomNextGarden();

  public:
    void TreeOfWisdomToolUpdate(/* GridItem * */ int);

  public:
    void TreeOfWisdomOpenStore();

  public:
    void TreeOfWisdomLeave();

  public:
    void TreeOfWisdomGrow();

  public:
    void TreeOfWisdomTool(int, int);

  public:
    bool TreeOfWisdomHitTest(int, int, /* HitResult * */ int);

  public:
    void TreeOfWisdomBabble();

  public:
    void TreeOfWisdomGiveWisdom();

  public:
    bool TreeOfWisdomCanFeed();

  public:
    static ZombieType IZombieSeedTypeToZombieType(SeedType);

  public:
    static bool IsZombieSeedType(SeedType);
};

#endif // __CHALLENGE_H__