#pragma once

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

enum ProjectileType : int
{
    PROJECTILE_PEA = 0x0000,
    PROJECTILE_SNOWPEA = 0x0001,
    PROJECTILE_CABBAGE = 0x0002,
    PROJECTILE_MELON = 0x0003,
    PROJECTILE_PUFF = 0x0004,
    PROJECTILE_WINTERMELON = 0x0005,
    PROJECTILE_FIREBALL = 0x0006,
    PROJECTILE_STAR = 0x0007,
    PROJECTILE_SPIKE = 0x0008,
    PROJECTILE_BASKETBALL = 0x0009,
    PROJECTILE_KERNEL = 0x000a,
    PROJECTILE_COBBIG = 0x000b,
    PROJECTILE_BUTTER = 0x000c,
    PROJECTILE_ZOMBIE_PEA = 0x000d,
    NUM_PROJECTILES = 0x000e,
};

#ifndef E_GAME_OBJECT_TYPE
#define E_GAME_OBJECT_TYPE
enum GameObjectType : int
{
    OBJECT_TYPE_NONE = 0x0000,
    OBJECT_TYPE_PLANT = 0x0001,
    OBJECT_TYPE_PROJECTILE = 0x0002,
    OBJECT_TYPE_COIN = 0x0003,
    OBJECT_TYPE_SEEDPACKET = 0x0004,
    OBJECT_TYPE_SHOVEL = 0x0005,
    OBJECT_TYPE_WATERING_CAN = 0x0006,
    OBJECT_TYPE_FERTILIZER = 0x0007,
    OBJECT_TYPE_BUG_SPRAY = 0x0008,
    OBJECT_TYPE_PHONOGRAPH = 0x0009,
    OBJECT_TYPE_CHOCOLATE = 0x000a,
    OBJECT_TYPE_GLOVE = 0x000b,
    OBJECT_TYPE_MONEY_SIGN = 0x000c,
    OBJECT_TYPE_WHEELBARROW = 0x000d,
    OBJECT_TYPE_TREE_FOOD = 0x000e,
    OBJECT_TYPE_NEXT_GARDEN = 0x000f,
    OBJECT_TYPE_MENU_BUTTON = 0x0010,
    OBJECT_TYPE_STORE_BUTTON = 0x0011,
    OBJECT_TYPE_SLOT_MACHINE_HANDLE = 0x0012,
    OBJECT_TYPE_SCARY_POT = 0x0013,
    OBJECT_TYPE_STINKY = 0x0014,
    OBJECT_TYPE_TREE_OF_WISDOM = 0x0015,
};
#endif

enum PlantPriority : int
{
    TOPPLANT_EATING_ORDER = 0x0000,
    TOPPLANT_DIGGING_ORDER = 0x0001,
    TOPPLANT_BUNGEE_ORDER = 0x0002,
    TOPPLANT_CATAPULT_ORDER = 0x0003,
    TOPPLANT_ZEN_TOOL_ORDER = 0x0004,
    TOPPLANT_ANY = 0x0005,
    TOPPLANT_ONLY_NORMAL_POSITION = 0x0006,
    TOPPLANT_ONLY_FLYING = 0x0007,
    TOPPLANT_ONLY_PUMPKIN = 0x0008,
    TOPPLANT_ONLY_UNDER_PLANT = 0x0009,
};

enum DebugTextMode : int
{
    DEBUG_TEXT_NONE = 0x0000,
    DEBUG_TEXT_ZOMBIE_SPAWN = 0x0001,
    DEBUG_TEXT_MUSIC = 0x0002,
    DEBUG_TEXT_MEMORY = 0x0003,
    DEBUG_TEXT_COLLISION = 0x0004,
};

enum MessageStyle : int
{
    MESSAGE_STYLE_OFF = 0x0000,
    MESSAGE_STYLE_TUTORIAL_LEVEL1 = 0x0001,
    MESSAGE_STYLE_TUTORIAL_LEVEL1_STAY = 0x0002,
    MESSAGE_STYLE_TUTORIAL_LEVEL2 = 0x0003,
    MESSAGE_STYLE_TUTORIAL_LATER = 0x0004,
    MESSAGE_STYLE_TUTORIAL_LATER_STAY = 0x0005,
    MESSAGE_STYLE_HINT_LONG = 0x0006,
    MESSAGE_STYLE_HINT_FAST = 0x0007,
    MESSAGE_STYLE_HINT_STAY = 0x0008,
    MESSAGE_STYLE_HINT_TALL_FAST = 0x0009,
    MESSAGE_STYLE_HINT_TALL_10SECONDS = 0x000a,
    MESSAGE_STYLE_HINT_TALL_8SECONDS = 0x000b,
    MESSAGE_STYLE_HINT_TALL_LONG = 0x000c,
    MESSAGE_STYLE_BIG_MIDDLE = 0x000d,
    MESSAGE_STYLE_BIG_MIDDLE_FAST = 0x000e,
    MESSAGE_STYLE_HOUSE_NAME = 0x000f,
    MESSAGE_STYLE_HUGE_WAVE = 0x0010,
    MESSAGE_STYLE_SLOT_MACHINE = 0x0011,
    MESSAGE_STYLE_ZEN_GARDEN_LONG = 0x0012,
};

enum GridSquareType : int
{
    GRIDSQUARE_NONE = 0x0000,
    GRIDSQUARE_GRASS = 0x0001,
    GRIDSQUARE_DIRT = 0x0002,
    GRIDSQUARE_POOL = 0x0003,
    GRIDSQUARE_HIGH_GROUND = 0x0004,
};

#ifndef E_COIN_MOTION
#define E_COIN_MOTION
enum CoinMotion : int
{
    COIN_MOTION_FROM_SKY = 0x0000,
    COIN_MOTION_FROM_SKY_SLOW = 0x0001,
    COIN_MOTION_FROM_PLANT = 0x0002,
    COIN_MOTION_COIN = 0x0003,
    COIN_MOTION_LAWNMOWER_COIN = 0x0004,
    COIN_MOTION_FROM_PRESENT = 0x0005,
    COIN_MOTION_FROM_BOSS = 0x0006,
};
#endif

enum BackgroundType : int
{
    BACKGROUND_1_DAY = 0x0000,
    BACKGROUND_2_NIGHT = 0x0001,
    BACKGROUND_3_POOL = 0x0002,
    BACKGROUND_4_FOG = 0x0003,
    BACKGROUND_5_ROOF = 0x0004,
    BACKGROUND_6_BOSS = 0x0005,
    BACKGROUND_MUSHROOM_GARDEN = 0x0006,
    BACKGROUND_GREENHOUSE = 0x0007,
    BACKGROUND_ZOMBIQUARIUM = 0x0008,
    BACKGROUND_TREE_OF_WISDOM = 0x0009,
};

enum AdviceType : int
{
    ADVICE_NONE = 0xff,
    ADVICE_CLICK_ON_SUN = 0x0000,
    ADVICE_CLICKED_ON_SUN = 0x0001,
    ADVICE_CLICKED_ON_COIN = 0x0002,
    ADVICE_SEED_REFRESH = 0x0003,
    ADVICE_CANT_AFFORD_PLANT = 0x0004,
    ADVICE_PLANT_GRAVEBUSTERS_ON_GRAVES = 0x0005,
    ADVICE_PLANT_LILYPAD_ON_WATER = 0x0006,
    ADVICE_PLANT_TANGLEKELP_ON_WATER = 0x0007,
    ADVICE_PLANT_SEASHROOM_ON_WATER = 0x0008,
    ADVICE_PLANT_POTATOE_MINE_ON_LILY = 0x0009,
    ADVICE_PLANT_WRONG_ART_TYPE = 0x000a,
    ADVICE_PLANT_NEED_POT = 0x000b,
    ADVICE_PLANT_NOT_ON_GRAVE = 0x000c,
    ADVICE_PLANT_NOT_ON_CRATER = 0x000d,
    ADVICE_CANT_PLANT_THERE = 0x000e,
    ADVICE_PLANT_NOT_ON_WATER = 0x000f,
    ADVICE_PLANTING_NEEDS_GROUND = 0x0010,
    ADVICE_BEGHOULED_DRAG_TO_MATCH_3 = 0x0011,
    ADVICE_BEGHOULED_MATCH_3 = 0x0012,
    ADVICE_BEGHOULED_MATCH_4 = 0x0013,
    ADVICE_BEGHOULED_SAVE_SUN = 0x0014,
    ADVICE_BEGHOULED_USE_CRATER_1 = 0x0015,
    ADVICE_BEGHOULED_USE_CRATER_2 = 0x0016,
    ADVICE_PLANT_NOT_PASSED_LINE = 0x0017,
    ADVICE_PLANT_ONLY_ON_REPEATERS = 0x0018,
    ADVICE_PLANT_ONLY_ON_MELONPULT = 0x0019,
    ADVICE_PLANT_ONLY_ON_SUNFLOWER = 0x001a,
    ADVICE_PLANT_ONLY_ON_SPIKEWEED = 0x001b,
    ADVICE_PLANT_ONLY_ON_KERNELPULT = 0x001c,
    ADVICE_PLANT_ONLY_ON_MAGNETSHROOM = 0x001d,
    ADVICE_PLANT_ONLY_ON_FUMESHROOM = 0x001e,
    ADVICE_PLANT_ONLY_ON_LILYPAD = 0x001f,
    ADVICE_PLANT_NEEDS_REPEATER = 0x0020,
    ADVICE_PLANT_NEEDS_MELONPULT = 0x0021,
    ADVICE_PLANT_NEEDS_SUNFLOWER = 0x0022,
    ADVICE_PLANT_NEEDS_SPIKEWEED = 0x0023,
    ADVICE_PLANT_NEEDS_KERNELPULT = 0x0024,
    ADVICE_PLANT_NEEDS_MAGNETSHROOM = 0x0025,
    ADVICE_PLANT_NEEDS_FUMESHROOM = 0x0026,
    ADVICE_PLANT_NEEDS_LILYPAD = 0x0027,
    ADVICE_SLOT_MACHINE_PULL = 0x0028,
    ADVICE_HUGE_WAVE = 0x0029,
    ADVICE_SHOVEL_REFRESH = 0x002a,
    ADVICE_PORTAL_RELOCATING = 0x002b,
    ADVICE_SLOT_MACHINE_COLLECT_SUN = 0x002c,
    ADVICE_DESTORY_POTS_TO_FINISIH_LEVEL = 0x002d,
    ADVICE_USE_SHOVEL_ON_POTS = 0x002e,
    ADVICE_ALMOST_THERE = 0x002f,
    ADVICE_ZOMBIQUARIUM_CLICK_TROPHY = 0x0030,
    ADVICE_ZOMBIQUARIUM_COLLECT_SUN = 0x0031,
    ADVICE_ZOMBIQUARIUM_CLICK_TO_FEED = 0x0032,
    ADVICE_ZOMBIQUARIUM_BUY_SNORKEL = 0x0033,
    ADVICE_I_ZOMBIE_PLANTS_NOT_REAL = 0x0034,
    ADVICE_I_ZOMBIE_NOT_PASSED_LINE = 0x0035,
    ADVICE_I_ZOMBIE_LEFT_OF_LINE = 0x0036,
    ADVICE_SLOT_MACHINE_SPIN_AGAIN = 0x0037,
    ADVICE_I_ZOMBIE_EAT_ALL_BRAINS = 0x0038,
    ADVICE_PEASHOOTER_DIED = 0x0039,
    ADVICE_STINKY_SLEEPING = 0x003a,
    ADVICE_BEGHOULED_NO_MOVES = 0x003b,
    ADVICE_PLANT_SUNFLOWER5 = 0x003c,
    ADVICE_PLANTING_NEED_SLEEPING = 0x003d,
    ADVICE_CLICK_TO_CONTINUE = 0x003e,
    ADVICE_SURVIVE_FLAGS = 0x003f,
    ADVICE_UNLOCKED_MODE = 0x0040,
    NUM_ADVICE_TYPES = 0x0041,
};

#ifndef E_COIN_TYPE
#define E_COIN_TYPE
enum CoinType : int
{
    COIN_NONE = 0x0000,
    COIN_SILVER = 0x0001,
    COIN_GOLD = 0x0002,
    COIN_DIAMOND = 0x0003,
    COIN_SUN = 0x0004,
    COIN_SMALLSUN = 0x0005,
    COIN_LARGESUN = 0x0006,
    COIN_FINAL_SEED_PACKET = 0x0007,
    COIN_TROPHY = 0x0008,
    COIN_SHOVEL = 0x0009,
    COIN_ALMANAC = 0x000a,
    COIN_CARKEYS = 0x000b,
    COIN_VASE = 0x000c,
    COIN_WATERING_CAN = 0x000d,
    COIN_TACO = 0x000e,
    COIN_NOTE = 0x000f,
    COIN_USABLE_SEED_PACKET = 0x0010,
    COIN_PRESENT_PLANT = 0x0011,
    COIN_AWARD_MONEY_BAG = 0x0012,
    COIN_AWARD_PRESENT = 0x0013,
    COIN_AWARD_BAG_DIAMOND = 0x0014,
    COIN_AWARD_SILVER_SUNFLOWER = 0x0015,
    COIN_AWARD_GOLD_SUNFLOWER = 0x0016,
    COIN_CHOCOLATE = 0x0017,
    COIN_AWARD_CHOCOLATE = 0x0018,
    COIN_PRESENT_MINIGAMES = 0x0019,
    COIN_PRESENT_PUZZLE_MODE = 0x001a,
};
#endif

#ifndef E_CURSOR_TYPE
#define E_CURSOR_TYPE
enum CursorType : int
{
    CURSOR_TYPE_NORMAL = 0x0000,
    CURSOR_TYPE_PLANT_FROM_BANK = 0x0001,
    CURSOR_TYPE_PLANT_FROM_USABLE_COIN = 0x0002,
    CURSOR_TYPE_PLANT_FROM_GLOVE = 0x0003,
    CURSOR_TYPE_PLANT_FROM_DUPLICATOR = 0x0004,
    CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW = 0x0005,
    CURSOR_TYPE_SHOVEL = 0x0006,
    CURSOR_TYPE_HAMMER = 0x0007,
    CURSOR_TYPE_COBCANNON_TARGET = 0x0008,
    CURSOR_TYPE_WATERING_CAN = 0x0009,
    CURSOR_TYPE_FERTILIZER = 0x000a,
    CURSOR_TYPE_BUG_SPRAY = 0x000b,
    CURSOR_TYPE_PHONOGRAPH = 0x000c,
    CURSOR_TYPE_CHOCOLATE = 0x000d,
    CURSOR_TYPE_GLOVE = 0x000e,
    CURSOR_TYPE_MONEY_SIGN = 0x000f,
    CURSOR_TYPE_WHEEELBARROW = 0x0010,
    CURSOR_TYPE_TREE_FOOD = 0x0011,
};
#endif

enum GridItemType : int
{
    GRIDITEM_NONE = 0x0000,
    GRIDITEM_GRAVESTONE = 0x0001,
    GRIDITEM_CRATER = 0x0002,
    GRIDITEM_LADDER = 0x0003,
    GRIDITEM_PORTAL_CIRCLE = 0x0004,
    GRIDITEM_PORTAL_SQUARE = 0x0005,
    GRIDITEM_BRAIN = 0x0006,
    GRIDITEM_SCARY_POT = 0x0007,
    GRIDITEM_SQUIRREL = 0x0008,
    GRIDITEM_ZEN_TOOL = 0x0009,
    GRIDITEM_STINKY = 0x000a,
    GRIDITEM_RAKE = 0x000b,
    GRIDITEM_IZOMBIE_BRAIN = 0x000c,
};

enum RenderLayer : int
{
    RENDER_LAYER_UI_BOTTOM = 0x000186a0,
    RENDER_LAYER_GROUND = 0x00030d40,
    RENDER_LAYER_LAWN = 0x000493e0,
    RENDER_LAYER_TOP = 0x00061a80,
    RENDER_LAYER_FOG = 0x0007a120,
    RENDER_LAYER_COIN_BANK = 0x000927c0,
    RENDER_LAYER_UI_TOP = 0x000aae60,
    RENDER_LAYER_ABOVE_UI = 0x000c3500,
    RENDER_LAYER_SCREEN_FADE = 0x000dbba0,
    RENDER_LAYER_ROW_OFFSET = 0x2710,
    RENDER_LAYER_GRAVE_STONE = 0x000497c8,
    RENDER_LAYER_PLANT = 0x00049bb0,
    RENDER_LAYER_ZOMBIE = 0x00049f98,
    RENDER_LAYER_PROJECTILE = 0x0004a768,
    RENDER_LAYER_LAWN_MOWER = 0x0004ab50,
    RENDER_LAYER_PARTICLE = 0x0004af38,
};

enum PlantRowType : int
{
    PLANTROW_DIRT = 0x0000,
    PLANTROW_NORMAL = 0x0001,
    PLANTROW_POOL = 0x0002,
    PLANTROW_HIGH_GROUND = 0x0003,
};

class TodSmoothArray
{ /* Size=0x10 */
  /* 0x0000 */ public:
    int mItem;
  /* 0x0004 */ public:
    float mWeight;
  /* 0x0008 */ public:
    float mLastPicked;
  /* 0x000c */ public:
    float mSecondLastPicked;
};

enum TutorialState : int
{
    TUTORIAL_OFF = 0x0000,
    TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER = 0x0001,
    TUTORIAL_LEVEL_1_PLANT_PEASHOOTER = 0x0002,
    TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER = 0x0003,
    TUTORIAL_LEVEL_1_COMPLETED = 0x0004,
    TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER = 0x0005,
    TUTORIAL_LEVEL_2_PLANT_SUNFLOWER = 0x0006,
    TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER = 0x0007,
    TUTORIAL_LEVEL_2_COMPLETED = 0x0008,
    TUTORIAL_MORESUN_PICK_UP_SUNFLOWER = 0x0009,
    TUTORIAL_MORESUN_PLANT_SUNFLOWER = 0x000a,
    TUTORIAL_MORESUN_REFRESH_SUNFLOWER = 0x000b,
    TUTORIAL_MORESUN_COMPLETED = 0x000c,
    TUTORIAL_SLOT_MACHINE_PULL = 0x000d,
    TUTORIAL_SLOT_MACHINE_COMPLETED = 0x000e,
    TUTORIAL_SHOVEL_PICKUP = 0x000f,
    TUTORIAL_SHOVEL_DIG = 0x0010,
    TUTORIAL_SHOVEL_KEEP_DIGGING = 0x0011,
    TUTORIAL_SHOVEL_COMPLETED = 0x0012,
    TUTORIAL_ZOMBIQUARIUM_BUY_SNORKEL = 0x0013,
    TUTORIAL_ZOMBIQUARIUM_BOUGHT_SNORKEL = 0x0014,
    TUTORIAL_ZOMBIQUARIUM_CLICK_TROPHY = 0x0015,
    TUTORIAL_ZEN_GARDEN_PICKUP_WATER = 0x0016,
    TUTORIAL_ZEN_GARDEN_WATER_PLANT = 0x0017,
    TUTORIAL_ZEN_GARDEN_KEEP_WATERING = 0x0018,
    TUTORIAL_ZEN_GARDEN_VISIT_STORE = 0x0019,
    TUTORIAL_ZEN_GARDEN_FERTILIZE_PLANTS = 0x001a,
    TUTORIAL_ZEN_GARDEN_COMPLETED = 0x001b,
    TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED = 0x001c,
    TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED = 0x001d,
    TUTORIAL_WHACK_A_ZOMBIE_COMPLETED = 0x001e,
};

#ifndef E_BOARD_RESULT
#define E_BOARD_RESULT
enum BoardResult : int
{
    BOARDRESULT_NONE = 0x0000,
    BOARDRESULT_WON = 0x0001,
    BOARDRESULT_LOST = 0x0002,
    BOARDRESULT_RESTART = 0x0003,
    BOARDRESULT_QUIT = 0x0004,
    BOARDRESULT_QUIT_APP = 0x0005,
    BOARDRESULT_CHEAT = 0x0006,
};
#endif

template <typename T> struct DataArray
{
    struct DataArrayItem
    {
        T mItem;   // the actual object
        int mID;   // unique ID/key used for lookups
        int mNext; // next index in free list
    };

    DataArrayItem *mBlock;      // 0x00 -> contiguous block of items
    unsigned int mMaxUsedCount; // 0x04 -> high water mark of active items
    unsigned int mMaxSize;      // 0x08 -> allocated capacity (# of DataArrayItem)
    unsigned int mFreeListHead; // 0x0C -> head index of free list
    unsigned int mSize;         // 0x10 -> current active count
    unsigned int mNextKey;      // 0x14 -> monotonically increasing key generator
    const char *mName;          // 0x18 -> debug name
};

class Board : public Sexy::Widget, public Sexy::ButtonListener
{   /* Size=0x57b0 */
    /* 0x0000: fields for Sexy::Widget */
    // char unk_0[0x88];
    /* 0x0088: fields for Sexy::ButtonListener */
    // char unk_88[4];
  /* 0x008c */ public:
    LawnApp *mApp;
  /* 0x0090 */ public:
    DataArray<Zombie> mZombies;
  /* 0x00ac */ public:
    DataArray<Plant> mPlants;
  /* 0x00c8 */ public:
    // DataArray<Projectile> mProjectiles;
    char unk_c8[0x1c];
  /* 0x00e4 */ public:
    // DataArray<Coin> mCoins;
    char unk_e4[0x1c];
  /* 0x0100 */ public:
    // DataArray<LawnMower> mLawnMowers;
    char unk_100[0x1c];
  /* 0x011c */ public:
    // DataArray<GridItem> mGridItems;
    char unk_11c[0x1c];
  /* 0x0138 */ public:
    CursorObject *mCursorObject;
  /* 0x013c */ public:
    /* CursorPreview * */ int mCursorPreview;
  /* 0x0140 */ public:
    /* MessageWidget * */ int mAdvice;
  /* 0x0144 */ public:
    /* SeedBank * */ int mSeedBank;
  /* 0x0148 */ public:
    /* GameButton * */ int mMenuButton;
  /* 0x014c */ public:
    /* GameButton * */ int mStoreButton;
  /* 0x0150 */ public:
    bool mIgnoreMouseUp;
    char pad_0x151[3];
  /* 0x0154 */ public:
    /* ToolTipWidget * */ int mToolTip;
  /* 0x0158 */ public:
    Sexy::Font *mDebugFont;
  /* 0x015c */ public:
    CutScene *mCutScene;
  /* 0x0160 */ public:
    Challenge *mChallenge;
  /* 0x0164 */ public:
    bool mPaused;
    char pad_0x165[3];
  /* 0x0168 */ public:
    GridSquareType mGridSquareType[9][6];
  /* 0x0240 */ public:
    int mGridCelLook[9][6];
  /* 0x0318 */ public:
    int mGridCelOffset[9][6][2];
  /* 0x04c8 */ public:
    int mGridCelFog[9][7];
  /* 0x05c4 */ public:
    bool mEnableGraveStones;
    char pad_0x5c5[3];
  /* 0x05c8 */ public:
    int mSpecialGraveStoneX;
  /* 0x05cc */ public:
    int mSpecialGraveStoneY;
  /* 0x05d0 */ public:
    float mFogOffset;
  /* 0x05d4 */ public:
    int mFogBlownCountDown;
  /* 0x05d8 */ public:
    PlantRowType mPlantRow[6];
  /* 0x05f0 */ public:
    int mWaveRowGotLawnMowered[6];
  /* 0x0608 */ public:
    int mBonusLawnMowersRemaining;
  /* 0x060c */ public:
    int mIceMinX[6];
  /* 0x0624 */ public:
    int mIceTimer[6];
  /* 0x063c */ public:
    ParticleSystemID mIceParticleID[6];
  /* 0x0654 */ public:
    TodSmoothArray mRowPickingArray[6];
  /* 0x06b4 */ public:
    ZombieType mZombiesInWave[100][50];
  /* 0x54d4 */ public:
    bool mZombieAllowed[100];
  /* 0x5538 */ public:
    int mSunCountDown;
  /* 0x553c */ public:
    int mNumSunsFallen;
  /* 0x5540 */ public:
    int mShakeCounter;
  /* 0x5544 */ public:
    int mShakeAmountX;
  /* 0x5548 */ public:
    int mShakeAmountY;
  /* 0x554c */ public:
    BackgroundType mBackground;
  /* 0x5550 */ public:
    int mLevel;
  /* 0x5554 */ public:
    int mSodPosition;
  /* 0x5558 */ public:
    int mPrevMouseX;
  /* 0x555c */ public:
    int mPrevMouseY;
  /* 0x5560 */ public:
    int mSunMoney;
  /* 0x5564 */ public:
    int mNumWaves;
  /* 0x5568 */ public:
    int mMainCounter;
  /* 0x556c */ public:
    int mEffectCounter;
  /* 0x5570 */ public:
    int mDrawCount;
  /* 0x5574 */ public:
    int mRiseFromGraveCounter;
  /* 0x5578 */ public:
    int mOutOfMoneyCounter;
  /* 0x557c */ public:
    int mCurrentWave;
  /* 0x5580 */ public:
    int mTotalSpawnedWaves;
  /* 0x5584 */ public:
    TutorialState mTutorialState;
  /* 0x5588 */ public:
    ParticleSystemID mTutorialParticleID;
  /* 0x558c */ public:
    int mTutorialTimer;
  /* 0x5590 */ public:
    int mLastBungeeWave;
  /* 0x5594 */ public:
    int mZombieHealthToNextWave;
  /* 0x5598 */ public:
    int mZombieHealthWaveStart;
  /* 0x559c */ public:
    int mZombieCountDown;
  /* 0x55a0 */ public:
    int mZombieCountDownStart;
  /* 0x55a4 */ public:
    int mHugeWaveCountDown;
  /* 0x55a8 */ public:
    bool mHelpDisplayed[65];
    char pad_0x55e9[3];
  /* 0x55ec */ public:
    AdviceType mHelpIndex;
  /* 0x55f0 */ public:
    bool mFinalBossKilled;
  /* 0x55f1 */ public:
    bool mShowShovel;
    char pad_0x55f2[2];
  /* 0x55f4 */ public:
    int mCoinBankFadeCount;
  /* 0x55f8 */ public:
    DebugTextMode mDebugTextMode;
  /* 0x55fc */ public:
    bool mLevelComplete;
    char pad_0x55fd[3];
  /* 0x5600 */ public:
    int mBoardFadeOutCounter;
  /* 0x5604 */ public:
    int mNextSurvivalStageCounter;
  /* 0x5608 */ public:
    int mScoreNextMowerCounter;
  /* 0x560c */ public:
    bool mLevelAwardSpawned;
    char pad_0x560d[3];
  /* 0x5610 */ public:
    int mProgressMeterWidth;
  /* 0x5614 */ public:
    int mFlagRaiseCounter;
  /* 0x5618 */ public:
    int mIceTrapCounter;
  /* 0x561c */ public:
    int mBoardRandSeed;
  /* 0x5620 */ public:
    ParticleSystemID mPoolSparklyParticleID;
  /* 0x5624 */ public:
    ReanimationID mFwooshID[6][12];
  /* 0x5744 */ public:
    int mFwooshCountDown;
  /* 0x5748 */ public:
    int mTimeStopCounter;
  /* 0x574c */ public:
    bool mDroppedFirstCoin;
    char pad_0x574d[3];
  /* 0x5750 */ public:
    int mFinalWaveSoundCounter;
  /* 0x5754 */ public:
    int mCobCannonCursorDelayCounter;
  /* 0x5758 */ public:
    int mCobCannonMouseX;
  /* 0x575c */ public:
    int mCobCannonMouseY;
  /* 0x5760 */ public:
    bool mKilledYeti;
  /* 0x5761 */ public:
    bool mMustacheMode;
  /* 0x5762 */ public:
    bool mSuperMowerMode;
  /* 0x5763 */ public:
    bool mFutureMode;
  /* 0x5764 */ public:
    bool mPinataMode;
  /* 0x5765 */ public:
    bool mDaisyMode;
  /* 0x5766 */ public:
    bool mSukhbirMode;
    char pad_0x5767;
  /* 0x5768 */ public:
    BoardResult mPrevBoardResult;
  /* 0x576c */ public:
    int mTriggeredLawnMowers;
  /* 0x5770 */ public:
    int mPlayTimeActiveLevel;
  /* 0x5774 */ public:
    int mPlayTimeInactiveLevel;
  /* 0x5778 */ public:
    int mMaxSunPlants;
  /* 0x577c */ public:
    int mStartDrawTime;
  /* 0x5780 */ public:
    int mIntervalDrawTime;
  /* 0x5784 */ public:
    int mIntervalDrawCountStart;
  /* 0x5788 */ public:
    float mMinFPS;
  /* 0x578c */ public:
    int mPreloadTime;
  /* 0x5790 */ public:
    int mGameID;
  /* 0x5794 */ public:
    int mGravesCleared;
  /* 0x5798 */ public:
    int mPlantsEaten;
  /* 0x579c */ public:
    int mPlantsShoveled;
  /* 0x57a0 */ public:
    int mCoinsCollected;
  /* 0x57a4 */ public:
    int mDiamondsCollected;
  /* 0x57a8 */ public:
    int mPottedPlantsCollected;
  /* 0x57ac */ public:
    int mChocolateCollected;

  public:
    Board(const Board &);

  public:
    Board(LawnApp *);

  public:
    virtual ~Board();

  public:
    void DisposeBoard();

  public:
    int CountSunBeingCollected();

  public:
    void DrawGameObjects(/* Sexy::Graphics * */ int);

  public:
    void ClearCursor();

  public:
    bool AreEnemyZombiesOnScreen();

  public:
    /* LawnMower * */ int FindLawnMowerInRow(int);

  public:
    bool SyncState(/* DataSync & */ int);

  public:
    void SaveGame(const std::string &);

  public:
    bool LoadGame(const std::string &);

  public:
    void InitLevel();

  public:
    void DisplayAdvice(const std::string &, MessageStyle, AdviceType);

  public:
    void StartLevel();

  public:
    Plant *AddPlant(int, int, SeedType, SeedType);

  public:
    /* Projectile * */ int AddProjectile(int, int, int, int, ProjectileType);

  public:
    Coin *AddCoin(int, int, CoinType, CoinMotion);

  public:
    void RefreshSeedPacketFromCursor();

  public:
    ZombieType PickGraveRisingZombieType(int);

  public:
    ZombieType PickZombieType(int, int, /* ZombiePicker * */ int);

  public:
    int PickRowForNewZombie(ZombieType);

  public:
    Zombie *AddZombie(ZombieType, int);

  public:
    void SpawnZombieWave();

  public:
    void RemoveAllZombies();

  public:
    void RemoveCutsceneZombies();

  public:
    void SpawnZombiesFromGraves();

  public:
    PlantingReason CanPlantAt(int, int, SeedType);

  public:
    virtual void MouseMove(int, int);

  public:
    virtual void MouseDrag(int, int);

  public:
    virtual void MouseDown(int, int, int);

  public:
    virtual void MouseUp(int, int, int);

  public:
    virtual void KeyChar(char);

  public:
    virtual void KeyUp(Sexy::KeyCode);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    virtual void Update();

  public:
    void UpdateLayers();

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    void DrawBackdrop(Sexy::Graphics *);

  public:
    virtual void ButtonMouseEnter(int);

  public:
    virtual void ButtonMouseLeave(int);

  public:
    virtual void ButtonPress(int);

  public:
    void AddSunMoney(int);

  public:
    bool TakeSunMoney(int);

  public:
    bool CanTakeSunMoney(int);

  public:
    void Pause(bool);

  public:
    void MakeEasyZombieType();

  public:
    void TryToSaveGame();

  public:
    bool NeedSaveGame();

  public:
    bool RowCanHaveZombies(int);

  public:
    void ProcessDeleteQueue();

  public:
    bool ChooseSeedsOnCurrentLevel();

  public:
    int GetNumSeedsInBank();

  public:
    bool StageIsNight();

  public:
    bool StageHasPool();

  public:
    bool StageHas6Rows();

  public:
    bool StageHasFog();

  public:
    bool StageHasGraveStones();

  public:
    int PixelToGridX(int, int);

  public:
    int PixelToGridY(int, int);

  public:
    int GridToPixelX(int, int);

  public:
    int GridToPixelY(int, int);

  public:
    int PixelToGridXKeepOnBoard(int, int);

  public:
    int PixelToGridYKeepOnBoard(int, int);

  public:
    void UpdateGameObjects();

  public:
    bool MouseHitTest(int, int, /* HitResult * */ int);

  public:
    void MouseDownWithPlant(int, int, int);

  public:
    void MouseDownWithTool(int, int, int, CursorType);

  public:
    void MouseDownNormal(int, int, int);

  public:
    bool CanInteractWithBoardButtons();

  public:
    void DrawProgressMeter(Sexy::Graphics *);

  public:
    void UpdateToolTip();

  public:
    Plant *GetTopPlantAt(int, int, PlantPriority);

  public:
    void GetPlantsOnLawn(int, int, /* PlantsOnLawn * */ int);

  public:
    int CountSunFlowers();

  public:
    int GetSeedPacketPositionX(int);

  public:
    void AddGraveStones(int, int, Sexy::MTRand &);

  public:
    int GetGraveStoneCount();

  public:
    void ZombiesWon(Zombie *);

  public:
    void DrawLevel(Sexy::Graphics *);

  public:
    void DrawShovel(Sexy::Graphics *);

  public:
    void UpdateZombieSpawning();

  public:
    void UpdateSunSpawning();

  public:
    void ClearAdvice(AdviceType);

  public:
    bool RowCanHaveZombieType(int, ZombieType);

  public:
    int NumberZombiesInWave(int);

  public:
    int TotalZombiesHealthInWave(int);

  public:
    void DrawDebugText(Sexy::Graphics *);

  public:
    void DrawUICoinBank(Sexy::Graphics *);

  public:
    void ShowCoinBank();

  public:
    void FadeOutLevel();

  public:
    void DrawFadeOut(Sexy::Graphics *);

  public:
    void DrawIce(Sexy::Graphics *, int);

  public:
    bool IsIceAt(int, int);

  public:
    ZombieID ZombieGetID(Zombie *);

  public:
    Zombie *ZombieGet(ZombieID);

  public:
    Zombie *ZombieTryToGet(ZombieID);

  public:
    void DrawDebugObjectRects(Sexy::Graphics *);

  public:
    void UpdateIce();

  public:
    int GetIceZPos(int);

  public:
    bool CanAddBobSled();

  public:
    void ShakeBoard(int, int);

  public:
    int CountUntriggerLawnMowers();

  public:
    bool IterateZombies(Zombie *&);

  public:
    bool IteratePlants(Plant *&);

  public:
    bool IterateProjectiles(/* Projectile *& */ int);

  public:
    bool IterateCoins(/* Coin *& */ int);

  public:
    bool IterateLawnMowers(/* LawnMower *& */ int);

  public:
    bool IterateParticles(/* TodParticleSystem *& */ int);

  public:
    bool IterateReanimations(/* Reanimation *& */ int);

  public:
    bool IterateGridItems(/* GridItem *& */ int);

  public:
    Zombie *AddZombieInRow(ZombieType, int, int);

  public:
    bool IsPoolSquare(int, int);

  public:
    void PickZombieWaves();

  public:
    void StopAllZombieSounds();

  public:
    bool HasLevelAwardDropped();

  public:
    void UpdateProgressMeter();

  public:
    void DrawUIBottom(Sexy::Graphics *);

  public:
    void DrawUITop(Sexy::Graphics *);

  public:
    Zombie *ZombieHitTest(int, int);

  public:
    void KillAllPlantsInRadius(int, int, int);

  public:
    Plant *GetPumpkinAt(int, int);

  public:
    Plant *GetFlowerPotAt(int, int);

  public:
    bool IsZombieWaveDistributionOk();

  public:
    void PickBackground();

  public:
    void InitZombieWaves();

  public:
    void InitSurvivalStage();

  public:
    void UpdateGame();

  public:
    void InitZombieWavesForLevel(int);

  public:
    unsigned int SeedNotRecommendedForLevel(SeedType);

  public:
    void DrawTopRightUI(Sexy::Graphics *);

  public:
    void DrawFog(Sexy::Graphics *);

  public:
    void UpdateFog();

  public:
    int LeftFogColumn();

  public:
    void DropLootPiece(int, int, int);

  public:
    void UpdateLevelEndSequence();

  public:
    /* LawnMower * */ int GetBottomLawnMower();

  public:
    bool CanDropLoot();

  public:
    ZombieType GetIntroducedZombieType();

  public:
    void PickSpecialGraveStone();

  public:
    float GetPosYBasedOnRow(float, int);

  public:
    void NextWaveComing();

  public:
    bool BungeeIsTargetingCell(int, int);

  public:
    int PlantingPixelToGridX(int, int, SeedType);

  public:
    int PlantingPixelToGridY(int, int, SeedType);

  public:
    Plant *FindUmbrellaPlant(int, int);

  public:
    void SetTutorialState(TutorialState);

  public:
    void DoFwoosh(int);

  public:
    void UpdateFwoosh();

  public:
    Plant *SpecialPlantHitTest(int, int);

  public:
    void UpdateMousePosition();

  public:
    Plant *ToolHitTest(int, int);

  public:
    bool CanAddGraveStoneAt(int, int);

  public:
    void UpdateGridItems();

  public:
    /* GridItem * */ int AddAGraveStone(int, int);

  public:
    int GetSurvivalFlagsCompleted();

  public:
    bool HasProgressMeter();

  public:
    void UpdateCursor();

  public:
    void UpdateTutorial();

  public:
    SeedType GetSeedTypeInCursor();

  public:
    int CountPlantByType(SeedType);

  public:
    bool PlantingRequirementsMet(SeedType);

  public:
    bool HasValidCobCannonSpot();

  public:
    bool IsValidCobCannonSpot(int, int);

  public:
    bool IsValidCobCannonSpotHelper(int, int);

  public:
    void MouseDownCobcannonFire(int, int, int);

  public:
    void KillAllZombiesInRadius(int, int, int, int, int, bool, int);

  public:
    int GetSeedBankExtraWidth();

  public:
    bool IsFlagWave(int);

  public:
    void DrawHouseDoorTop(Sexy::Graphics *);

  public:
    void DrawHouseDoorBottom(Sexy::Graphics *);

  public:
    Zombie *GetBossZombie();

  public:
    bool HasConveyorBeltSeedBank();

  public:
    bool StageHasRoof();

  public:
    void SpawnZombiesFromPool();

  public:
    void SpawnZombiesFromSky();

  public:
    void PickUpTool(GameObjectType);

  public:
    void TutorialArrowShow(int, int);

  public:
    void TutorialArrowRemove();

  public:
    int CountCoinsBeingCollected();

  public:
    void BungeeDropZombie(/* BungeeDropGrid * */ int, ZombieType);

  public:
    void SetupBungeeDrop(/* BungeeDropGrid * */ int);

  public:
    void PutZombieInWave(ZombieType, int, /* ZombiePicker * */ int);

  public:
    void PutInMissingZombies(int, /* ZombiePicker * */ int);

  public:
    Sexy::TRect<int> GetShovelButtonRect();

  public:
    Sexy::TRect<int> GetZenButtonRect(GameObjectType);

  public:
    Plant *NewPlant(int, int, SeedType, SeedType);

  public:
    void DoPlantingEffects(int, int, Plant *);

  public:
    bool IsFinalSurvivalStage();

  public:
    void SurvivalSaveScore();

  public:
    int CountZombiesOnScreen();

  public:
    int GetNumWavesPerSurvivalStage();

  public:
    int GetLevelRandSeed();

  public:
    void AddBossRenderItem(/* RenderItem * */ int, int &, Zombie *);

  public:
    /* GridItem * */ int GetCraterAt(int, int);

  public:
    /* GridItem * */ int GetGraveStoneAt(int, int);

  public:
    /* GridItem * */ int GetLadderAt(int, int);

  public:
    /* GridItem * */ int AddALadder(int, int);

  public:
    /* GridItem * */ int AddACrater(int, int);

  public:
    void InitLawnMowers();

  public:
    bool IsPlantInCursor();

  public:
    void HighlightPlantsForMouse(int, int);

  public:
    void ClearFogAroundPlant(Plant *, int);

  public:
    void RemoveParticleByType(ParticleEffect);

  public:
    /* GridItem * */ int GetScaryPotAt(int, int);

  public:
    void PuzzleSaveStreak();

  public:
    void ClearAdviceImmediately();

  public:
    bool IsFinalScaryPotterStage();

  public:
    void DisplayAdviceAgain(const std::string &, MessageStyle, AdviceType);

  public:
    /* GridItem * */ int GetSquirrelAt(int, int);

  public:
    /* GridItem * */ int GetZenToolAt(int, int);

  public:
    bool IsPlantInGoldWateringCanRange(int, int, Plant *);

  public:
    bool StageHasZombieWalkInFromRight();

  public:
    void PlaceRake();

  public:
    /* GridItem * */ int GetRake();

  public:
    bool IsScaryPotterDaveTalking();

  public:
    Zombie *GetWinningZombie();

  public:
    void ResetFPSStats();

  public:
    int CountEmptyPotsOrLilies(SeedType);

  public:
    /* GridItem * */ int GetGridItemAt(GridItemType, int, int);

  public:
    bool ProgressMeterHasFlags();

  public:
    bool IsLastStandFinalStage();

  public:
    int GetNumWavesPerFlag();

  public:
    int GetCurrentPlantCost(SeedType, SeedType);

  public:
    bool PlantUsesAcceleratedPricing(SeedType);

  public:
    void FreezeEffectsForCutscene(bool);

  public:
    void LoadBackgroundImages();

  public:
    bool CanUseGameObject(GameObjectType);

  public:
    void SetMustacheMode(bool);

  public:
    int CountCoinByType(CoinType);

  public:
    void SetSuperMowerMode(bool);

  public:
    void DrawZenWheelBarrowButton(Sexy::Graphics *, int);

  public:
    void DrawZenButtons(Sexy::Graphics *);

  public:
    void OffsetYForPlanting(int &, SeedType);

  public:
    void SetFutureMode(bool);

  public:
    void SetPinataMode(bool);

  public:
    void SetDaisyMode(bool);

  public:
    void SetSukhbirMode(bool);

  public:
    bool MouseHitTestPlant(int, int, /* HitResult * */ int);

  public:
    Board &operator=(const Board &);

  public:
    // virtual void *__vecDelDtor(unsigned int);

  public:
    static bool CanZombieSpawnOnLevel(ZombieType, int);

  public:
    static int MakeRenderOrder(RenderLayer, int, int);

  public:
    static bool IsZombieTypePoolOnly(ZombieType);
};

#endif // __BOARD_H__