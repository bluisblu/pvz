#pragma once

#ifndef __REANIMATOR_H__
#define __REANIMATOR_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/SexyMatrix.h"

#include "Attachment.h"
#include "ReanimAtlas.h"

class AttachEffect;

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

#ifndef E_ATTACHMENT_ID
#define E_ATTACHMENT_ID
enum AttachmentID : int
{
    ATTACHMENTID_NULL = 0x0000,
};
#endif

#ifndef E_REANIMATION_TYPE
#define E_REANIMATION_TYPE
enum ReanimationType : int
{
    REANIM_NONE = -1,
    REANIM_LOADBAR_SPROUT = 0x0000,
    REANIM_LOADBAR_ZOMBIEHEAD = 0x0001,
    REANIM_SODROLL = 0x0002,
    REANIM_FINAL_WAVE = 0x0003,
    REANIM_PEASHOOTER = 0x0004,
    REANIM_WALLNUT = 0x0005,
    REANIM_LILYPAD = 0x0006,
    REANIM_SUNFLOWER = 0x0007,
    REANIM_LAWNMOWER = 0x0008,
    REANIM_READYSETPLANT = 0x0009,
    REANIM_CHERRYBOMB = 0x000a,
    REANIM_SQUASH = 0x000b,
    REANIM_DOOMSHROOM = 0x000c,
    REANIM_SNOWPEA = 0x000d,
    REANIM_REPEATER = 0x000e,
    REANIM_SUNSHROOM = 0x000f,
    REANIM_TALLNUT = 0x0010,
    REANIM_FUMESHROOM = 0x0011,
    REANIM_PUFFSHROOM = 0x0012,
    REANIM_HYPNOSHROOM = 0x0013,
    REANIM_CHOMPER = 0x0014,
    REANIM_ZOMBIE = 0x0015,
    REANIM_SUN = 0x0016,
    REANIM_POTATOMINE = 0x0017,
    REANIM_SPIKEWEED = 0x0018,
    REANIM_SPIKEROCK = 0x0019,
    REANIM_THREEPEATER = 0x001a,
    REANIM_MARIGOLD = 0x001b,
    REANIM_ICESHROOM = 0x001c,
    REANIM_ZOMBIE_FOOTBALL = 0x001d,
    REANIM_ZOMBIE_NEWSPAPER = 0x001e,
    REANIM_ZOMBIE_ZAMBONI = 0x001f,
    REANIM_SPLASH = 0x0020,
    REANIM_JALAPENO = 0x0021,
    REANIM_JALAPENO_FIRE = 0x0022,
    REANIM_COIN_SILVER = 0x0023,
    REANIM_ZOMBIE_CHARRED = 0x0024,
    REANIM_ZOMBIE_CHARRED_IMP = 0x0025,
    REANIM_ZOMBIE_CHARRED_DIGGER = 0x0026,
    REANIM_ZOMBIE_CHARRED_ZAMBONI = 0x0027,
    REANIM_ZOMBIE_CHARRED_CATAPULT = 0x0028,
    REANIM_ZOMBIE_CHARRED_GARGANTUAR = 0x0029,
    REANIM_SCRAREYSHROOM = 0x002a,
    REANIM_PUMPKIN = 0x002b,
    REANIM_PLANTERN = 0x002c,
    REANIM_TORCHWOOD = 0x002d,
    REANIM_SPLITPEA = 0x002e,
    REANIM_SEASHROOM = 0x002f,
    REANIM_BLOVER = 0x0030,
    REANIM_FLOWER_POT = 0x0031,
    REANIM_CACTUS = 0x0032,
    REANIM_DANCER = 0x0033,
    REANIM_TANGLEKELP = 0x0034,
    REANIM_STARFRUIT = 0x0035,
    REANIM_POLEVAULTER = 0x0036,
    REANIM_BALLOON = 0x0037,
    REANIM_GARGANTUAR = 0x0038,
    REANIM_IMP = 0x0039,
    REANIM_DIGGER = 0x003a,
    REANIM_DIGGER_DIRT = 0x003b,
    REANIM_ZOMBIE_DOLPHINRIDER = 0x003c,
    REANIM_POGO = 0x003d,
    REANIM_BACKUP_DANCER = 0x003e,
    REANIM_BOBSLED = 0x003f,
    REANIM_JACKINTHEBOX = 0x0040,
    REANIM_SNORKEL = 0x0041,
    REANIM_BUNGEE = 0x0042,
    REANIM_CATAPULT = 0x0043,
    REANIM_LADDER = 0x0044,
    REANIM_PUFF = 0x0045,
    REANIM_SLEEPING = 0x0046,
    REANIM_GRAVE_BUSTER = 0x0047,
    REANIM_ZOMBIES_WON = 0x0048,
    REANIM_MAGNETSHROOM = 0x0049,
    REANIM_BOSS = 0x004a,
    REANIM_CABBAGEPULT = 0x004b,
    REANIM_KERNELPULT = 0x004c,
    REANIM_MELONPULT = 0x004d,
    REANIM_COFFEEBEAN = 0x004e,
    REANIM_UMBRELLALEAF = 0x004f,
    REANIM_GATLINGPEA = 0x0050,
    REANIM_CATTAIL = 0x0051,
    REANIM_GLOOMSHROOM = 0x0052,
    REANIM_BOSS_ICEBALL = 0x0053,
    REANIM_BOSS_FIREBALL = 0x0054,
    REANIM_COBCANNON = 0x0055,
    REANIM_GARLIC = 0x0056,
    REANIM_GOLD_MAGNET = 0x0057,
    REANIM_WINTER_MELON = 0x0058,
    REANIM_TWIN_SUNFLOWER = 0x0059,
    REANIM_POOL_CLEANER = 0x005a,
    REANIM_ROOF_CLEANER = 0x005b,
    REANIM_FIRE_PEA = 0x005c,
    REANIM_IMITATER = 0x005d,
    REANIM_YETI = 0x005e,
    REANIM_BOSS_DRIVER = 0x005f,
    REANIM_LAWN_MOWERED_ZOMBIE = 0x0060,
    REANIM_CRAZY_DAVE = 0x0061,
    REANIM_TEXT_FADE_ON = 0x0062,
    REANIM_HAMMER = 0x0063,
    REANIM_SLOT_MACHINE_HANDLE = 0x0064,
    REANIM_CREDITS_FOOTBALL = 0x0065,
    REANIM_CREDITS_JACKBOX = 0x0066,
    REANIM_SELECTOR_SCREEN = 0x0067,
    REANIM_PORTAL_CIRCLE = 0x0068,
    REANIM_PORTAL_SQUARE = 0x0069,
    REANIM_ZENGARDEN_SPROUT = 0x006a,
    REANIM_ZENGARDEN_WATERINGCAN = 0x006b,
    REANIM_ZENGARDEN_FERTILIZER = 0x006c,
    REANIM_ZENGARDEN_BUGSPRAY = 0x006d,
    REANIM_ZENGARDEN_PHONOGRAPH = 0x006e,
    REANIM_DIAMOND = 0x006f,
    REANIM_ZOMBIE_HAND = 0x0070,
    REANIM_STINKY = 0x0071,
    REANIM_RAKE = 0x0072,
    REANIM_RAIN_CIRCLE = 0x0073,
    REANIM_RAIN_SPLASH = 0x0074,
    REANIM_ZOMBIE_SURPRISE = 0x0075,
    REANIM_COIN_GOLD = 0x0076,
    REANIM_TREE_OF_WISDOM = 0x0077,
    REANIM_TREE_OF_WISDOM_CLOUDS = 0x0078,
    REANIM_TREE_FOOD = 0x0079,
    REANIM_CREDITS_MAIN = 0x007a,
    REANIM_CREDITS_MAIN2 = 0x007b,
    REANIM_CREDITS_MAIN3 = 0x007c,
    REANIM_ZOMBIE_CREDITS_DANCE = 0x007d,
    REANIM_CREDITS_STAGE = 0x007e,
    REANIM_CREDITS_BIGBRAIN = 0x007f,
    REANIM_CREDITS_FLOWER_PETALS = 0x0080,
    REANIM_CREDITS_INFANTRY = 0x0081,
    REANIM_CREDITS_THROAT = 0x0082,
    REANIM_CREDITS_CRAZYDAVE = 0x0083,
    REANIM_CREDITS_BOSSDANCE = 0x0084,
    REANIM_ZOMBIE_CREDITS_SCREEN_DOOR = 0x0085,
    REANIM_ZOMBIE_CREDITS_CONEHEAD = 0x0086,
    REANIM_CREDITS_ZOMBIEARMY1 = 0x0087,
    REANIM_CREDITS_ZOMBIEARMY2 = 0x0088,
    REANIM_CREDITS_TOMBSTONES = 0x0089,
    REANIM_CREDITS_SOLARPOWER = 0x008a,
    REANIM_CREDITS_ANYHOUR = 0x008b,
    REANIM_CREDITS_WEARETHEUNDEAD = 0x008c,
    REANIM_CREDITS_DISCOLIGHTS = 0x008d,
    NUM_REANIMS = 0x008e,
};
#endif

#ifndef E_REANIM_LOOP_TYPE
#define E_REANIM_LOOP_TYPE
enum ReanimLoopType : int
{
    REANIM_LOOP = 0x0000,
    REANIM_LOOP_FULL_LAST_FRAME = 0x0001,
    REANIM_PLAY_ONCE = 0x0002,
    REANIM_PLAY_ONCE_AND_HOLD = 0x0003,
    REANIM_PLAY_ONCE_FULL_LAST_FRAME = 0x0004,
    REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD = 0x0005,
};
#endif

class ReanimatorTransform
{ /* Size=0x2c */
  /* 0x0000 */ public:
    float mTransX;
  /* 0x0004 */ public:
    float mTransY;
  /* 0x0008 */ public:
    float mSkewX;
  /* 0x000c */ public:
    float mSkewY;
  /* 0x0010 */ public:
    float mScaleX;
  /* 0x0014 */ public:
    float mScaleY;
  /* 0x0018 */ public:
    float mFrame;
  /* 0x001c */ public:
    float mAlpha;
  /* 0x0020 */ public:
    Sexy::Image *mImage;
  /* 0x0024 */ public:
    Sexy::Font *mFont;
  /* 0x0028 */ public:
    char *mText;

  public:
    ReanimatorTransform();
};

class ReanimatorTrack
{ /* Size=0xc */
  /* 0x0000 */ public:
    char *mName;
  /* 0x0004 */ public:
    ReanimatorTransform *mTransforms;
  /* 0x0008 */ public:
    int mTransformCount;

  public:
    ReanimatorTrack();
};

class ReanimatorTrackInstance
{ /* Size=0x60 */
  /* 0x0000 */ public:
    int mBlendCounter;
  /* 0x0004 */ public:
    int mBlendTime;
  /* 0x0008 */ public:
    ReanimatorTransform mBlendTransform;
  /* 0x0034 */ public:
    float mShakeOverride;
  /* 0x0038 */ public:
    float mShakeX;
  /* 0x003c */ public:
    float mShakeY;
  /* 0x0040 */ public:
    AttachmentID mAttachmentID;
  /* 0x0044 */ public:
    Sexy::Image *mImageOverride;
  /* 0x0048 */ public:
    int mRenderGroup;
  /* 0x004c */ public:
    Sexy::Color mTrackColor;
  /* 0x005c */ public:
    bool mIgnoreClipRect;
  /* 0x005d */ public:
    bool mTruncateDisappearingFrames;

  public:
    ReanimatorTrackInstance();
};

class ReanimatorDefinition
{ /* Size=0x10 */
  /* 0x0000 */ public:
    ReanimatorTrack *mTracks;
  /* 0x0004 */ public:
    int mTrackCount;
  /* 0x0008 */ public:
    float mFPS;
  /* 0x000c */ public:
    ReanimAtlas *mReanimAtlas;

  public:
    ReanimatorDefinition();
};

class ReanimationHolder;

class Reanimation
{ /* Size=0x9c */
  /* 0x0000 */ public:
    ReanimationType mReanimationType;
  /* 0x0004 */ public:
    float mAnimTime;
  /* 0x0008 */ public:
    float mAnimRate;
  /* 0x000c */ public:
    ReanimatorDefinition *mDefinition;
  /* 0x0010 */ public:
    ReanimLoopType mLoopType;
  /* 0x0014 */ public:
    bool mDead;
  /* 0x0018 */ public:
    int mFrameStart;
  /* 0x001c */ public:
    int mFrameCount;
  /* 0x0020 */ public:
    int mFrameBasePose;
  /* 0x0024 */ public:
    Sexy::SexyTransform2D mOverlayMatrix;
  /* 0x0048 */ public:
    Sexy::Color mColorOverride;
  /* 0x0058 */ public:
    ReanimatorTrackInstance *mTrackInstances;
  /* 0x005c */ public:
    int mLoopCount;
  /* 0x0060 */ public:
    ReanimationHolder *mReanimationHolder;
  /* 0x0064 */ public:
    bool mIsAttachment;
  /* 0x0068 */ public:
    int mRenderOrder;
  /* 0x006c */ public:
    Sexy::Color mExtraAdditiveColor;
  /* 0x007c */ public:
    bool mEnableExtraAdditiveDraw;
  /* 0x0080 */ public:
    Sexy::Color mExtraOverlayColor;
  /* 0x0090 */ public:
    bool mEnableExtraOverlayDraw;
  /* 0x0094 */ public:
    float mLastFrameTime;
  /* 0x0098 */ public:
    FilterEffect mFilterEffect;

  public:
    Reanimation();

  public:
    ~Reanimation();

  public:
    void ReanimationInitialize(float, float, ReanimatorDefinition *);

  public:
    void ReanimationInitializeType(float, float, ReanimationType);

  public:
    void ReanimationDie();

  public:
    void Update();

  public:
    void Draw(Sexy::Graphics *);

  public:
    void DrawRenderGroup(Sexy::Graphics *, int);

  public:
    bool DrawTrack(Sexy::Graphics *, int, int, /*TodTriangleGroup * */ int);

  public:
    void GetCurrentTransform(int, ReanimatorTransform *);

  public:
    void GetTransformAtTime(int, ReanimatorTransform *, /*ReanimatorFrameTime * */ int);

  public:
    void GetFrameTime(/*ReanimatorFrameTime * */ int);

  public:
    int FindTrackIndex(const char *);

  public:
    void AttachToAnotherReanimation(Reanimation *, const char *);

  public:
    void GetAttachmentOverlayMatrix(int, Sexy::SexyTransform2D &);

  public:
    void SetFramesForLayer(const char *);

  public:
    bool TrackExists(const char *);

  public:
    void StartBlend(int);

  public:
    void SetShakeOverride(const char *, float);

  public:
    void SetPosition(float, float);

  public:
    void OverrideScale(float, float);

  public:
    float GetTrackVelocity(const char *);

  public:
    void SetImageOverride(const char *, Sexy::Image *);

  public:
    Sexy::Image *GetImageOverride(const char *);

  public:
    void ShowOnlyTrack(const char *);

  public:
    void GetTrackMatrix(int, Sexy::SexyTransform2D &);

  public:
    void AssignRenderGroupToTrack(const char *, int);

  public:
    void AssignRenderGroupToPrefix(const char *, int);

  public:
    void PropogateColorToAttachments();

  public:
    bool ShouldTriggerTimedEvent(float);

  public:
    void TodTriangleGroupDraw(Sexy::Graphics *, /*TodTriangleGroup * */ int);

  public:
    Sexy::Image *GetCurrentTrackImage(const char *);

  public:
    /*AttachEffect * */ int AttachParticleToTrack(const char *, /*TodParticleSystem * */ int, float, float);

  public:
    void GetTrackBasePoseMatrix(int, Sexy::SexyTransform2D &);

  public:
    bool IsTrackShowing(const char *);

  public:
    void SetTruncateDisappearingFrames(const char *, bool);

  public:
    void PlayReanim(const char *, ReanimLoopType, int, float);

  public:
    void ReanimationDelete();

  public:
    ReanimatorTrackInstance *GetTrackInstanceByName(const char *);

  public:
    void GetFramesForLayer(const char *, int &, int &);

  public:
    void UpdateAttacherTrack(int);

  public:
    void AttacherSynchWalkSpeed(int, Reanimation *, const /*AttacherInfo & */ int);

  public:
    bool IsAnimPlaying(const char *);

  public:
    void SetBasePoseFromAnim(const char *);

  public:
    void ReanimBltMatrix(Sexy::Graphics *, Sexy::Image *, const Sexy::SexyMatrix3 &, const Sexy::TRect<int> &,
                         const Sexy::Color &, int, const Sexy::TRect<int> &);

  public:
    // void *__vecDelDtor(unsigned int);

  public:
    static void MatrixFromTransform(ReanimatorTransform &, Sexy::SexyMatrix3 &);

  public:
    static void ParseAttacherTrack(const ReanimatorTransform &, /*AttacherInfo & */ int);
};

class ReanimationHolder
{ /* Size=0x1c */
  /* 0x0000 */ public:
    // DataArray<Reanimation> mReanimations;
    char mReanimations[0x1c];

  public:
    ReanimationHolder();

  public:
    ~ReanimationHolder();

  public:
    void InitializeHolder();

  public:
    void DisposeHolder();

  public:
    Reanimation *AllocReanimation(float, float, int, ReanimationType);
};

AttachEffect *AttachReanim(AttachmentID *param_1, Reanimation *param_2, float param_3, float param_4)
{
    return NULL;
}

void ReanimatorEnsureDefinitionLoaded(ReanimationType theReanimType, bool theIsPreloading);

#endif