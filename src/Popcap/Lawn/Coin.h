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
    COIN_NONE                   = 0x0000,
    COIN_SILVER                 = 0x0001,
    COIN_GOLD                   = 0x0002,
    COIN_DIAMOND                = 0x0003,
    COIN_SUN                    = 0x0004,
    COIN_SMALLSUN               = 0x0005,
    COIN_LARGESUN               = 0x0006,
    COIN_FINAL_SEED_PACKET      = 0x0007,
    COIN_TROPHY                 = 0x0008,
    COIN_SHOVEL                 = 0x0009,
    COIN_ALMANAC                = 0x000a,
    COIN_CARKEYS                = 0x000b,
    COIN_VASE                   = 0x000c,
    COIN_WATERING_CAN           = 0x000d,
    COIN_TACO                   = 0x000e,
    COIN_NOTE                   = 0x000f,
    COIN_USABLE_SEED_PACKET     = 0x0010,
    COIN_PRESENT_PLANT          = 0x0011,
    COIN_AWARD_MONEY_BAG        = 0x0012,
    COIN_AWARD_PRESENT          = 0x0013,
    COIN_AWARD_BAG_DIAMOND      = 0x0014,
    COIN_AWARD_SILVER_SUNFLOWER = 0x0015,
    COIN_AWARD_GOLD_SUNFLOWER   = 0x0016,
    COIN_CHOCOLATE              = 0x0017,
    COIN_AWARD_CHOCOLATE        = 0x0018,
    COIN_PRESENT_MINIGAMES      = 0x0019,
    COIN_PRESENT_PUZZLE_MODE    = 0x001a,
};
#endif

#ifndef E_COIN_MOTION
#define E_COIN_MOTION
enum CoinMotion : int
{
    COIN_MOTION_FROM_SKY       = 0x0000,
    COIN_MOTION_FROM_SKY_SLOW  = 0x0001,
    COIN_MOTION_FROM_PLANT     = 0x0002,
    COIN_MOTION_COIN           = 0x0003,
    COIN_MOTION_LAWNMOWER_COIN = 0x0004,
    COIN_MOTION_FROM_PRESENT   = 0x0005,
    COIN_MOTION_FROM_BOSS      = 0x0006,
};
#endif

class Coin : public GameObject
{ /* Size=0xd0 */
  public:
    /* 0x0000: fields for GameObject */
    /* 0x0024 */ float mPosX;
    /* 0x0028 */ float mPosY;
    /* 0x002c */ float mVelX;
    /* 0x0030 */ float mVelY;
    /* 0x0034 */ float mScale;
    /* 0x0038 */ bool mDead;
    // char pad_0x39[3];
    /* 0x003c */ int mFadeCount;
    /* 0x0040 */ float mCollectX;
    /* 0x0044 */ float mCollectY;
    /* 0x0048 */ int mGroundY;
    /* 0x004c */ int mCoinAge;
    /* 0x0050 */ bool mIsBeingCollected;
    // char pad_0x51[3];
    /* 0x0054 */ int mDisappearCounter;
    /* 0x0058 */ CoinType mType;
    /* 0x005c */ CoinMotion mCoinMotion;
    /* 0x0060 */ AttachmentID mAttachmentID;
    /* 0x0064 */ float mCollectionDistance;
    /* 0x0068 */ SeedType mUsableSeedType;
    // char pad_0x69[4];
    /* 0x0070 */ PottedPlant mPottedPlantSpec;
    /* 0x00c8 */ bool mNeedsBouncyArrow;
    /* 0x00c9 */ bool mHasBouncyArrow;
    /* 0x00ca */ bool mHitGround;
    /* 0x00cc */ int mTimesDropped;

  public:
    void CoinInitialize(int, int, CoinType, CoinMotion);
    ~Coin();
    void MouseDown(int, int, int);
    bool MouseHitTest(int, int, HitResult *);
    void Die();
    void StartFade();
    void Update();
    void Draw(Sexy::Graphics *);
    void Collect();
    int GetSunValue();
    void UpdateFade();
    void UpdateFall();
    void ScoreCoin();
    void UpdateCollected();
    Sexy::Color GetColor();
    bool IsMoney();
    bool IsSun();
    float GetSunScale();
    SeedType GetFinalSeedPacketType();
    bool IsLevelAward();
    bool CoinGetsBouncyArrow();
    void FanOutCoins(CoinType, int);
    int GetDisappearTime();
    void DroppedUsableSeed();
    void PlayCollectSound();
    void TryAutoCollectAfterLevelAward();
    bool IsPresentWithAdvice();
    void PlayGroundSound();
    void PlayLaunchSound();
    Coin();
    static int GetCoinValue(CoinType);
};

#endif
