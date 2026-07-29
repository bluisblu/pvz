#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

class PlayerInfo;

#include "Enums.h"
#include "Plant.h"

class PlayerInfo
{ /* Size=0x4818 */
  public:
    /* 0x0000 */ std::string mName;
    /* 0x001c */ unsigned int mUseSeq;
    /* 0x0020 */ unsigned int mId;
    /* 0x0024 */ int mLevel;
    /* 0x0028 */ int mCoins;
    /* 0x002c */ int mFinishedAdventure;
    /* 0x0030 */ int mChallengeRecords[100];
    /* 0x01c0 */ int mPurchases[80];
    /* 0x0300 */ int mPlayTimeActivePlayer;
    /* 0x0304 */ int mPlayTimeInactivePlayer;
    /* 0x0308 */ int mHasUsedCheatKeys;
    /* 0x030c */ int mHasWokenStinky;
    /* 0x0310 */ int mDidntPurchasePacketUpgrade;
    /* 0x0314 */ int mLastStinkyChocolateTime;
    /* 0x0318 */ int mStinkyPosX;
    /* 0x031c */ int mStinkyPosY;
    /* 0x0320 */ int mHasUnlockedMinigames;
    /* 0x0324 */ int mHasUnlockedPuzzleMode;
    /* 0x0328 */ int mHasNewMiniGame;
    /* 0x032c */ int mHasNewVasebreaker;
    /* 0x0330 */ int mHasNewIZombie;
    /* 0x0334 */ int mHasNewSurvival;
    /* 0x0338 */ int mPlaceHolderPlayerStats[6];
    /* 0x0350 */ int mNumPottedPlants;
    /* 0x0358 */ PottedPlant mPottedPlant[200];

  public:
    PlayerInfo(const PlayerInfo &);
    PlayerInfo();
    ~PlayerInfo();
    void Reset();
    void AddCoins(int);
    void SyncSummary(class DataSync &);
    void SyncDetails(class DataSync &);
    void DeleteUserFiles();
    void LoadDetails();
    void SaveDetails();
    int GetLevel();
    void SetLevel(int);
    void ResetChallengeRecord(GameMode);
    PlayerInfo &operator=(const PlayerInfo &);
};

#endif
