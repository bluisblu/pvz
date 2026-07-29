#ifndef __CUTSCENE_H__
#define __CUTSCENE_H__

#include "LawnApp.h"

class CutScene
{ /* Size=0x38 */
  public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Board *mBoard;
    /* 0x0008 */ int mCutsceneTime;
    /* 0x000c */ int mSodTime;
    /* 0x0010 */ int mGraveStoneTime;
    /* 0x0014 */ int mReadySetPlantTime;
    /* 0x0018 */ int mFogTime;
    /* 0x001c */ int mBossTime;
    /* 0x0020 */ int mCrazyDaveTime;
    /* 0x0024 */ int mLawnMowerTime;
    /* 0x0028 */ int mCrazyDaveDialogStart;
    /* 0x002c */ bool mSeedChoosing;
    /* 0x0030 */ ReanimationID mZombiesWonReanimID;
    /* 0x0034 */ bool mPreloaded;
    /* 0x0035 */ bool mPlacedZombies;
    /* 0x0036 */ bool mPlacedLawnItems;

  public:
    CutScene();
    void StartLevelIntro();
    void CancelIntro();
    void Update();
    void AnimateBoard();
    void StartSeedChooser();
    void EndSeedChooser();
    int CalcPosition(int, int, int, int);
    void PlaceStreetZombies();
    void AddGraveStoneParticles();
    void PlaceAZombie(ZombieType, int, int);
    bool CanZombieGoInGridSpot(ZombieType, int, int, bool *[5]);
    bool IsSurvivalRepick();
    bool IsAfterSeedChooser();
    void AddFlowerPots();
    void UpdateZombiesWon();
    void StartZombiesWon();
    bool ShowZombieWalking();
    bool IsCutSceneOver();
    void ZombieWonClick();
    void MouseDown(int, int);
    void KeyDown(Sexy::KeyCode);
    void AdvanceCrazyDaveDialog(bool);
    void ShowShovel();
    bool CanGetPacketUpgrade();
    void FindPlaceForStreetZombies(ZombieType, bool *[5], int &, int &);
    void FindAndPlaceZombie(ZombieType, bool *[5]);
    bool Is2x2Zombie(ZombieType);
    void PreloadResources();
    bool IsBeforePreloading();
    bool IsShowingCrazyDave();
    bool IsNonScrollingCutscene();
    bool IsScrolledLeftAtStart();
    bool IsInShovelTutorial();
    void PlaceLawnItems();
    bool CanGetSecondPacketUpgrade();
};

#endif
