#ifndef __COIN_H__
#define __COIN_H__

#include "GameObject.h"
#include "LawnApp.h"
#include "Plant.h"

class GameObject;
class LawnApp;
class Plant;

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

class Coin : public GameObject
{   /* Size=0xd0 */
    /* 0x0000: fields for GameObject */
  /* 0x0024 */ public:
    float mPosX;
  /* 0x0028 */ public:
    float mPosY;
  /* 0x002c */ public:
    float mVelX;
  /* 0x0030 */ public:
    float mVelY;
  /* 0x0034 */ public:
    float mScale;
  /* 0x0038 */ public:
    bool mDead;
    // char pad_0x39[3];
  /* 0x003c */ public:
    int mFadeCount;
  /* 0x0040 */ public:
    float mCollectX;
  /* 0x0044 */ public:
    float mCollectY;
  /* 0x0048 */ public:
    int mGroundY;
  /* 0x004c */ public:
    int mCoinAge;
  /* 0x0050 */ public:
    bool mIsBeingCollected;
    // char pad_0x51[3];
  /* 0x0054 */ public:
    int mDisappearCounter;
  /* 0x0058 */ public:
    CoinType mType;
  /* 0x005c */ public:
    CoinMotion mCoinMotion;
  /* 0x0060 */ public:
    AttachmentID mAttachmentID;
  /* 0x0064 */ public:
    float mCollectionDistance;
  /* 0x0068 */ public:
    SeedType mUsableSeedType;
    // char pad_0x69[4];
  /* 0x0070 */ public:
    PottedPlant mPottedPlantSpec;
  /* 0x00c8 */ public:
    bool mNeedsBouncyArrow;
  /* 0x00c9 */ public:
    bool mHasBouncyArrow;
  /* 0x00ca */ public:
    bool mHitGround;
  /* 0x00cc */ public:
    int mTimesDropped;

  public:
    void CoinInitialize(int, int, CoinType, CoinMotion);

  public:
    ~Coin();

  public:
    void MouseDown(int, int, int);

  public:
    bool MouseHitTest(int, int, HitResult *);

  public:
    void Die();

  public:
    void StartFade();

  public:
    void Update();

  public:
    void Draw(Sexy::Graphics *);

  public:
    void Collect();

  public:
    int GetSunValue();

  public:
    void UpdateFade();

  public:
    void UpdateFall();

  public:
    void ScoreCoin();

  public:
    void UpdateCollected();

  public:
    Sexy::Color GetColor();

  public:
    bool IsMoney();

  public:
    bool IsSun();

  public:
    float GetSunScale();

  public:
    SeedType GetFinalSeedPacketType();

  public:
    bool IsLevelAward();

  public:
    bool CoinGetsBouncyArrow();

  public:
    void FanOutCoins(CoinType, int);

  public:
    int GetDisappearTime();

  public:
    void DroppedUsableSeed();

  public:
    void PlayCollectSound();

  public:
    void TryAutoCollectAfterLevelAward();

  public:
    bool IsPresentWithAdvice();

  public:
    void PlayGroundSound();

  public:
    void PlayLaunchSound();

  public:
    Coin();

  public:
    static int GetCoinValue(CoinType);
};

#endif