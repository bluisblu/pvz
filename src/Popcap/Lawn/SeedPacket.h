#ifndef __SEEDPACKET_H__
#define __SEEDPACKET_H__

#include "Enums.h"
#include "GameObject.h"

#include "SexyAppFramework/Graphics.h"

class SeedPacket : public GameObject
{
  public:
    int mRefreshCounter;             // 0x24
    int mRefreshTime;                // 0x28
    int mIndex;                      // 0x2C
    int mOffsetX;                    // 0x30
    SeedType mPacketType;            // 0x34
    SeedType mImitaterType;          // 0x38
    int mSlotMachineCountDown;       // 0x3C
    SeedType mSlotMachiningNextSeed; // 0x40
    float mSlotMachiningPosition;    // 0x44
    bool mActive;                    // 0x48
    bool mRefreshing;                // 0x49
    int mTimesUsed;                  // 0x4C
    SeedPacket();
    void Update();
    void Draw(Sexy::Graphics *);
    void MouseDown(int, int, int);
    bool MouseHitTest(int, int, HitResult *);
    void Deactivate();
    void Activate();
    void PickNextSlotMachineSeed();
    void SlotMachineStart();
    void WasPlanted();
    void FlashIfReady();
    bool CanPickUp();
    void SetPacketType(SeedType, SeedType);
};

class SeedBank : public GameObject
{
  public:
    int mNumPackets;             // 0x24
    SeedPacket mSeedPackets[10]; // 0x28
    int mCutSceneDarken;         // 0x348
    int mConveyorBeltCounter;    // 0x34C
    SeedBank();
    void Draw(Sexy::Graphics *);
    bool MouseHitTest(int, int, HitResult *);
    void Move(int, int);
    bool ContainsPoint(int, int);
    int GetNumSeedsOnConveyorBelt();
    void AddSeed(SeedType, bool);
    void RemoveSeed(int);
    int CountOfTypeOnConveyorBelt(SeedType);
    void UpdateConveyorBelt();
    void UpdateWidth();
    void RefreshAllPackets();
};

#endif
