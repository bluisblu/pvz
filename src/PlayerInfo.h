#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include "Plant.h"

#ifndef E_GAME_MODE
#define E_GAME_MODE
enum GameMode : int
{
    GAMEMODE_ADVENTURE = 0x0000,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_1 = 0x0001,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_2 = 0x0002,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_3 = 0x0003,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_4 = 0x0004,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_5 = 0x0005,
    GAMEMODE_SURVIVAL_HARD_STAGE_1 = 0x0006,
    GAMEMODE_SURVIVAL_HARD_STAGE_2 = 0x0007,
    GAMEMODE_SURVIVAL_HARD_STAGE_3 = 0x0008,
    GAMEMODE_SURVIVAL_HARD_STAGE_4 = 0x0009,
    GAMEMODE_SURVIVAL_HARD_STAGE_5 = 0x000a,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_1 = 0x000b,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_2 = 0x000c,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_3 = 0x000d,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_4 = 0x000e,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_5 = 0x000f,
    GAMEMODE_CHALLENGE_WAR_AND_PEAS = 0x0010,
    GAMEMODE_CHALLENGE_WALLNUT_BOWLING = 0x0011,
    GAMEMODE_CHALLENGE_SLOT_MACHINE = 0x0012,
    GAMEMODE_CHALLENGE_RAINING_SEEDS = 0x0013,
    GAMEMODE_CHALLENGE_BEGHOULED = 0x0014,
    GAMEMODE_CHALLENGE_INVISIGHOUL = 0x0015,
    GAMEMODE_CHALLENGE_SEEING_STARS = 0x0016,
    GAMEMODE_CHALLENGE_ZOMBIQUARIUM = 0x0017,
    GAMEMODE_CHALLENGE_BEGHOULED_TWIST = 0x0018,
    GAMEMODE_CHALLENGE_LITTLE_TROUBLE = 0x0019,
    GAMEMODE_CHALLENGE_PORTAL_COMBAT = 0x001a,
    GAMEMODE_CHALLENGE_COLUMN = 0x001b,
    GAMEMODE_CHALLENGE_BOBSLED_BONANZA = 0x001c,
    GAMEMODE_CHALLENGE_SPEED = 0x001d,
    GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE = 0x001e,
    GAMEMODE_CHALLENGE_LAST_STAND = 0x001f,
    GAMEMODE_CHALLENGE_WAR_AND_PEAS_2 = 0x0020,
    GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2 = 0x0021,
    GAMEMODE_CHALLENGE_POGO_PARTY = 0x0022,
    GAMEMODE_CHALLENGE_FINAL_BOSS = 0x0023,
    GAMEMODE_CHALLENGE_ART_CHALLENGE_1 = 0x0024,
    GAMEMODE_CHALLENGE_SUNNY_DAY = 0x0025,
    GAMEMODE_CHALLENGE_RESODDED = 0x0026,
    GAMEMODE_CHALLENGE_BIG_TIME = 0x0027,
    GAMEMODE_CHALLENGE_ART_CHALLENGE_2 = 0x0028,
    GAMEMODE_CHALLENGE_AIR_RAID = 0x0029,
    GAMEMODE_CHALLENGE_ICE = 0x002a,
    GAMEMODE_CHALLENGE_ZEN_GARDEN = 0x002b,
    GAMEMODE_CHALLENGE_HIGH_GRAVITY = 0x002c,
    GAMEMODE_CHALLENGE_GRAVE_DANGER = 0x002d,
    GAMEMODE_CHALLENGE_SHOVEL = 0x002e,
    GAMEMODE_CHALLENGE_STORMY_NIGHT = 0x002f,
    GAMEMODE_CHALLENGE_BUNGEE_BLITZ = 0x0030,
    GAMEMODE_CHALLENGE_SQUIRREL = 0x0031,
    GAMEMODE_TREE_OF_WISDOM = 0x0032,
    GAMEMODE_SCARY_POTTER_1 = 0x0033,
    GAMEMODE_SCARY_POTTER_2 = 0x0034,
    GAMEMODE_SCARY_POTTER_3 = 0x0035,
    GAMEMODE_SCARY_POTTER_4 = 0x0036,
    GAMEMODE_SCARY_POTTER_5 = 0x0037,
    GAMEMODE_SCARY_POTTER_6 = 0x0038,
    GAMEMODE_SCARY_POTTER_7 = 0x0039,
    GAMEMODE_SCARY_POTTER_8 = 0x003a,
    GAMEMODE_SCARY_POTTER_9 = 0x003b,
    GAMEMODE_SCARY_POTTER_ENDLESS = 0x003c,
    GAMEMODE_PUZZLE_I_ZOMBIE_1 = 0x003d,
    GAMEMODE_PUZZLE_I_ZOMBIE_2 = 0x003e,
    GAMEMODE_PUZZLE_I_ZOMBIE_3 = 0x003f,
    GAMEMODE_PUZZLE_I_ZOMBIE_4 = 0x0040,
    GAMEMODE_PUZZLE_I_ZOMBIE_5 = 0x0041,
    GAMEMODE_PUZZLE_I_ZOMBIE_6 = 0x0042,
    GAMEMODE_PUZZLE_I_ZOMBIE_7 = 0x0043,
    GAMEMODE_PUZZLE_I_ZOMBIE_8 = 0x0044,
    GAMEMODE_PUZZLE_I_ZOMBIE_9 = 0x0045,
    GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS = 0x0046,
    NUM_GAME_MODES = 0x0047,
};
#endif

class PlayerInfo
{ /* Size=0x4818 */
  /* 0x0000 */ public:
    std::string mName;
  /* 0x001c */ public:
    unsigned int mUseSeq;
  /* 0x0020 */ public:
    unsigned int mId;
  /* 0x0024 */ public:
    int mLevel;
  /* 0x0028 */ public:
    int mCoins;
  /* 0x002c */ public:
    int mFinishedAdventure;
  /* 0x0030 */ public:
    int mChallengeRecords[100];
  /* 0x01c0 */ public:
    int mPurchases[80];
  /* 0x0300 */ public:
    int mPlayTimeActivePlayer;
  /* 0x0304 */ public:
    int mPlayTimeInactivePlayer;
  /* 0x0308 */ public:
    int mHasUsedCheatKeys;
  /* 0x030c */ public:
    int mHasWokenStinky;
  /* 0x0310 */ public:
    int mDidntPurchasePacketUpgrade;
  /* 0x0314 */ public:
    int mLastStinkyChocolateTime;
  /* 0x0318 */ public:
    int mStinkyPosX;
  /* 0x031c */ public:
    int mStinkyPosY;
  /* 0x0320 */ public:
    int mHasUnlockedMinigames;
  /* 0x0324 */ public:
    int mHasUnlockedPuzzleMode;
  /* 0x0328 */ public:
    int mHasNewMiniGame;
  /* 0x032c */ public:
    int mHasNewVasebreaker;
  /* 0x0330 */ public:
    int mHasNewIZombie;
  /* 0x0334 */ public:
    int mHasNewSurvival;
  /* 0x0338 */ public:
    int mPlaceHolderPlayerStats[6];
  /* 0x0350 */ public:
    int mNumPottedPlants;
  /* 0x0358 */ public:
    PottedPlant mPottedPlant[200];

  public:
    PlayerInfo(const PlayerInfo &);

  public:
    PlayerInfo();

  public:
    ~PlayerInfo();

  public:
    void Reset();

  public:
    void AddCoins(int);

  public:
    void SyncSummary(/*DataSync & */ int);

  public:
    void SyncDetails(/*DataSync & */ int);

  public:
    void DeleteUserFiles();

  public:
    void LoadDetails();

  public:
    void SaveDetails();

  public:
    int GetLevel();

  public:
    void SetLevel(int);

  public:
    void ResetChallengeRecord(GameMode);

  public:
    PlayerInfo &operator=(const PlayerInfo &);

  public:
    // void *__vecDelDtor(unsigned int);
};

#endif