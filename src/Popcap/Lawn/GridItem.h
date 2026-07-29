#ifndef __GRIDITEM_H__
#define __GRIDITEM_H__

#include "LawnApp.h"
#include "Plant.h"
#include "Zombie.h"

class MotionTrailFrame
{ /* Size=0xc */
  public:
    /* 0x0000 */ float mPosX;
    /* 0x0004 */ float mPosY;
    /* 0x0008 */ float mAnimTime;
};

class GridItem
{ /* Size=0xe8 */
  public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Board *mBoard;
    /* 0x0008 */ GridItemType mGridItemType;
    /* 0x000c */ GridItemState mGridItemState;
    /* 0x0010 */ int mGridX;
    /* 0x0014 */ int mGridY;
    /* 0x0018 */ int mGridItemCounter;
    /* 0x001c */ int mRenderOrder;
    /* 0x0020 */ bool mDead;
    /* 0x0024 */ float mPosX;
    /* 0x0028 */ float mPosY;
    /* 0x002c */ float mGoalX;
    /* 0x0030 */ float mGoalY;
    /* 0x0034 */ ReanimationID mGridItemReanimID;
    /* 0x0038 */ ParticleSystemID mGridItemParticleID;
    /* 0x003c */ ZombieType mZombieType;
    /* 0x0040 */ SeedType mSeedType;
    /* 0x0044 */ ScaryPotType mScaryPotType;
    /* 0x0048 */ bool mHighlighted;
    /* 0x004c */ int mTransparentCounter;
    /* 0x0050 */ int mSunCount;
    /* 0x0054 */ MotionTrailFrame mMotionTrailFrames[12];
    /* 0x00e4 */ int mMotionTrailCount;

  public:
    GridItem();
    void DrawLadder(Sexy::Graphics *);
    void DrawCrater(Sexy::Graphics *);
    void DrawGraveStone(Sexy::Graphics *);
    void GridItemDie();
    void AddGraveStoneParticles();
    void DrawGridItem(Sexy::Graphics *);
    void DrawGridItemOverlay(Sexy::Graphics *);
    void OpenPortal();
    void Update();
    void ClosePortal();
    void DrawScaryPot(Sexy::Graphics *);
    void UpdateScaryPot();
    void UpdatePortal();
    void DrawSquirrel(Sexy::Graphics *);
    void UpdateRake();
    Zombie *RakeFindZombie();
    void DrawIZombieBrain(Sexy::Graphics *);
    void UpdateBrain();
    void DrawStinky(Sexy::Graphics *);
};
#endif
