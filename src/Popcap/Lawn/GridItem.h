#pragma once

#ifndef __GRIDITEM_H__
#define __GRIDITEM_H__

#include "LawnApp.h"
#include "Plant.h"
#include "Zombie.h"

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

#ifndef E_GRID_ITEM_TYPE
#define E_GRID_ITEM_TYPE
enum GridItemType : int
{
    GRIDITEM_NONE          = 0x0000,
    GRIDITEM_GRAVESTONE    = 0x0001,
    GRIDITEM_CRATER        = 0x0002,
    GRIDITEM_LADDER        = 0x0003,
    GRIDITEM_PORTAL_CIRCLE = 0x0004,
    GRIDITEM_PORTAL_SQUARE = 0x0005,
    GRIDITEM_BRAIN         = 0x0006,
    GRIDITEM_SCARY_POT     = 0x0007,
    GRIDITEM_SQUIRREL      = 0x0008,
    GRIDITEM_ZEN_TOOL      = 0x0009,
    GRIDITEM_STINKY        = 0x000a,
    GRIDITEM_RAKE          = 0x000b,
    GRIDITEM_IZOMBIE_BRAIN = 0x000c,
};
#endif

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
