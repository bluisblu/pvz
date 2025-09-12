#pragma once

#ifndef __CURSOROBJECT_H__
#define __CURSOROBJECT_H__

#include "GameObject.h"
#include "LawnApp.h"

#ifndef E_COIN_ID
#define E_COIN_ID
enum CoinID : int
{
    COINID_NULL = 0x0000,
};
#endif

#ifndef E_PLANT_ID
#define E_PLANT_ID
enum PlantID : int
{
    PLANTID_NULL = 0x0000,
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

class CursorObject : public GameObject
{   /* Size=0x4c */
    /* 0x0000: fields for GameObject */
  /* 0x0024 */ public:
    int mSeedBankIndex;
  /* 0x0028 */ public:
    SeedType mType;
  /* 0x002c */ public:
    SeedType mImitaterType;
  /* 0x0030 */ public:
    CursorType mCursorType;
  /* 0x0034 */ public:
    CoinID mCoinID;
  /* 0x0038 */ public:
    PlantID mGlovePlantID;
  /* 0x003c */ public:
    PlantID mDuplicatorPlantID;
  /* 0x0040 */ public:
    PlantID mCobCannonPlantID;
  /* 0x0044 */ public:
    int mHammerDownCounter;
  /* 0x0048 */ public:
    ReanimationID mReanimCursorID;

  public:
    CursorObject();

  public:
    void Update();

  public:
    void Draw(Sexy::Graphics *);

  public:
    void Die();
};

#endif // __CURSOROBJECT_H__