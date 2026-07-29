#ifndef __COIN_H__
#define __COIN_H__

#include "GameObject.h"
#include "LawnApp.h"
#include "Plant.h"

class GameObject;
class LawnApp;

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
