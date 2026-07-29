#ifndef __PLANT_H__
#define __PLANT_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Enums.h"
#include "GameObject.h"

class PottedPlant
{ /* Size=0x58 */
  public:
    /* 0x0000 */ SeedType mSeedType;
    /* 0x0004 */ GardenType mWhichZenGarden;
    /* 0x0008 */ int mX;
    /* 0x000c */ int mY;
    /* 0x0010 */ int mFacing;
    // char pad_0x14[4];
    /* 0x0018 */ long long mLastWateredTime;
    /* 0x0020 */ DrawVariation mDrawVariation;
    /* 0x0024 */ PottedPlantAge mPlantAge;
    /* 0x0028 */ int mTimesFed;
    /* 0x002c */ int mFeedingsPerGrow;
    /* 0x0030 */ PottedPlantNeed mPlantNeed;
    // char pad_0x34[4];
    /* 0x0038 */ long long mLastNeedFulfilledTime;
    /* 0x0040 */ long long mLastFertilizedTime;
    /* 0x0048 */ long long mLastChocolateTime;
    /* 0x0050 */ int mFutureAttribute[1];
    char pad_0x54[4];

  public:
    void InitializePottedPlant(SeedType);
};

class Zombie;

#define MAX_MAGNET_ITEMS 5

class MagnetItem
{ /* Size=0x14 */
  public:
    /* 0x0000 */ float mPosX;
    /* 0x0004 */ float mPosY;
    /* 0x0008 */ float mDestOffsetX;
    /* 0x000c */ float mDestOffsetY;
    /* 0x0010 */ MagnetItemType mItemType;
};

class PlantDefinition
{ /* Size=0x24 */
  public:
    /* 0x0000 */ SeedType mSeedType;
    /* 0x0004 */ Sexy::Image **mPlantImage;
    /* 0x0008 */ ReanimationType mReanimationType;
    /* 0x000c */ int mPacketIndex;
    /* 0x0010 */ int mSeedCost;
    /* 0x0014 */ int mRefreshTime;
    /* 0x0018 */ PlantSubClass mSubClass;
    /* 0x001c */ int mLaunchRate;
    /* 0x0020 */ const char *mPlantName;
};

class Plant : public GameObject
{ /* Size=0x148 */
  public:
    /* 0x0000: fields for GameObject */
    /* 0x0024 */ SeedType mSeedType;
    /* 0x0028 */ int mPlantCol;
    /* 0x002c */ int mAnimCounter;
    /* 0x0030 */ bool mAnimPing;
    char pad_0x31[3];
    /* 0x0034 */ int mFrame;
    /* 0x0038 */ int mFrameLength;
    /* 0x003c */ int mNumFrames;
    /* 0x0040 */ PlantState mState;
    /* 0x0044 */ bool mDead;
    /* 0x0045 */ bool mSquished;
    char pad_0x46[2];
    /* 0x0048 */ int mPlantHealth;
    /* 0x004c */ int mPlantMaxHealth;
    /* 0x0050 */ int mSubclass;
    /* 0x0054 */ int mDisappearCountdown;
    /* 0x0058 */ int mDoSpecialCountdown;
    /* 0x005c */ int mStateCountdown;
    /* 0x0060 */ int mLaunchCounter;
    /* 0x0064 */ int mLaunchRate;
    /* 0x0068 */ // Sexy::TRect<int> mPlantRect;
    int mPlantRect[0x4];
    /* 0x0078 */ // Sexy::TRect<int> mPlantAttackRect;
    int mPlantAttackRect[0x4];
    /* 0x0088 */ int mTargetX;
    /* 0x008c */ int mTargetY;
    /* 0x0090 */ int mStartRow;
    /* 0x0094 */ ParticleSystemID mParticleID;
    /* 0x0098 */ int mShootingCounter;
    /* 0x009c */ ReanimationID mBodyReanimID;
    /* 0x00a0 */ ReanimationID mHeadReanimID;
    /* 0x00a4 */ ReanimationID mHeadReanimID2;
    /* 0x00a8 */ ReanimationID mHeadReanimID3;
    /* 0x00ac */ ReanimationID mBlinkReanimID;
    /* 0x00b0 */ ReanimationID mLightReanimID;
    /* 0x00b4 */ ReanimationID mSleepingReanimID;
    /* 0x00b8 */ int mBlinkCountdown;
    /* 0x00bc */ int mRecentlyEatenCountdown;
    /* 0x00c0 */ int mEatenFlashCountdown;
    /* 0x00c4 */ int mBeghouledFlashCountdown;
    /* 0x00c8 */ float mShakeOffsetX;
    /* 0x00cc */ float mShakeOffsetY;
    /* 0x00d0 */ MagnetItem mMagnetItems[5];
    /* 0x0134 */ ZombieID mTargetZombieID;
    /* 0x0138 */ int mWakeUpCounter;
    /* 0x013c */ bool mIsAsleep;
    /* 0x013d */ bool mIsOnBoard;
    /* 0x013e */ bool mIsOnBungee;
    /* 0x013f */ bool mHighlighted;
    /* 0x0140 */ SeedType mImitaterType;
    /* 0x0144 */ int mPottedPlantIndex;

  public:
    void PlantInitialize(int, int, SeedType, SeedType);
    void Update();
    void Animate();
    void Draw(Sexy::Graphics *);
    void MouseDown(int, int, int);
    void DoSpecial();
    void Fire(Zombie *, int, PlantWeapon);
    Zombie *FindTargetZombie(int, PlantWeapon);
    void Die();
    void UpdateProductionPlant();
    void UpdateShooter();
    bool FindTargetAndFire(int, PlantWeapon);
    void LaunchThreepeater();
    void UpdateAbilities();
    void Squish();
    void DoRowAreaDamage(int, unsigned int);
    int GetDamageRangeFlags(PlantWeapon);
    /* Sexy::TRect<int> */ void *GetPlantRect();
    /* Sexy::TRect<int> */ void *GetPlantAttackRect(PlantWeapon);
    Zombie *FindSquashTarget();
    void UpdateSquash();
    bool NotOnGround();
    void DoSquashDamage();
    void BurnRow(int);
    void IceZombies();
    void BlowAwayFliers(int, int);
    void UpdateGraveBuster();
    /* TodParticleSystem * */ void *AddAttachedParticle(int, int, int, ParticleEffect);
    void GetPeaHeadOffset(int &, int &);
    bool MakesSun();
    void KillAllPlantsNearDoom();
    bool IsOnHighGround();
    void UpdateTorchwood();
    void LaunchStarFruit();
    bool FindStarFruitTarget();
    void UpdateChomper();
    void DoBlink();
    void UpdateBlink();
    void PlayBodyReanim(const char *, ReanimLoopType, int, float);
    void UpdateMagnetShroom();
    MagnetItem *GetFreeMagnetItem();
    void DrawMagnetItems(Sexy::Graphics *);
    void UpdateDoomShroom();
    void UpdateIceShroom();
    void UpdatePotato();
    int CalcRenderOrder();
    void AnimateNuts();
    void SetSleeping(bool);
    void UpdateShooting();
    void DrawShadow(Sexy::Graphics *, float, float);
    void UpdateScaredyShroom();
    int DistanceToClosestZombie();
    void UpdateSpikeweed();
    void MagnetShroomAttactItem(Zombie *);
    void UpdateSunShroom();
    void UpdateBowling();
    void AnimatePumpkin();
    void UpdateBlover();
    void UpdateCactus();
    void StarFruitFire();
    void UpdateTanglekelp();
    /* Reanimation * */ void *AttachBlinkAnim(/* Reanimation * */ void *);
    void UpdateReanimColor();
    bool IsUpgradableTo(SeedType);
    bool IsPartOfUpgradableTo(SeedType);
    void UpdateCobCannon();
    void CobCannonFire(int, int);
    void UpdateGoldMagnetShroom();
    bool IsOnBoard();
    void RemoveEffects();
    void UpdateCoffeeBean();
    void UpdateUmbrella();
    void EndBlink();
    void AnimateGarlic();
    /* Coin * */ void *FindGoldMagnetTarget();
    void SpikeweedAttack();
    void ImitaterMorph();
    void UpdateImitater();
    void UpdateReanim();
    void SpikeRockTakeDamage();
    bool IsSpiky();
    bool IsInPlay();
    void UpdateNeedsFood();
    void PlayIdleAnim(float);
    void UpdateFlowerPot();
    void UpdateLilypad();
    void GoldMagnetFindTargets();
    bool IsAGoldMagnetAboutToSuck();
    bool DrawMagnetItemsOnTop();
    Plant(const Plant &);
    Plant();
    static Sexy::Image *GetImage(SeedType);
    static int GetCost(SeedType, SeedType);
    static std::string GetNameString(SeedType, SeedType);
    static std::string GetToolTip(SeedType);
    static int GetRefreshTime(SeedType, SeedType);
    static bool IsNocturnal(SeedType);
    static bool IsAquatic(SeedType);
    static bool IsFlying(SeedType);
    static bool IsUpgrade(SeedType);
    static void DrawSeedType(Sexy::Graphics *, SeedType, SeedType, DrawVariation, float, float);
    static void PreloadPlantResources(SeedType);
};

PlantDefinition const &GetPlantDefinition(SeedType seedType) // placeholder
{
    static PlantDefinition invalidPlant;
    return invalidPlant;
}

#endif // __PLANT_H__
