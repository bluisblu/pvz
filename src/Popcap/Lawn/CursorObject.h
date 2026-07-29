#ifndef __CURSOROBJECT_H__
#define __CURSOROBJECT_H__

#include "GameObject.h"
#include "LawnApp.h"

class CursorObject : public GameObject
{ /* Size=0x4c */
  public:
    /* 0x0000: fields for GameObject */
    /* 0x0024 */ int mSeedBankIndex;
    /* 0x0028 */ SeedType mType;
    /* 0x002c */ SeedType mImitaterType;
    /* 0x0030 */ CursorType mCursorType;
    /* 0x0034 */ CoinID mCoinID;
    /* 0x0038 */ PlantID mGlovePlantID;
    /* 0x003c */ PlantID mDuplicatorPlantID;
    /* 0x0040 */ PlantID mCobCannonPlantID;
    /* 0x0044 */ int mHammerDownCounter;
    /* 0x0048 */ ReanimationID mReanimCursorID;

  public:
    CursorObject();
    void Update();
    void Draw(Sexy::Graphics *);
    void Die();
};

#endif // __CURSOROBJECT_H__
