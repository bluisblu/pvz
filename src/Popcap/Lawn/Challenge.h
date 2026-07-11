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
class GridItem;

#ifndef E_GRID_ITEM_STATE
#define E_GRID_ITEM_STATE
enum GridItemState : int
{
    GRIDITEM_STATE_NORMAL                     = 0x0000,
    GRIDITEM_STATE_GRAVESTONE_SPECIAL         = 0x0001,
    GRIDITEM_STATE_PORTAL_CLOSED              = 0x0002,
    GRIDITEM_STATE_SCARY_POT_QUESTION         = 0x0003,
    GRIDITEM_STATE_SCARY_POT_LEAF             = 0x0004,
    GRIDITEM_STATE_SCARY_POT_ZOMBIE           = 0x0005,
    GRIDITEM_STATE_SQUIRREL_WAITING           = 0x0006,
    GRIDITEM_STATE_SQUIRREL_PEEKING           = 0x0007,
    GRIDITEM_STATE_SQUIRREL_RUNNING_UP        = 0x0008,
    GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN      = 0x0009,
    GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT      = 0x000a,
    GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT     = 0x000b,
    GRIDITEM_STATE_SQUIRREL_CAUGHT            = 0x000c,
    GRIDITEM_STATE_SQUIRREL_ZOMBIE            = 0x000d,
    GRIDITEM_STATE_ZEN_TOOL_WATERING_CAN      = 0x000e,
    GRIDITEM_STATE_ZEN_TOOL_FERTILIZER        = 0x000f,
    GRIDITEM_STATE_ZEN_TOOL_BUG_SPRAY         = 0x0010,
    GRIDITEM_STATE_ZEN_TOOL_PHONOGRAPH        = 0x0011,
    GRIDITEM_STATE_ZEN_TOOL_GOLD_WATERING_CAN = 0x0012,
    GRIDITEM_STINKY_WALKING_LEFT              = 0x0013,
    GRIDITEM_STINKY_TURNING_LEFT              = 0x0014,
    GRIDITEM_STINKY_WALKING_RIGHT             = 0x0015,
    GRIDITEM_STINKY_TURNING_RIGHT             = 0x0016,
    GRIDITEM_STINKY_SLEEPING                  = 0x0017,
    GRIDITEM_STINKY_FALLING_ASLEEP            = 0x0018,
    GRIDITEM_STINKY_WAKING_UP                 = 0x0019,
    GRIDITEM_STATE_RAKE_ATTRACTING            = 0x001a,
    GRIDITEM_STATE_RAKE_WAITING               = 0x001b,
    GRIDITEM_STATE_RAKE_TRIGGERED             = 0x001c,
    GRIDITEM_STATE_BRAIN_SQUISHED             = 0x001d,
};
#endif

enum ChallengeState : int
{
    STATECHALLENGE_NORMAL                 = 0x0000,
    STATECHALLENGE_BEGHOULED_MOVING       = 0x0001,
    STATECHALLENGE_BEGHOULED_FALLING      = 0x0002,
    STATECHALLENGE_BEGHOULED_NO_MATCHES   = 0x0003,
    STATECHALLENGE_SLOT_MACHINE_ROLLING   = 0x0004,
    STATECHALLENGE_STORM_FLASH_1          = 0x0005,
    STATECHALLENGE_STORM_FLASH_2          = 0x0006,
    STATECHALLENGE_STORM_FLASH_3          = 0x0007,
    STATECHALLENGE_ZEN_FADING             = 0x0008,
    STATECHALLENGE_SCARY_POTTER_MALLETING = 0x0009,
    STATECHALLENGE_LAST_STAND_ONSLAUGHT   = 0x000a,
    STATECHALLENGE_TREE_JUST_GREW         = 0x000b,
    STATECHALLENGE_TREE_GIVE_WISDOM       = 0x000c,
    STATECHALLENGE_TREE_WAITING_TO_BABBLE = 0x000d,
    STATECHALLENGE_TREE_BABBLING          = 0x000e,
};

#ifndef E_SCARY_POT_TYPE
#define E_SCARY_POT_TYPE
enum ScaryPotType : int
{
    SCARYPOT_NONE   = 0x0000,
    SCARYPOT_SEED   = 0x0001,
    SCARYPOT_ZOMBIE = 0x0002,
    SCARYPOT_SUN    = 0x0003,
};
#endif

#ifndef E_PLANTING_REASON
#define E_PLANTING_REASON
enum PlantingReason : int
{
    PLANTING_OK              = 0x0000,
    PLANTING_NOT_HERE        = 0x0001,
    PLANTING_ONLY_ON_GRAVES  = 0x0002,
    PLANTING_ONLY_IN_POOL    = 0x0003,
    PLANTING_ONLY_ON_GROUND  = 0x0004,
    PLANTING_NEEDS_POT       = 0x0005,
    PLANTING_NOT_ON_ART      = 0x0006,
    PLANTING_NOT_PASSED_LINE = 0x0007,
    PLANTING_NEEDS_UPGRADE   = 0x0008,
    PLANTING_NOT_ON_GRAVE    = 0x0009,
    PLANTING_NOT_ON_CRATER   = 0x000a,
    PLANTING_NOT_ON_WATER    = 0x000b,
    PLANTING_NEEDS_GROUND    = 0x000c,
    PLANTING_NEEDS_SLEEPING  = 0x000d,
};
#endif

#ifndef E_ZOMBIE_TYPE
#define E_ZOMBIE_TYPE
enum ZombieType : int
{
    ZOMBIE_INVALID           = -1,
    ZOMBIE_NORMAL            = 0x0000,
    ZOMBIE_FLAG              = 0x0001,
    ZOMBIE_TRAFFIC_CONE      = 0x0002,
    ZOMBIE_POLEVAULTER       = 0x0003,
    ZOMBIE_PAIL              = 0x0004,
    ZOMBIE_NEWSPAPER         = 0x0005,
    ZOMBIE_DOOR              = 0x0006,
    ZOMBIE_FOOTBALL          = 0x0007,
    ZOMBIE_DANCER            = 0x0008,
    ZOMBIE_BACKUP_DANCER     = 0x0009,
    ZOMBIE_DUCKY_TUBE        = 0x000a,
    ZOMBIE_SNORKEL           = 0x000b,
    ZOMBIE_ZAMBONI           = 0x000c,
    ZOMBIE_BOBSLED           = 0x000d,
    ZOMBIE_DOLPHIN_RIDER     = 0x000e,
    ZOMBIE_JACK_IN_THE_BOX   = 0x000f,
    ZOMBIE_BALLOON           = 0x0010,
    ZOMBIE_DIGGER            = 0x0011,
    ZOMBIE_POGO              = 0x0012,
    ZOMBIE_YETI              = 0x0013,
    ZOMBIE_BUNGEE            = 0x0014,
    ZOMBIE_LADDER            = 0x0015,
    ZOMBIE_CATAPULT          = 0x0016,
    ZOMBIE_GARGANTUAR        = 0x0017,
    ZOMBIE_IMP               = 0x0018,
    ZOMBIE_BOSS              = 0x0019,
    ZOMBIE_PEA_HEAD          = 0x001a,
    ZOMBIE_WALLNUT_HEAD      = 0x001b,
    ZOMBIE_JALAPENO_HEAD     = 0x001c,
    ZOMBIE_GATLING_HEAD      = 0x001d,
    ZOMBIE_SQUASH_HEAD       = 0x001e,
    ZOMBIE_TALLNUT_HEAD      = 0x001f,
    ZOMBIE_REDEYE_GARGANTUAR = 0x0020,
    NUM_ZOMBIE_TYPES         = 0x0021,
};
#endif

#ifndef E_FILTER_EFFECT
#define E_FILTER_EFFECT
enum FilterEffect : int
{
    FILTER_EFFECT_NONE            = 0xff,
    FILTER_EFFECT_WASHED_OUT      = 0x0000,
    FILTER_EFFECT_LESS_WASHED_OUT = 0x0001,
    FILTER_EFFECT_WHITE           = 0x0002,
    NUM_FILTER_EFFECTS            = 0x0003,
};
#endif

class Challenge
{ /* Size=0xbc */
  public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Board *mBoard;
    /* 0x0008 */ bool mBeghouledMouseCapture;
    /* 0x000c */ int mBeghouledMouseDownX;
    /* 0x0010 */ int mBeghouledMouseDownY;
    /* 0x0014 */ bool mBeghouledEated[9][6];
    /* 0x004a */ bool mBeghouledPurcasedUpgrade[3];
    /* 0x0050 */ int mBeghouledMatchesThisMove;
    /* 0x0054 */ ChallengeState mChallengeState;
    /* 0x0058 */ int mChallengeStateCounter;
    /* 0x005c */ int mConveyorBeltCounter;
    /* 0x0060 */ int mChallengeScore;
    /* 0x0064 */ bool mShowBowlingLine;
    /* 0x0068 */ SeedType mLastConveyorSeedType;
    /* 0x006c */ int mSurvivalStage;
    /* 0x0070 */ int mSlotMachineRollCount;
    /* 0x0074 */ ReanimationID mReanimChallenge;
    /* 0x0078 */ ReanimationID mReanimCloud[6];
    /* 0x0090 */ int mCloudCounter[6];
    /* 0x00a8 */ int mChallengeGridX;
    /* 0x00ac */ int mChallengeGridY;
    /* 0x00b0 */ int mScaryPotterPots;
    /* 0x00b4 */ int mRainCounter;
    /* 0x00b8 */ int mTreeOfWisdomTalkIndex;

  public:
    Challenge();
    void StartLevel();
    void BeghouledPopulateBoard();
    void LoadBeghouledBoardState(/* BeghouledBoardState * */ void *);
    SeedType BeghouledPickSeed(int, int, /* BeghouledBoardState * */ void *, bool);
    bool BeghouledBoardHasMatch(/* BeghouledBoardState * */ void *);
    SeedType BeghouledGetPlantAt(int, int, /* BeghouledBoardState * */ void *);
    int BeghouledVerticalMatchLength(int, int, /* BeghouledBoardState * */ void *);
    int BeghouledHorizontalMatchLength(int, int, /* BeghouledBoardState * */ void *);
    void BeghouledDragStart(int, int);
    void BeghouledDragUpdate(int, int);
    void BeghouledDragCancel();
    bool MouseMove(int, int);
    bool MouseDown(int, int, int, /* HitResult * */ void *);
    bool MouseUp(int, int);
    void ClearCursor();
    void BeghouledRemoveHorizontalMatch(int, int, /* BeghouledBoardState * */ void *);
    void BeghouledRemoveVerticalMatch(int, int, /* BeghouledBoardState * */ void *);
    void BeghouledRemoveMatches(/* BeghouledBoardState * */ void *);
    void Update();
    void UpdateBeghouled();
    bool UpdateBeghouledPlant(Plant *);
    void BeghouledFallIntoSquare(int, int, /* BeghouledBoardState * */ void *);
    void BeghouledMakePlantsFall(/* BeghouledBoardState * */ void *);
    void ZombieAtePlant(Zombie *, Plant *);
    void DrawBackdrop(Sexy::Graphics *);
    void DrawArtChallenge(Sexy::Graphics *);
    void CheckForCompleteArtChallenge(int, int);
    SeedType GetArtChallengeSeed(int, int);
    void PlantAdded(Plant *);
    PlantingReason CanPlantAt(int, int, SeedType);
    void DrawBeghouled(Sexy::Graphics *);
    bool BeghouledIsValidMove(int, int, int, int, /* BeghouledBoardState * */ void *);
    bool BeghouledCheckForPossibleMoves(/* BeghouledBoardState * */ void *);
    void BeghouledCheckStuckState();
    void InitZombieWavesSurvival();
    void InitZombieWavesFromList(ZombieType *, int);
    void InitZombieWaves();
    Sexy::TRect<int> ShotMachineGetHandleRect();
    void UpdateSlotMachine();
    void DrawSlotMachine(Sexy::Graphics *);
    bool UpdateToolTip(int, int);
    void WhackAZombieSpawning();
    bool UpdateZombieSpawning();
    void BeghouledClearCrater(int);
    void MouseDownWhackAZombie(int, int);
    void DrawStormNight(Sexy::Graphics *);
    void UpdateStormyNight();
    void InitLevel();
    void SpawnZombieWave();
    void GraveDangerSpawnRandomGrave();
    void GraveDangerSpawnGraveAt(int, int);
    void SpawnLevelAward(int, int);
    void BeghouledScore(int, int, int, bool);
    void DrawStormFlash(Sexy::Graphics *, int, int);
    void UpdateRainingSeeds();
    void PlayBossEnter();
    void UpdateConveyorBelt();
    void PortalStart();
    void UpdatePortalCombat();
    GridItem *GetOtherPortal(GridItem *);
    void UpdatePortal(GridItem *);
    float PortalCombatRowSpawnWeight(int);
    bool CanTargetZombieWithPortals(Plant *, Zombie *);
    GridItem *GetPortalToRight(int, int);
    GridItem *GetPortalAt(int, int);
    void MoveAPortal();
    int GetPortalDistanceToMower(int);
    GridItem *GetPortalToLeft(int, int);
    void BeghouledPacketClicked(/* SeedPacket * */ void *);
    void BeghouledShuffle();
    bool BeghouledCanClearCrater();
    void BeghouledUpdateCraters();
    Zombie *ZombiquariumSpawnSnorkle();
    void ZombiquariumPacketClicked(/* SeedPacket * */ void *);
    void ZombiquariumMouseDown(int, int);
    void ZombiquariumDropBrain(int, int);
    void ZombiquariumUpdate();
    void ShovelAddWallnuts();
    void ScaryPotterPlacePot(ScaryPotType, ZombieType, SeedType, int,
                             /* TodWeightedGridArray * */ void *, int);
    void ScaryPotterStart();
    void ScaryPotterUpdate();
    void ScaryPotterOpenPot(GridItem *);
    void ScaryPotterJackExplode(int, int);
    bool ScaryPotterIsCompleted();
    void ScaryPotterChangePotType(GridItemState, int);
    void ScaryPotterPopulate();
    void ScaryPotterDontPlaceInCol(int, /* TodWeightedGridArray * */ void *, int);
    void ScaryPotterFillColumnWithPlant(int, SeedType, /* TodWeightedGridArray * */ void *, int);
    void PuzzleNextStageClear();
    void ScaryPotterMalletPot(GridItem *);
    void IZombieMouseDownWithZombie(int, int, int);
    void IZombieStart();
    void IZombiePlacePlants(SeedType, int, int);
    void IZombieUpdate();
    void IZombieDrawPlant(Sexy::Graphics *, Plant *);
    void IZombieSetPlantFilterEffect(Plant *, FilterEffect);
    int ScaryPotterCountSunInPot(GridItem *);
    int ScaryPotterCountPots();
    void IZombieInitLevel();
    void DrawRain(Sexy::Graphics *);
    void DrawWeather(Sexy::Graphics *);
    void SquirrelUpdate();
    int SquirrelCountUncaught();
    void SquirrelStart();
    void SquirrelFound(GridItem *);
    void SquirrelPeek(GridItem *);
    void SquirrelChew(GridItem *);
    void SquirrelUpdateOne(GridItem *);
    void IZombieSetupPlant(Plant *);
    void UpdateRain();
    bool IZombieEatBrain(Zombie *);
    GridItem *IZombieGetBrainTarget(Zombie *);
    void IZombiePlacePlantInSquare(SeedType, int, int);
    void AdvanceCrazyDaveDialog();
    void BeghouledFlashPlant(int, int, int, int, int, int);
    void BeghouledFlashAMatch();
    bool BeghouledFlashFromBoardState(/* BeghouledBoardState * */ void *, int, int, int, int);
    void IZombiePlantDropRemainingSun(Plant *);
    void IZombieSquishBrain(GridItem *);
    void IZombieScoreBrain(GridItem *);
    void LastStandUpate();
    void WhackAZombiePlaceGraves(int);
    bool BeghouledTwistSquareFromMouse(int, int, int &, int &);
    bool BeghouledTwistValidMove(int, int, /* BeghouledBoardState * */ void *);
    void BeghouledTwistMouseDown(int, int);
    bool BeghouledTwistMoveCausesMatch(int, int, /* BeghouledBoardState * */ void *);
    bool BeghouledTwistFlashMatch(/* BeghouledBoardState * */ void *, int, int);
    void BeghouledCancelMatchFlashing();
    void BeghouledStartFalling(ChallengeState);
    void BeghouledFillHoles(/* BeghouledBoardState * */ void *, bool);
    void BeghouledMakeStartBoard();
    void BeghouledCreatePlants(/* BeghouledBoardState * */ void *,
                               /* BeghouledBoardState * */ void *);
    void PuzzlePhaseComplete(int, int);
    void IZombiePlaceZombie(ZombieType, int, int);
    void WhackAZombieUpdate();
    void LastStandCompletedStage();
    void TreeOfWisdomUpdate();
    void TreeOfWisdomFertilize();
    void TreeOfWisdomInit();
    int TreeOfWisdomGetSize();
    void TreeOfWisdomDraw(Sexy::Graphics *);
    void TreeOfWisdomNextGarden();
    void TreeOfWisdomToolUpdate(GridItem *);
    void TreeOfWisdomOpenStore();
    void TreeOfWisdomLeave();
    void TreeOfWisdomGrow();
    void TreeOfWisdomTool(int, int);
    bool TreeOfWisdomHitTest(int, int, /* HitResult * */ void *);
    void TreeOfWisdomBabble();
    void TreeOfWisdomGiveWisdom();
    bool TreeOfWisdomCanFeed();
    static ZombieType IZombieSeedTypeToZombieType(SeedType);
    static bool IsZombieSeedType(SeedType);
};

#endif // __CHALLENGE_H__
