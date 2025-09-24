#pragma once

#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Attachment.h"
#include "GameObject.h"
#include "Plant.h"

class GameObject;
class Plant;

enum BossPart : int
{
    BOSS_PART_BACK_LEG = 0x0000,
    BOSS_PART_FRONT_LEG = 0x0001,
    BOSS_PART_MAIN = 0x0002,
    BOSS_PART_BACK_ARM = 0x0003,
    BOSS_PART_FIREBALL = 0x0004,
};

enum HelmType : int
{
    HELMTYPE_NONE = 0x0000,
    HELMTYPE_TRAFFIC_CONE = 0x0001,
    HELMTYPE_PAIL = 0x0002,
    HELMTYPE_FOOTBALL = 0x0003,
    HELMTYPE_DIGGER = 0x0004,
    HELMTYPE_REDEYES = 0x0005,
    HELMTYPE_HEADBAND = 0x0006,
    HELMTYPE_BOBSLED = 0x0007,
    HELMTYPE_WALLNUT = 0x0008,
    HELMTYPE_TALLNUT = 0x0009,
};

enum ShieldType : int
{
    SHIELDTYPE_NONE = 0x0000,
    SHIELDTYPE_DOOR = 0x0001,
    SHIELDTYPE_NEWSPAPER = 0x0002,
    SHIELDTYPE_LADDER = 0x0003,
};

enum ZombieAttackType : int
{
    ATTACKTYPE_CHEW = 0x0000,
    ATTACKTYPE_DRIVE_OVER = 0x0001,
    ATTACKTYPE_VAULT = 0x0002,
    ATTACKTYPE_LADDER = 0x0003,
};

enum ZombiePhase : int
{
    PHASE_ZOMBIE_NORMAL = 0x0000,
    PHASE_ZOMBIE_DYING = 0x0001,
    PHASE_ZOMBIE_BURNED = 0x0002,
    PHASE_ZOMBIE_MOWERED = 0x0003,
    PHASE_BUNGEE_DIVING = 0x0004,
    PHASE_BUNGEE_DIVING_SCREAMING = 0x0005,
    PHASE_BUNGEE_AT_BOTTOM = 0x0006,
    PHASE_BUNGEE_GRABBING = 0x0007,
    PHASE_BUNGEE_RISING = 0x0008,
    PHASE_BUNGEE_HIT_OUCHY = 0x0009,
    PHASE_BUNGEE_CUTSCENE = 0x000a,
    PHASE_POLEVAULTER_PRE_VAULT = 0x000b,
    PHASE_POLEVAULTER_IN_VAULT = 0x000c,
    PHASE_POLEVAULTER_POST_VAULT = 0x000d,
    PHASE_RISING_FROM_GRAVE = 0x000e,
    PHASE_JACK_IN_THE_BOX_RUNNING = 0x000f,
    PHASE_JACK_IN_THE_BOX_POPPING = 0x0010,
    PHASE_BOBSLED_SLIDING = 0x0011,
    PHASE_BOBSLED_BOARDING = 0x0012,
    PHASE_BOBSLED_CRASHING = 0x0013,
    PHASE_POGO_BOUNCING = 0x0014,
    PHASE_POGO_HIGH_BOUNCE_1 = 0x0015,
    PHASE_POGO_HIGH_BOUNCE_2 = 0x0016,
    PHASE_POGO_HIGH_BOUNCE_3 = 0x0017,
    PHASE_POGO_HIGH_BOUNCE_4 = 0x0018,
    PHASE_POGO_HIGH_BOUNCE_5 = 0x0019,
    PHASE_POGO_HIGH_BOUNCE_6 = 0x001a,
    PHASE_POGO_FORWARD_BOUNCE_2 = 0x001b,
    PHASE_POGO_FORWARD_BOUNCE_7 = 0x001c,
    PHASE_NEWSPAPER_READING = 0x001d,
    PHASE_NEWSPAPER_MADDENING = 0x001e,
    PHASE_NEWSPAPER_MAD = 0x001f,
    PHASE_DIGGER_TUNNELING = 0x0020,
    PHASE_DIGGER_RISING = 0x0021,
    PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE = 0x0022,
    PHASE_DIGGER_RISE_WITHOUT_AXE = 0x0023,
    PHASE_DIGGER_STUNNED = 0x0024,
    PHASE_DIGGER_WALKING = 0x0025,
    PHASE_DIGGER_WALKING_WITHOUT_AXE = 0x0026,
    PHASE_DIGGER_CUTSCENE = 0x0027,
    PHASE_DANCER_DANCING_IN = 0x0028,
    PHASE_DANCER_SNAPPING_FINGERS = 0x0029,
    PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT = 0x002a,
    PHASE_DANCER_SNAPPING_FINGERS_HOLD = 0x002b,
    PHASE_DANCER_DANCING_LEFT = 0x002c,
    PHASE_DANCER_WALK_TO_RAISE = 0x002d,
    PHASE_DANCER_RAISE_LEFT_1 = 0x002e,
    PHASE_DANCER_RAISE_RIGHT_1 = 0x002f,
    PHASE_DANCER_RAISE_LEFT_2 = 0x0030,
    PHASE_DANCER_RAISE_RIGHT_2 = 0x0031,
    PHASE_DANCER_RISING = 0x0032,
    PHASE_DOLPHIN_WALKING = 0x0033,
    PHASE_DOLPHIN_INTO_POOL = 0x0034,
    PHASE_DOLPHIN_RIDING = 0x0035,
    PHASE_DOLPHIN_IN_JUMP = 0x0036,
    PHASE_DOLPHIN_WALKING_IN_POOL = 0x0037,
    PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN = 0x0038,
    PHASE_SNORKEL_WALKING = 0x0039,
    PHASE_SNORKEL_INTO_POOL = 0x003a,
    PHASE_SNORKEL_WALKING_IN_POOL = 0x003b,
    PHASE_SNORKEL_UP_TO_EAT = 0x003c,
    PHASE_SNORKEL_EATING_IN_POOL = 0x003d,
    PHASE_SNORKEL_DOWN_FROM_EAT = 0x003e,
    PHASE_ZOMBIQUARIUM_ACCEL = 0x003f,
    PHASE_ZOMBIQUARIUM_DRIFT = 0x0040,
    PHASE_ZOMBIQUARIUM_BACK_AND_FORTH = 0x0041,
    PHASE_ZOMBIQUARIUM_BITE = 0x0042,
    PHASE_CATAPULT_LAUNCHING = 0x0043,
    PHASE_CATAPULT_RELOADING = 0x0044,
    PHASE_GARGANTUAR_THROWING = 0x0045,
    PHASE_GARGANTUAR_SMASHING = 0x0046,
    PHASE_IMP_GETTING_THROWN = 0x0047,
    PHASE_IMP_LANDING = 0x0048,
    PHASE_BALLOON_FLYING = 0x0049,
    PHASE_BALLOON_POPPING = 0x004a,
    PHASE_BALLOON_WALKING = 0x004b,
    PHASE_LADDER_CARRYING = 0x004c,
    PHASE_LADDER_PLACING = 0x004d,
    PHASE_BOSS_ENTER = 0x004e,
    PHASE_BOSS_IDLE = 0x004f,
    PHASE_BOSS_SPAWNING = 0x0050,
    PHASE_BOSS_STOMPING = 0x0051,
    PHASE_BOSS_BUNGEES_ENTER = 0x0052,
    PHASE_BOSS_BUNGEES_DROP = 0x0053,
    PHASE_BOSS_BUNGEES_LEAVE = 0x0054,
    PHASE_BOSS_DROP_RV = 0x0055,
    PHASE_BOSS_HEAD_ENTER = 0x0056,
    PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT = 0x0057,
    PHASE_BOSS_HEAD_IDLE_AFTER_SPIT = 0x0058,
    PHASE_BOSS_HEAD_SPIT = 0x0059,
    PHASE_BOSS_HEAD_LEAVE = 0x005a,
    PHASE_YETI_RUNNING = 0x005b,
    PHASE_SQUASH_PRE_LAUNCH = 0x005c,
    PHASE_SQUASH_RISING = 0x005d,
    PHASE_SQUASH_FALLING = 0x005e,
    PHASE_SQUASH_DONE_FALLING = 0x005f,
};

enum ZombieHeight : int
{
    HEIGHT_ZOMBIE_NORMAL = 0x0000,
    HEIGHT_IN_TO_POOL = 0x0001,
    HEIGHT_OUT_OF_POOL = 0x0002,
    HEIGHT_DRAGGED_UNDER = 0x0003,
    HEIGHT_UP_TO_HIGH_GROUND = 0x0004,
    HEIGHT_DOWN_OFF_HIGH_GROUND = 0x0005,
    HEIGHT_UP_LADDER = 0x0006,
    HEIGHT_FALLING = 0x0007,
    HEIGHT_IN_TO_CHIMNEY = 0x0008,
    HEIGHT_GETTING_BUNGEE_DROPPED = 0x0009,
    HEIGHT_ZOMBIQUARIUM = 0x000a,
};

#ifndef E_PLANT_ID
#define E_PLANT_ID
enum PlantID : int
{
    PLANTID_NULL = 0x0000,
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

#ifndef E_ZOMBIE_ID
#define E_ZOMBIE_ID
enum ZombieID : int
{
    ZOMBIEID_NULL = 0x0000,
};
#endif

#ifndef E_REANIMATION_ID
#define E_REANIMATION_ID
enum ReanimationID : int
{
    REANIMATIONID_NULL = 0x0000,
};
#endif

#ifndef E_PARTICLE_EFFECT
#define E_PARTICLE_EFFECT
enum ParticleEffect : int
{
    PARTICLE_NONE = -1,
    PARTICLE_MELONSPLASH = 0x0000,
    PARTICLE_WINTERMELON = 0x0001,
    PARTICLE_FUMECLOUD = 0x0002,
    PARTICLE_POPCORNSPLASH = 0x0003,
    PARTICLE_POWIE = 0x0004,
    PARTICLE_JACKEXPLODE = 0x0005,
    PARTICLE_ZOMBIE_HEAD = 0x0006,
    PARTICLE_ZOMBIE_ARM = 0x0007,
    PARTICLE_ZOMBIE_TRAFFIC_CONE = 0x0008,
    PARTICLE_ZOMBIE_PAIL = 0x0009,
    PARTICLE_ZOMBIE_HELMET = 0x000a,
    PARTICLE_ZOMBIE_FLAG = 0x000b,
    PARTICLE_ZOMBIE_DOOR = 0x000c,
    PARTICLE_ZOMBIE_NEWSPAPER = 0x000d,
    PARTICLE_ZOMBIE_HEADLIGHT = 0x000e,
    PARTICLE_POW = 0x000f,
    PARTICLE_ZOMBIE_POGO = 0x0010,
    PARTICLE_ZOMBIE_NEWSPAPER_HEAD = 0x0011,
    PARTICLE_ZOMBIE_BALLOON_HEAD = 0x0012,
    PARTICLE_SOD_ROLL = 0x0013,
    PARTICLE_GRAVE_STONE_RISE = 0x0014,
    PARTICLE_PLANTING = 0x0015,
    PARTICLE_PLANTING_POOL = 0x0016,
    PARTICLE_ZOMBIE_RISE = 0x0017,
    PARTICLE_GRAVE_BUSTER = 0x0018,
    PARTICLE_GRAVE_BUSTER_DIE = 0x0019,
    PARTICLE_POOL_SPLASH = 0x001a,
    PARTICLE_ICE_SPARKLE = 0x001b,
    PARTICLE_SEED_PACKET = 0x001c,
    PARTICLE_TALL_NUT_BLOCK = 0x001d,
    PARTICLE_DOOM = 0x001e,
    PARTICLE_DIGGER_RISE = 0x001f,
    PARTICLE_DIGGER_TUNNEL = 0x0020,
    PARTICLE_DANCER_RISE = 0x0021,
    PARTICLE_POOL_SPARKLY = 0x0022,
    PARTICLE_WALLNUT_EAT_SMALL = 0x0023,
    PARTICLE_WALLNUT_EAT_LARGE = 0x0024,
    PARTICLE_PEA_SPLAT = 0x0025,
    PARTICLE_SPIKE_SPLAT = 0x0026,
    PARTICLE_BUTTER_SPLAT = 0x0027,
    PARTICLE_CABBAGE_SPLAT = 0x0028,
    PARTICLE_PUFF_SPLAT = 0x0029,
    PARTICLE_STAR_SPLAT = 0x002a,
    PARTICLE_ICE_TRAP = 0x002b,
    PARTICLE_SNOWPEA_SPLAT = 0x002c,
    PARTICLE_SNOWPEA_PUFF = 0x002d,
    PARTICLE_SNOWPEA_TRAIL = 0x002e,
    PARTICLE_LANTERN_SHINE = 0x002f,
    PARTICLE_SEED_PACKET_PICKUP = 0x0030,
    PARTICLE_POTATO_MINE = 0x0031,
    PARTICLE_POTATO_MINE_RISE = 0x0032,
    PARTICLE_PUFFSHROOM_TRAIL = 0x0033,
    PARTICLE_PUFFSHROOM_MUZZLE = 0x0034,
    PARTICLE_SEED_PACKET_FLASH = 0x0035,
    PARTICLE_WHACK_A_ZOMBIE_RISE = 0x0036,
    PARTICLE_ZOMBIE_LADDER = 0x0037,
    PARTICLE_UMBRELLA_REFLECT = 0x0038,
    PARTICLE_SEED_PACKET_PICK = 0x0039,
    PARTICLE_ICE_TRAP_ZOMBIE = 0x003a,
    PARTICLE_ICE_TRAP_RELEASE = 0x003b,
    PARTICLE_ZAMBONI_SMOKE = 0x003c,
    PARTICLE_GLOOMCLOUD = 0x003d,
    PARTICLE_ZOMBIE_POGO_HEAD = 0x003e,
    PARTICLE_ZAMBONI_TIRE = 0x003f,
    PARTICLE_ZAMBONI_EXPLOSION = 0x0040,
    PARTICLE_ZAMBONI_EXPLOSION2 = 0x0041,
    PARTICLE_CATAPULT_EXPLOSION = 0x0042,
    PARTICLE_MOWER_CLOUD = 0x0043,
    PARTICLE_BOSS_ICE_BALL = 0x0044,
    PARTICLE_BLASTMARK = 0x0045,
    PARTICLE_COIN_PICKUP_ARROW = 0x0046,
    PARTICLE_PRESENT_PICKUP = 0x0047,
    PARTICLE_IMITATER_MORPH = 0x0048,
    PARTICLE_MOWERED_ZOMBIE_HEAD = 0x0049,
    PARTICLE_MOWERED_ZOMBIE_ARM = 0x004a,
    PARTICLE_ZOMBIE_HEAD_POOL = 0x004b,
    PARTICLE_ZOMBIE_BOSS_FIREBALL = 0x004c,
    PARTICLE_FIREBALL_DEATH = 0x004d,
    PARTICLE_ICEBALL_DEATH = 0x004e,
    PARTICLE_ICEBALL_TRAIL = 0x004f,
    PARTICLE_FIREBALL_TRAIL = 0x0050,
    PARTICLE_BOSS_EXPLOSION = 0x0051,
    PARTICLE_SCREEN_FLASH = 0x0052,
    PARTICLE_TROPHY_SPARKLE = 0x0053,
    PARTICLE_PORTAL_CIRCLE = 0x0054,
    PARTICLE_PORTAL_SQUARE = 0x0055,
    PARTICLE_POTTED_PLANT_GLOW = 0x0056,
    PARTICLE_POTTED_WATER_PLANT_GLOW = 0x0057,
    PARTICLE_POTTED_ZEN_GLOW = 0x0058,
    PARTICLE_MIND_CONTROL = 0x0059,
    PARTICLE_VASE_SHATTER = 0x005a,
    PARTICLE_VASE_SHATTER_LEAF = 0x005b,
    PARTICLE_VASE_SHATTER_ZOMBIE = 0x005c,
    PARTICLE_AWARD_PICKUP_ARROW = 0x005d,
    PARTICLE_ZOMBIE_SEAWEED = 0x005e,
    PARTICLE_ZOMBIE_MUSTACHE = 0x005f,
    PARTICLE_ZOMBIE_FUTURE_GLASSES = 0x0060,
    PARTICLE_PINATA = 0x0061,
    PARTICLE_DUST_SQUASH = 0x0062,
    PARTICLE_DUST_FOOT = 0x0063,
    PARTICLE_DAISY = 0x0064,
    PARTICLE_CREDIT_STROBE = 0x0065,
    PARTICLE_CREDITS_RAYSWIPE = 0x0066,
    PARTICLE_CREDITS_ZOMBIEHEADWIPE = 0x0067,
    PARTICLE_STARBURST = 0x0068,
    PARTICLE_CREDITS_FOG = 0x0069,
    NUM_PARTICLES = 0x006a,
};
#endif

class Zombie : public GameObject
{   /* Size=0x158 */
    /* 0x0000: fields for GameObject */
  /* 0x0024 */ public:
    ZombieType mZombieType;
  /* 0x0028 */ public:
    ZombiePhase mZombiePhase;
  /* 0x002c */ public:
    float mPosX;
  /* 0x0030 */ public:
    float mPosY;
  /* 0x0034 */ public:
    float mVelX;
  /* 0x0038 */ public:
    int mAnimCounter;
  /* 0x003c */ public:
    int mGroanCounter;
  /* 0x0040 */ public:
    int mAnimTicksPerFrame;
  /* 0x0044 */ public:
    int mAnimFrames;
  /* 0x0048 */ public:
    int mFrame;
  /* 0x004c */ public:
    int mPrevFrame;
  /* 0x0050 */ public:
    bool mVariant;
  /* 0x0051 */ public:
    bool mIsEating;
    char pad_0x52[2];
  /* 0x0054 */ public:
    int mJustGotShotCounter;
  /* 0x0058 */ public:
    int mShieldJustGotShotCounter;
  /* 0x005c */ public:
    int mShieldRecoilCounter;
  /* 0x0060 */ public:
    int mZombieAge;
  /* 0x0064 */ public:
    ZombieHeight mZombieHeight;
  /* 0x0068 */ public:
    int mPhaseCounter;
  /* 0x006c */ public:
    int mFromWave;
  /* 0x0070 */ public:
    bool mDroppedLoot;
    char pad_0x71[3];
  /* 0x0074 */ public:
    int mZombieFade;
  /* 0x0078 */ public:
    bool mFlatTires;
    char pad_0x79[3];
  /* 0x007c */ public:
    int mUseLadderCol;
  /* 0x0080 */ public:
    int mTargetCol;
  /* 0x0084 */ public:
    float mAltitude;
  /* 0x0088 */ public:
    bool mHitUmbrella;
    char pad_0x89[3];
  /* 0x008c */ public:
    Sexy::TRect<int> mZombieRect;
  /* 0x009c */ public:
    Sexy::TRect<int> mZombieAttackRect;
  /* 0x00ac */ public:
    int mChilledCounter;
  /* 0x00b0 */ public:
    int mButteredCounter;
  /* 0x00b4 */ public:
    int mIceTrapCounter;
  /* 0x00b8 */ public:
    bool mMindControlled;
  /* 0x00b9 */ public:
    bool mBlowingAway;
  /* 0x00ba */ public:
    bool mHasHead;
  /* 0x00bb */ public:
    bool mHasArm;
  /* 0x00bc */ public:
    bool mHasObject;
  /* 0x00bd */ public:
    bool mInPool;
  /* 0x00be */ public:
    bool mOnHighGround;
  /* 0x00bf */ public:
    bool mYuckyFace;
  /* 0x00c0 */ public:
    int mYuckyFaceCounter;
  /* 0x00c4 */ public:
    HelmType mHelmType;
  /* 0x00c8 */ public:
    int mBodyHealth;
  /* 0x00cc */ public:
    int mBodyMaxHealth;
  /* 0x00d0 */ public:
    int mHelmHealth;
  /* 0x00d4 */ public:
    int mHelmMaxHealth;
  /* 0x00d8 */ public:
    ShieldType mShieldType;
  /* 0x00dc */ public:
    int mShieldHealth;
  /* 0x00e0 */ public:
    int mShieldMaxHealth;
  /* 0x00e4 */ public:
    int mFlyingHealth;
  /* 0x00e8 */ public:
    int mFlyingMaxHealth;
  /* 0x00ec */ public:
    bool mDead;
    char pad_0xed[3];
  /* 0x00f0 */ public:
    ZombieID mRelatedZombieID;
  /* 0x00f4 */ public:
    ZombieID mFollowerZombieID[4];
  /* 0x0104 */ public:
    bool mPlayingSong;
    char pad_0x105[3];
  /* 0x0108 */ public:
    int mParticleOffsetX;
  /* 0x010c */ public:
    int mParticleOffsetY;
  /* 0x0110 */ public:
    AttachmentID mAttachmentID;
  /* 0x0114 */ public:
    int mSummonCounter;
  /* 0x0118 */ public:
    ReanimationID mBodyReanimID;
  /* 0x011c */ public:
    float mScaleZombie;
  /* 0x0120 */ public:
    float mVelZ;
  /* 0x0124 */ public:
    float mOrginalAnimRate;
  /* 0x0128 */ public:
    PlantID mTargetPlantID;
  /* 0x012c */ public:
    int mBossMode;
  /* 0x0130 */ public:
    int mTargetRow;
  /* 0x0134 */ public:
    int mBossBungeeCounter;
  /* 0x0138 */ public:
    int mBossStompCounter;
  /* 0x013c */ public:
    int mBossHeadCounter;
  /* 0x0140 */ public:
    ReanimationID mBossFireBallReanimID;
  /* 0x0144 */ public:
    ReanimationID mSpecialHeadReanimID;
  /* 0x0148 */ public:
    int mFireballRow;
  /* 0x014c */ public:
    bool mIsFireBall;
    char pad_0x14d[3];
  /* 0x0150 */ public:
    ReanimationID mMoweredReanimID;
  /* 0x0154 */ public:
    int mLastPortalX;

  public:
    Zombie(const Zombie &);

  public:
    Zombie();

  public:
    void ZombieInitialize(int, ZombieType, bool, Zombie *, int);

  public:
    ~Zombie();

  public:
    void Animate();

  public:
    void CheckIfPreyCaught();

  public:
    void EatZombie(Zombie *);

  public:
    void EatPlant(Plant *);

  public:
    void Update();

  public:
    void DieNoLoot();

  public:
    void DieWithLoot();

  public:
    void Draw(Sexy::Graphics *);

  public:
    void DrawZombie(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void DrawZombieWithParts(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void DrawZombiePart(Sexy::Graphics *, Sexy::Image *, int, int, /*ZombieDrawPosition & */ int);

  public:
    void DrawBungeeCord(Sexy::Graphics *, int, int);

  public:
    void TakeDamage(int, unsigned int);

  public:
    void SetRow(int);

  public:
    float GetPosYBasedOnRow(int);

  public:
    void ApplyChill(bool);

  public:
    void UpdateZombieBungee();

  public:
    void BungeeLanding();

  public:
    bool EffectedByDamage(unsigned int);

  public:
    void PickRandomSpeed();

  public:
    void UpdateZombiePolevaulter();

  public:
    void UpdateZombieDolphinRider();

  public:
    void PickBungeeZombieTarget(int);

  public:
    int CountBungeesTargetingSunFlowers();

  public:
    Plant *FindPlantTarget(ZombieAttackType);

  public:
    void CheckSquish(ZombieAttackType);

  public:
    void RiseFromGrave(int, int);

  public:
    void UpdateZombieRiseFromGrave();

  public:
    void UpdateDamageStates(unsigned int);

  public:
    void UpdateZombiePool();

  public:
    void CheckForPool();

  public:
    void GetDrawPos(/*ZombieDrawPosition & */ int);

  public:
    void UpdateZombieHighGround();

  public:
    void CheckForHighGround();

  public:
    bool IsOnHighGround();

  public:
    void DropLoot();

  public:
    bool TrySpawnLevelAward();

  public:
    void StartZombieSound();

  public:
    void StopZombieSound();

  public:
    void UpdateZombieJackInTheBox();

  public:
    void DrawZombieHead(Sexy::Graphics *, /*ZombieDrawPosition & */ int, int);

  public:
    void UpdateZombiePosition();

  public:
    Sexy::TRect<int> GetZombieRect();

  public:
    Sexy::TRect<int> GetZombieAttackRect();

  public:
    void UpdateZombieWalking();

  public:
    void UpdateZombieBobsled();

  public:
    void BobsledCrash();

  public:
    Plant *IsStandingOnSpikeweed();

  public:
    void CheckForZombieStep();

  public:
    void CountExpectedMowers();

  public:
    void OverrideParticleColor(/* TodParticleSystem * */ int);

  public:
    void OverrideParticleScale(/* TodParticleSystem * */ int);

  public:
    void PoolSplash(bool);

  public:
    void UpdateZombieFlyer();

  public:
    void UpdateZombiePogo();

  public:
    void UpdateZombieNewspaper();

  public:
    void LandFlyer(unsigned int);

  public:
    void UpdateZombieDigger();

  public:
    bool IsWalkingBackwards();

  public:
    /* TodParticleSystem * */ int AddAttachedParticle(int, int, ParticleEffect);

  public:
    void PogoBreak(unsigned int);

  public:
    void UpdateZombieFalling();

  public:
    void UpdateZombieDancer();

  public:
    ZombieID SummonBackupDancer(int, int);

  public:
    void SummonBackupDancers();

  public:
    int GetDancerFrame();

  public:
    void BungeeStealTarget();

  public:
    void UpdateYuckyFace();

  public:
    void DrawIceTrap(Sexy::Graphics *, /*ZombieDrawPosition & */ int, bool);

  public:
    void HitIceTrap();

  public:
    int GetHelmDamageIndex();

  public:
    int GetShieldDamageIndex();

  public:
    void DrawReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ int, int);

  public:
    void UpdatePlaying();

  public:
    bool NeedsMoreBackupDancers();

  public:
    void ConvertToNormalZombie();

  public:
    void UpdateDancerWalking();

  public:
    void StartEating();

  public:
    void StopEating();

  public:
    void UpdateAnimSpeed();

  public:
    void ReanimShowPrefix(const char *, int);

  public:
    void PlayDeathAnim(unsigned int);

  public:
    void UpdateDeath();

  public:
    void DrawShadow(Sexy::Graphics *);

  public:
    bool HasShadow();

  public:
    /* Reanimation * */ int LoadReanim(ReanimationType);

  public:
    int TakeFlyingDamage(int, unsigned int);

  public:
    int TakeShieldDamage(int, unsigned int);

  public:
    int TakeHelmDamage(int, unsigned int);

  public:
    void TakeBodyDamage(int, unsigned int);

  public:
    void AttachShield();

  public:
    void DetachShield();

  public:
    void UpdateReanim();

  public:
    void GetTrackPosition(const char *, float &, float &);

  public:
    void LoadPlainZombieReanim();

  public:
    void ShowDoorArms(bool);

  public:
    void ReanimShowTrack(const char *, int);

  public:
    void PlayZombieAppearSound();

  public:
    void StartMindControlled();

  public:
    bool IsFlying();

  public:
    void DropHead(unsigned int);

  public:
    bool CanTargetPlant(Plant *, ZombieAttackType);

  public:
    void UpdateZombieCatapult();

  public:
    Plant *FindCatapultTarget();

  public:
    void ZombieCatapultFire(Plant *);

  public:
    void UpdateClimbingLadder();

  public:
    void UpdateZombieGargantuar();

  public:
    int GetBodyDamageIndex();

  public:
    void ApplyBurn();

  public:
    void UpdateBurn();

  public:
    bool ZombieNotWalking();

  public:
    Zombie *FindZombieTarget();

  public:
    void PlayZombieReanim(const char *, ReanimLoopType, int, float);

  public:
    void UpdateZombieBackupDancer();

  public:
    ZombiePhase GetDancerPhase();

  public:
    bool IsMovingAtChilledSpeed();

  public:
    void StartWalkAnim(int);

  public:
    /* Reanimation * */ int AddAttachedReanim(int, int, ReanimationType);

  public:
    void DragUnder();

  public:
    bool IsOnBoard();

  public:
    void DrawButter(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    bool IsImmobilizied();

  public:
    void ApplyButter();

  public:
    float ZombieTargetLeadX(float);

  public:
    void UpdateZombieImp();

  public:
    void SquishAllInSquare(int, int, ZombieAttackType);

  public:
    void RemoveIceTrap();

  public:
    bool IsBouncingPogo();

  public:
    int GetBobsledPosition();

  public:
    void DrawBobsledReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ int, bool);

  public:
    void BobsledDie();

  public:
    void BobsledBurn();

  public:
    bool IsBobsledTeamWithSled();

  public:
    bool CanBeFrozen();

  public:
    bool CanBeChilled();

  public:
    void UpdateZombieSnorkel();

  public:
    void ReanimIgnoreClipRect(const char *, bool);

  public:
    void SetAnimRate(float);

  public:
    void ApplyAnimRate(float);

  public:
    bool IsDeadOrDying();

  public:
    void DrawDancerReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void DrawBungeeReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void DrawBungeeTarget(Sexy::Graphics *);

  public:
    void BungeeDie();

  public:
    void ZamboniDeath(unsigned int);

  public:
    void CatapultDeath(unsigned int);

  public:
    bool SetupDrawZombieWon(Sexy::Graphics *);

  public:
    void WalkIntoHouse();

  public:
    void UpdateZamboni();

  public:
    void UpdateZombieChimney();

  public:
    void UpdateLadder();

  public:
    void DropArm(unsigned int);

  public:
    bool CanLoseBodyParts();

  public:
    void DropHelm(unsigned int);

  public:
    void DropShield(unsigned int);

  public:
    void ReanimReenableClipping();

  public:
    void UpdateBoss();

  public:
    void BossPlayIdle();

  public:
    void BossRVLanding();

  public:
    void BossStompContact();

  public:
    bool BossAreBungeesDone();

  public:
    void BossBungeeSpawn();

  public:
    void BossSpawnAttack();

  public:
    void BossBungeeAttack();

  public:
    void BossRVAttack();

  public:
    void BossSpawnContact();

  public:
    void BossBungeeLeave();

  public:
    void BossStompAttack();

  public:
    bool BossCanStompRow(int);

  public:
    void BossDie();

  public:
    void BossHeadAttack();

  public:
    void BossHeadSpitContact();

  public:
    void BossHeadSpit();

  public:
    void UpdateBossFireball();

  public:
    void BossDestroyFireball();

  public:
    void BossDestroyIceballInRow(int);

  public:
    void DiggerLoseAxe();

  public:
    void BungeeDropZombie(Zombie *, int, int);

  public:
    void ShowYuckyFace(bool);

  public:
    void AnimateChewSound();

  public:
    void AnimateChewEffect();

  public:
    void UpdateActions();

  public:
    void CheckForBoardEdge();

  public:
    void UpdateYeti();

  public:
    void DrawBossPart(Sexy::Graphics *, BossPart);

  public:
    void BossSetupReanim();

  public:
    void MowDown();

  public:
    void UpdateMowered();

  public:
    void DropFlag();

  public:
    void DropPole();

  public:
    void DrawBossBackArm(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void BossStartDeath();

  public:
    void RemoveColdEffects();

  public:
    void BossHeadSpitEffect();

  public:
    void DrawBossFireBall(Sexy::Graphics *, /*ZombieDrawPosition & */ int);

  public:
    void UpdateZombiePeaHead();

  public:
    void UpdateZombieJalapenoHead();

  public:
    void ApplyBossSmokeParticles(bool);

  public:
    void UpdateZombiquarium();

  public:
    bool ZombiquariumFindClosestBrain();

  public:
    void UpdateZombieGatlingHead();

  public:
    void UpdateZombieSquashHead();

  public:
    bool IsTanglekelpTarget();

  public:
    bool HasYuckyFaceImage();

  public:
    bool IsTangleKelpTarget();

  public:
    bool IsFireResistant();

  public:
    void EnableMustache(bool);

  public:
    void EnableFuture(bool);

  public:
    void BungeeDropPlant();

  public:
    void RemoveButter();

  public:
    void BalloonPropellerHatSpin(bool);

  public:
    void DoDaisies();

  public:
    // void *__vecDelDtor(unsigned int);

  public:
    static void SetupDoorArms(Reanimation *, bool);

  public:
    static void SetupReanimLayers(Reanimation *, ZombieType);

  public:
    static void PreloadZombieResources(ZombieType);
};

#endif // __ZOMBIE_H__