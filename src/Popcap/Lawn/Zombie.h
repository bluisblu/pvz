#pragma once

#include "TodLib/Attachment.h"
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GameObject.h"
#include "LawnApp.h"
#include "Plant.h"
#include "TodLib/Attachment.h"

class Attachment;
class GameObject;
class Plant;
class LawnApp;

enum BossPart : int
{
    BOSS_PART_BACK_LEG  = 0x0000,
    BOSS_PART_FRONT_LEG = 0x0001,
    BOSS_PART_MAIN      = 0x0002,
    BOSS_PART_BACK_ARM  = 0x0003,
    BOSS_PART_FIREBALL  = 0x0004,
};

enum HelmType : int
{
    HELMTYPE_NONE         = 0x0000,
    HELMTYPE_TRAFFIC_CONE = 0x0001,
    HELMTYPE_PAIL         = 0x0002,
    HELMTYPE_FOOTBALL     = 0x0003,
    HELMTYPE_DIGGER       = 0x0004,
    HELMTYPE_REDEYES      = 0x0005,
    HELMTYPE_HEADBAND     = 0x0006,
    HELMTYPE_BOBSLED      = 0x0007,
    HELMTYPE_WALLNUT      = 0x0008,
    HELMTYPE_TALLNUT      = 0x0009,
};

enum ShieldType : int
{
    SHIELDTYPE_NONE      = 0x0000,
    SHIELDTYPE_DOOR      = 0x0001,
    SHIELDTYPE_NEWSPAPER = 0x0002,
    SHIELDTYPE_LADDER    = 0x0003,
};

enum ZombieAttackType : int
{
    ATTACKTYPE_CHEW       = 0x0000,
    ATTACKTYPE_DRIVE_OVER = 0x0001,
    ATTACKTYPE_VAULT      = 0x0002,
    ATTACKTYPE_LADDER     = 0x0003,
};

enum ZombiePhase : int
{
    PHASE_ZOMBIE_NORMAL                      = 0x0000,
    PHASE_ZOMBIE_DYING                       = 0x0001,
    PHASE_ZOMBIE_BURNED                      = 0x0002,
    PHASE_ZOMBIE_MOWERED                     = 0x0003,
    PHASE_BUNGEE_DIVING                      = 0x0004,
    PHASE_BUNGEE_DIVING_SCREAMING            = 0x0005,
    PHASE_BUNGEE_AT_BOTTOM                   = 0x0006,
    PHASE_BUNGEE_GRABBING                    = 0x0007,
    PHASE_BUNGEE_RISING                      = 0x0008,
    PHASE_BUNGEE_HIT_OUCHY                   = 0x0009,
    PHASE_BUNGEE_CUTSCENE                    = 0x000a,
    PHASE_POLEVAULTER_PRE_VAULT              = 0x000b,
    PHASE_POLEVAULTER_IN_VAULT               = 0x000c,
    PHASE_POLEVAULTER_POST_VAULT             = 0x000d,
    PHASE_RISING_FROM_GRAVE                  = 0x000e,
    PHASE_JACK_IN_THE_BOX_RUNNING            = 0x000f,
    PHASE_JACK_IN_THE_BOX_POPPING            = 0x0010,
    PHASE_BOBSLED_SLIDING                    = 0x0011,
    PHASE_BOBSLED_BOARDING                   = 0x0012,
    PHASE_BOBSLED_CRASHING                   = 0x0013,
    PHASE_POGO_BOUNCING                      = 0x0014,
    PHASE_POGO_HIGH_BOUNCE_1                 = 0x0015,
    PHASE_POGO_HIGH_BOUNCE_2                 = 0x0016,
    PHASE_POGO_HIGH_BOUNCE_3                 = 0x0017,
    PHASE_POGO_HIGH_BOUNCE_4                 = 0x0018,
    PHASE_POGO_HIGH_BOUNCE_5                 = 0x0019,
    PHASE_POGO_HIGH_BOUNCE_6                 = 0x001a,
    PHASE_POGO_FORWARD_BOUNCE_2              = 0x001b,
    PHASE_POGO_FORWARD_BOUNCE_7              = 0x001c,
    PHASE_NEWSPAPER_READING                  = 0x001d,
    PHASE_NEWSPAPER_MADDENING                = 0x001e,
    PHASE_NEWSPAPER_MAD                      = 0x001f,
    PHASE_DIGGER_TUNNELING                   = 0x0020,
    PHASE_DIGGER_RISING                      = 0x0021,
    PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE = 0x0022,
    PHASE_DIGGER_RISE_WITHOUT_AXE            = 0x0023,
    PHASE_DIGGER_STUNNED                     = 0x0024,
    PHASE_DIGGER_WALKING                     = 0x0025,
    PHASE_DIGGER_WALKING_WITHOUT_AXE         = 0x0026,
    PHASE_DIGGER_CUTSCENE                    = 0x0027,
    PHASE_DANCER_DANCING_IN                  = 0x0028,
    PHASE_DANCER_SNAPPING_FINGERS            = 0x0029,
    PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT = 0x002a,
    PHASE_DANCER_SNAPPING_FINGERS_HOLD       = 0x002b,
    PHASE_DANCER_DANCING_LEFT                = 0x002c,
    PHASE_DANCER_WALK_TO_RAISE               = 0x002d,
    PHASE_DANCER_RAISE_LEFT_1                = 0x002e,
    PHASE_DANCER_RAISE_RIGHT_1               = 0x002f,
    PHASE_DANCER_RAISE_LEFT_2                = 0x0030,
    PHASE_DANCER_RAISE_RIGHT_2               = 0x0031,
    PHASE_DANCER_RISING                      = 0x0032,
    PHASE_DOLPHIN_WALKING                    = 0x0033,
    PHASE_DOLPHIN_INTO_POOL                  = 0x0034,
    PHASE_DOLPHIN_RIDING                     = 0x0035,
    PHASE_DOLPHIN_IN_JUMP                    = 0x0036,
    PHASE_DOLPHIN_WALKING_IN_POOL            = 0x0037,
    PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN    = 0x0038,
    PHASE_SNORKEL_WALKING                    = 0x0039,
    PHASE_SNORKEL_INTO_POOL                  = 0x003a,
    PHASE_SNORKEL_WALKING_IN_POOL            = 0x003b,
    PHASE_SNORKEL_UP_TO_EAT                  = 0x003c,
    PHASE_SNORKEL_EATING_IN_POOL             = 0x003d,
    PHASE_SNORKEL_DOWN_FROM_EAT              = 0x003e,
    PHASE_ZOMBIQUARIUM_ACCEL                 = 0x003f,
    PHASE_ZOMBIQUARIUM_DRIFT                 = 0x0040,
    PHASE_ZOMBIQUARIUM_BACK_AND_FORTH        = 0x0041,
    PHASE_ZOMBIQUARIUM_BITE                  = 0x0042,
    PHASE_CATAPULT_LAUNCHING                 = 0x0043,
    PHASE_CATAPULT_RELOADING                 = 0x0044,
    PHASE_GARGANTUAR_THROWING                = 0x0045,
    PHASE_GARGANTUAR_SMASHING                = 0x0046,
    PHASE_IMP_GETTING_THROWN                 = 0x0047,
    PHASE_IMP_LANDING                        = 0x0048,
    PHASE_BALLOON_FLYING                     = 0x0049,
    PHASE_BALLOON_POPPING                    = 0x004a,
    PHASE_BALLOON_WALKING                    = 0x004b,
    PHASE_LADDER_CARRYING                    = 0x004c,
    PHASE_LADDER_PLACING                     = 0x004d,
    PHASE_BOSS_ENTER                         = 0x004e,
    PHASE_BOSS_IDLE                          = 0x004f,
    PHASE_BOSS_SPAWNING                      = 0x0050,
    PHASE_BOSS_STOMPING                      = 0x0051,
    PHASE_BOSS_BUNGEES_ENTER                 = 0x0052,
    PHASE_BOSS_BUNGEES_DROP                  = 0x0053,
    PHASE_BOSS_BUNGEES_LEAVE                 = 0x0054,
    PHASE_BOSS_DROP_RV                       = 0x0055,
    PHASE_BOSS_HEAD_ENTER                    = 0x0056,
    PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT         = 0x0057,
    PHASE_BOSS_HEAD_IDLE_AFTER_SPIT          = 0x0058,
    PHASE_BOSS_HEAD_SPIT                     = 0x0059,
    PHASE_BOSS_HEAD_LEAVE                    = 0x005a,
    PHASE_YETI_RUNNING                       = 0x005b,
    PHASE_SQUASH_PRE_LAUNCH                  = 0x005c,
    PHASE_SQUASH_RISING                      = 0x005d,
    PHASE_SQUASH_FALLING                     = 0x005e,
    PHASE_SQUASH_DONE_FALLING                = 0x005f,
};

enum ZombieHeight : int
{
    HEIGHT_ZOMBIE_NORMAL          = 0x0000,
    HEIGHT_IN_TO_POOL             = 0x0001,
    HEIGHT_OUT_OF_POOL            = 0x0002,
    HEIGHT_DRAGGED_UNDER          = 0x0003,
    HEIGHT_UP_TO_HIGH_GROUND      = 0x0004,
    HEIGHT_DOWN_OFF_HIGH_GROUND   = 0x0005,
    HEIGHT_UP_LADDER              = 0x0006,
    HEIGHT_FALLING                = 0x0007,
    HEIGHT_IN_TO_CHIMNEY          = 0x0008,
    HEIGHT_GETTING_BUNGEE_DROPPED = 0x0009,
    HEIGHT_ZOMBIQUARIUM           = 0x000a,
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
    PARTICLE_NONE                    = -1,
    PARTICLE_MELONSPLASH             = 0x0000,
    PARTICLE_WINTERMELON             = 0x0001,
    PARTICLE_FUMECLOUD               = 0x0002,
    PARTICLE_POPCORNSPLASH           = 0x0003,
    PARTICLE_POWIE                   = 0x0004,
    PARTICLE_JACKEXPLODE             = 0x0005,
    PARTICLE_ZOMBIE_HEAD             = 0x0006,
    PARTICLE_ZOMBIE_ARM              = 0x0007,
    PARTICLE_ZOMBIE_TRAFFIC_CONE     = 0x0008,
    PARTICLE_ZOMBIE_PAIL             = 0x0009,
    PARTICLE_ZOMBIE_HELMET           = 0x000a,
    PARTICLE_ZOMBIE_FLAG             = 0x000b,
    PARTICLE_ZOMBIE_DOOR             = 0x000c,
    PARTICLE_ZOMBIE_NEWSPAPER        = 0x000d,
    PARTICLE_ZOMBIE_HEADLIGHT        = 0x000e,
    PARTICLE_POW                     = 0x000f,
    PARTICLE_ZOMBIE_POGO             = 0x0010,
    PARTICLE_ZOMBIE_NEWSPAPER_HEAD   = 0x0011,
    PARTICLE_ZOMBIE_BALLOON_HEAD     = 0x0012,
    PARTICLE_SOD_ROLL                = 0x0013,
    PARTICLE_GRAVE_STONE_RISE        = 0x0014,
    PARTICLE_PLANTING                = 0x0015,
    PARTICLE_PLANTING_POOL           = 0x0016,
    PARTICLE_ZOMBIE_RISE             = 0x0017,
    PARTICLE_GRAVE_BUSTER            = 0x0018,
    PARTICLE_GRAVE_BUSTER_DIE        = 0x0019,
    PARTICLE_POOL_SPLASH             = 0x001a,
    PARTICLE_ICE_SPARKLE             = 0x001b,
    PARTICLE_SEED_PACKET             = 0x001c,
    PARTICLE_TALL_NUT_BLOCK          = 0x001d,
    PARTICLE_DOOM                    = 0x001e,
    PARTICLE_DIGGER_RISE             = 0x001f,
    PARTICLE_DIGGER_TUNNEL           = 0x0020,
    PARTICLE_DANCER_RISE             = 0x0021,
    PARTICLE_POOL_SPARKLY            = 0x0022,
    PARTICLE_WALLNUT_EAT_SMALL       = 0x0023,
    PARTICLE_WALLNUT_EAT_LARGE       = 0x0024,
    PARTICLE_PEA_SPLAT               = 0x0025,
    PARTICLE_SPIKE_SPLAT             = 0x0026,
    PARTICLE_BUTTER_SPLAT            = 0x0027,
    PARTICLE_CABBAGE_SPLAT           = 0x0028,
    PARTICLE_PUFF_SPLAT              = 0x0029,
    PARTICLE_STAR_SPLAT              = 0x002a,
    PARTICLE_ICE_TRAP                = 0x002b,
    PARTICLE_SNOWPEA_SPLAT           = 0x002c,
    PARTICLE_SNOWPEA_PUFF            = 0x002d,
    PARTICLE_SNOWPEA_TRAIL           = 0x002e,
    PARTICLE_LANTERN_SHINE           = 0x002f,
    PARTICLE_SEED_PACKET_PICKUP      = 0x0030,
    PARTICLE_POTATO_MINE             = 0x0031,
    PARTICLE_POTATO_MINE_RISE        = 0x0032,
    PARTICLE_PUFFSHROOM_TRAIL        = 0x0033,
    PARTICLE_PUFFSHROOM_MUZZLE       = 0x0034,
    PARTICLE_SEED_PACKET_FLASH       = 0x0035,
    PARTICLE_WHACK_A_ZOMBIE_RISE     = 0x0036,
    PARTICLE_ZOMBIE_LADDER           = 0x0037,
    PARTICLE_UMBRELLA_REFLECT        = 0x0038,
    PARTICLE_SEED_PACKET_PICK        = 0x0039,
    PARTICLE_ICE_TRAP_ZOMBIE         = 0x003a,
    PARTICLE_ICE_TRAP_RELEASE        = 0x003b,
    PARTICLE_ZAMBONI_SMOKE           = 0x003c,
    PARTICLE_GLOOMCLOUD              = 0x003d,
    PARTICLE_ZOMBIE_POGO_HEAD        = 0x003e,
    PARTICLE_ZAMBONI_TIRE            = 0x003f,
    PARTICLE_ZAMBONI_EXPLOSION       = 0x0040,
    PARTICLE_ZAMBONI_EXPLOSION2      = 0x0041,
    PARTICLE_CATAPULT_EXPLOSION      = 0x0042,
    PARTICLE_MOWER_CLOUD             = 0x0043,
    PARTICLE_BOSS_ICE_BALL           = 0x0044,
    PARTICLE_BLASTMARK               = 0x0045,
    PARTICLE_COIN_PICKUP_ARROW       = 0x0046,
    PARTICLE_PRESENT_PICKUP          = 0x0047,
    PARTICLE_IMITATER_MORPH          = 0x0048,
    PARTICLE_MOWERED_ZOMBIE_HEAD     = 0x0049,
    PARTICLE_MOWERED_ZOMBIE_ARM      = 0x004a,
    PARTICLE_ZOMBIE_HEAD_POOL        = 0x004b,
    PARTICLE_ZOMBIE_BOSS_FIREBALL    = 0x004c,
    PARTICLE_FIREBALL_DEATH          = 0x004d,
    PARTICLE_ICEBALL_DEATH           = 0x004e,
    PARTICLE_ICEBALL_TRAIL           = 0x004f,
    PARTICLE_FIREBALL_TRAIL          = 0x0050,
    PARTICLE_BOSS_EXPLOSION          = 0x0051,
    PARTICLE_SCREEN_FLASH            = 0x0052,
    PARTICLE_TROPHY_SPARKLE          = 0x0053,
    PARTICLE_PORTAL_CIRCLE           = 0x0054,
    PARTICLE_PORTAL_SQUARE           = 0x0055,
    PARTICLE_POTTED_PLANT_GLOW       = 0x0056,
    PARTICLE_POTTED_WATER_PLANT_GLOW = 0x0057,
    PARTICLE_POTTED_ZEN_GLOW         = 0x0058,
    PARTICLE_MIND_CONTROL            = 0x0059,
    PARTICLE_VASE_SHATTER            = 0x005a,
    PARTICLE_VASE_SHATTER_LEAF       = 0x005b,
    PARTICLE_VASE_SHATTER_ZOMBIE     = 0x005c,
    PARTICLE_AWARD_PICKUP_ARROW      = 0x005d,
    PARTICLE_ZOMBIE_SEAWEED          = 0x005e,
    PARTICLE_ZOMBIE_MUSTACHE         = 0x005f,
    PARTICLE_ZOMBIE_FUTURE_GLASSES   = 0x0060,
    PARTICLE_PINATA                  = 0x0061,
    PARTICLE_DUST_SQUASH             = 0x0062,
    PARTICLE_DUST_FOOT               = 0x0063,
    PARTICLE_DAISY                   = 0x0064,
    PARTICLE_CREDIT_STROBE           = 0x0065,
    PARTICLE_CREDITS_RAYSWIPE        = 0x0066,
    PARTICLE_CREDITS_ZOMBIEHEADWIPE  = 0x0067,
    PARTICLE_STARBURST               = 0x0068,
    PARTICLE_CREDITS_FOG             = 0x0069,
    NUM_PARTICLES                    = 0x006a,
};
#endif

class Zombie : public GameObject
{   /* Size=0x158 */
    /* 0x0000: fields for GameObject */
  public:
    /* 0x0024 */ ZombieType mZombieType;
    /* 0x0028 */ ZombiePhase mZombiePhase;
    /* 0x002c */ float mPosX;
    /* 0x0030 */ float mPosY;
    /* 0x0034 */ float mVelX;
    /* 0x0038 */ int mAnimCounter;
    /* 0x003c */ int mGroanCounter;
    /* 0x0040 */ int mAnimTicksPerFrame;
    /* 0x0044 */ int mAnimFrames;
    /* 0x0048 */ int mFrame;
    /* 0x004c */ int mPrevFrame;
    /* 0x0050 */ bool mVariant;
    /* 0x0051 */ bool mIsEating;
    char pad_0x52[2];
    /* 0x0054 */ int mJustGotShotCounter;
    /* 0x0058 */ int mShieldJustGotShotCounter;
    /* 0x005c */ int mShieldRecoilCounter;
    /* 0x0060 */ int mZombieAge;
    /* 0x0064 */ ZombieHeight mZombieHeight;
    /* 0x0068 */ int mPhaseCounter;
    /* 0x006c */ int mFromWave;
    /* 0x0070 */ bool mDroppedLoot;
    char pad_0x71[3];
    /* 0x0074 */ int mZombieFade;
    /* 0x0078 */ bool mFlatTires;
    char pad_0x79[3];
    /* 0x007c */ int mUseLadderCol;
    /* 0x0080 */ int mTargetCol;
    /* 0x0084 */ float mAltitude;
    /* 0x0088 */ bool mHitUmbrella;
    char pad_0x89[3];
    /* 0x008c */ Sexy::TRect<int> mZombieRect;
    /* 0x009c */ Sexy::TRect<int> mZombieAttackRect;
    /* 0x00ac */ int mChilledCounter;
    /* 0x00b0 */ int mButteredCounter;
    /* 0x00b4 */ int mIceTrapCounter;
    /* 0x00b8 */ bool mMindControlled;
    /* 0x00b9 */ bool mBlowingAway;
    /* 0x00ba */ bool mHasHead;
    /* 0x00bb */ bool mHasArm;
    /* 0x00bc */ bool mHasObject;
    /* 0x00bd */ bool mInPool;
    /* 0x00be */ bool mOnHighGround;
    /* 0x00bf */ bool mYuckyFace;
    /* 0x00c0 */ int mYuckyFaceCounter;
    /* 0x00c4 */ HelmType mHelmType;
    /* 0x00c8 */ int mBodyHealth;
    /* 0x00cc */ int mBodyMaxHealth;
    /* 0x00d0 */ int mHelmHealth;
    /* 0x00d4 */ int mHelmMaxHealth;
    /* 0x00d8 */ ShieldType mShieldType;
    /* 0x00dc */ int mShieldHealth;
    /* 0x00e0 */ int mShieldMaxHealth;
    /* 0x00e4 */ int mFlyingHealth;
    /* 0x00e8 */ int mFlyingMaxHealth;
    /* 0x00ec */ bool mDead;
    char pad_0xed[3];
    /* 0x00f0 */ ZombieID mRelatedZombieID;
    /* 0x00f4 */ ZombieID mFollowerZombieID[4];
    /* 0x0104 */ bool mPlayingSong;
    char pad_0x105[3];
    /* 0x0108 */ int mParticleOffsetX;
    /* 0x010c */ int mParticleOffsetY;
    /* 0x0110 */ AttachmentID mAttachmentID;
    /* 0x0114 */ int mSummonCounter;
    /* 0x0118 */ ReanimationID mBodyReanimID;
    /* 0x011c */ float mScaleZombie;
    /* 0x0120 */ float mVelZ;
    /* 0x0124 */ float mOrginalAnimRate;
    /* 0x0128 */ PlantID mTargetPlantID;
    /* 0x012c */ int mBossMode;
    /* 0x0130 */ int mTargetRow;
    /* 0x0134 */ int mBossBungeeCounter;
    /* 0x0138 */ int mBossStompCounter;
    /* 0x013c */ int mBossHeadCounter;
    /* 0x0140 */ ReanimationID mBossFireBallReanimID;
    /* 0x0144 */ ReanimationID mSpecialHeadReanimID;
    /* 0x0148 */ int mFireballRow;
    /* 0x014c */ bool mIsFireBall;
    char pad_0x14d[3];
    /* 0x0150 */ ReanimationID mMoweredReanimID;
    /* 0x0154 */ int mLastPortalX;

  public:
    Zombie(const Zombie &);
    Zombie();
    void ZombieInitialize(int, ZombieType, bool, Zombie *, int);
    ~Zombie();
    void Animate();
    void CheckIfPreyCaught();
    void EatZombie(Zombie *);
    void EatPlant(Plant *);
    void Update();
    void DieNoLoot();
    void DieWithLoot();
    void Draw(Sexy::Graphics *);
    void DrawZombie(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void DrawZombieWithParts(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void DrawZombiePart(Sexy::Graphics *, Sexy::Image *, int, int,
                        /*ZombieDrawPosition & */ void *);
    void DrawBungeeCord(Sexy::Graphics *, int, int);
    void TakeDamage(int, unsigned int);
    void SetRow(int);
    float GetPosYBasedOnRow(int);
    void ApplyChill(bool);
    void UpdateZombieBungee();
    void BungeeLanding();
    bool EffectedByDamage(unsigned int);
    void PickRandomSpeed();
    void UpdateZombiePolevaulter();
    void UpdateZombieDolphinRider();
    void PickBungeeZombieTarget(int);
    int CountBungeesTargetingSunFlowers();
    Plant *FindPlantTarget(ZombieAttackType);
    void CheckSquish(ZombieAttackType);
    void RiseFromGrave(int, int);
    void UpdateZombieRiseFromGrave();
    void UpdateDamageStates(unsigned int);
    void UpdateZombiePool();
    void CheckForPool();
    void GetDrawPos(/*ZombieDrawPosition & */ void *);
    void UpdateZombieHighGround();
    void CheckForHighGround();
    bool IsOnHighGround();
    void DropLoot();
    bool TrySpawnLevelAward();
    void StartZombieSound();
    void StopZombieSound();
    void UpdateZombieJackInTheBox();
    void DrawZombieHead(Sexy::Graphics *, /*ZombieDrawPosition & */ void *, int);
    void UpdateZombiePosition();
    Sexy::TRect<int> GetZombieRect();
    Sexy::TRect<int> GetZombieAttackRect();
    void UpdateZombieWalking();
    void UpdateZombieBobsled();
    void BobsledCrash();
    Plant *IsStandingOnSpikeweed();
    void CheckForZombieStep();
    void CountExpectedMowers();
    void OverrideParticleColor(/* TodParticleSystem * */ void *);
    void OverrideParticleScale(/* TodParticleSystem * */ void *);
    void PoolSplash(bool);
    void UpdateZombieFlyer();
    void UpdateZombiePogo();
    void UpdateZombieNewspaper();
    void LandFlyer(unsigned int);
    void UpdateZombieDigger();
    bool IsWalkingBackwards();
    /* TodParticleSystem * */ void *AddAttachedParticle(int, int, ParticleEffect);
    void PogoBreak(unsigned int);
    void UpdateZombieFalling();
    void UpdateZombieDancer();
    ZombieID SummonBackupDancer(int, int);
    void SummonBackupDancers();
    int GetDancerFrame();
    void BungeeStealTarget();
    void UpdateYuckyFace();
    void DrawIceTrap(Sexy::Graphics *, /*ZombieDrawPosition & */ void *, bool);
    void HitIceTrap();
    int GetHelmDamageIndex();
    int GetShieldDamageIndex();
    void DrawReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ void *, int);
    void UpdatePlaying();
    bool NeedsMoreBackupDancers();
    void ConvertToNormalZombie();
    void UpdateDancerWalking();
    void StartEating();
    void StopEating();
    void UpdateAnimSpeed();
    void ReanimShowPrefix(const char *, int);
    void PlayDeathAnim(unsigned int);
    void UpdateDeath();
    void DrawShadow(Sexy::Graphics *);
    bool HasShadow();
    Reanimation *LoadReanim(ReanimationType);
    int TakeFlyingDamage(int, unsigned int);
    int TakeShieldDamage(int, unsigned int);
    int TakeHelmDamage(int, unsigned int);
    void TakeBodyDamage(int, unsigned int);
    void AttachShield();
    void DetachShield();
    void UpdateReanim();
    void GetTrackPosition(const char *, float &, float &);
    void LoadPlainZombieReanim();
    void ShowDoorArms(bool);
    void ReanimShowTrack(const char *, int);
    void PlayZombieAppearSound();
    void StartMindControlled();
    bool IsFlying();
    void DropHead(unsigned int);
    bool CanTargetPlant(Plant *, ZombieAttackType);
    void UpdateZombieCatapult();
    Plant *FindCatapultTarget();
    void ZombieCatapultFire(Plant *);
    void UpdateClimbingLadder();
    void UpdateZombieGargantuar();
    int GetBodyDamageIndex();
    void ApplyBurn();
    void UpdateBurn();
    bool ZombieNotWalking();
    Zombie *FindZombieTarget();
    void PlayZombieReanim(const char *, ReanimLoopType, int, float);
    void UpdateZombieBackupDancer();
    ZombiePhase GetDancerPhase();
    bool IsMovingAtChilledSpeed();
    void StartWalkAnim(int);
    Reanimation *AddAttachedReanim(int, int, ReanimationType);
    void DragUnder();
    bool IsOnBoard();
    void DrawButter(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    bool IsImmobilizied();
    void ApplyButter();
    float ZombieTargetLeadX(float);
    void UpdateZombieImp();
    void SquishAllInSquare(int, int, ZombieAttackType);
    void RemoveIceTrap();
    bool IsBouncingPogo();
    int GetBobsledPosition();
    void DrawBobsledReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ void *, bool);
    void BobsledDie();
    void BobsledBurn();
    bool IsBobsledTeamWithSled();
    bool CanBeFrozen();
    bool CanBeChilled();
    void UpdateZombieSnorkel();
    void ReanimIgnoreClipRect(const char *, bool);
    void SetAnimRate(float);
    void ApplyAnimRate(float);
    bool IsDeadOrDying();
    void DrawDancerReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void DrawBungeeReanim(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void DrawBungeeTarget(Sexy::Graphics *);
    void BungeeDie();
    void ZamboniDeath(unsigned int);
    void CatapultDeath(unsigned int);
    bool SetupDrawZombieWon(Sexy::Graphics *);
    void WalkIntoHouse();
    void UpdateZamboni();
    void UpdateZombieChimney();
    void UpdateLadder();
    void DropArm(unsigned int);
    bool CanLoseBodyParts();
    void DropHelm(unsigned int);
    void DropShield(unsigned int);
    void ReanimReenableClipping();
    void UpdateBoss();
    void BossPlayIdle();
    void BossRVLanding();
    void BossStompContact();
    bool BossAreBungeesDone();
    void BossBungeeSpawn();
    void BossSpawnAttack();
    void BossBungeeAttack();
    void BossRVAttack();
    void BossSpawnContact();
    void BossBungeeLeave();
    void BossStompAttack();
    bool BossCanStompRow(int);
    void BossDie();
    void BossHeadAttack();
    void BossHeadSpitContact();
    void BossHeadSpit();
    void UpdateBossFireball();
    void BossDestroyFireball();
    void BossDestroyIceballInRow(int);
    void DiggerLoseAxe();
    void BungeeDropZombie(Zombie *, int, int);
    void ShowYuckyFace(bool);
    void AnimateChewSound();
    void AnimateChewEffect();
    void UpdateActions();
    void CheckForBoardEdge();
    void UpdateYeti();
    void DrawBossPart(Sexy::Graphics *, BossPart);
    void BossSetupReanim();
    void MowDown();
    void UpdateMowered();
    void DropFlag();
    void DropPole();
    void DrawBossBackArm(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void BossStartDeath();
    void RemoveColdEffects();
    void BossHeadSpitEffect();
    void DrawBossFireBall(Sexy::Graphics *, /*ZombieDrawPosition & */ void *);
    void UpdateZombiePeaHead();
    void UpdateZombieJalapenoHead();
    void ApplyBossSmokeParticles(bool);
    void UpdateZombiquarium();
    bool ZombiquariumFindClosestBrain();
    void UpdateZombieGatlingHead();
    void UpdateZombieSquashHead();
    bool IsTanglekelpTarget();
    bool HasYuckyFaceImage();
    bool IsTangleKelpTarget();
    bool IsFireResistant();
    void EnableMustache(bool);
    void EnableFuture(bool);
    void BungeeDropPlant();
    void RemoveButter();
    void BalloonPropellerHatSpin(bool);
    void DoDaisies();
    static void SetupDoorArms(Reanimation *, bool);
    static void SetupReanimLayers(Reanimation *, ZombieType);
    static void PreloadZombieResources(ZombieType);
};

#endif // __ZOMBIE_H__
