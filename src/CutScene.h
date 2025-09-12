#pragma once

#ifndef __CUTSCENE_H__
#define __CUTSCENE_H__

#include "LawnApp.h"

class CutScene
{ /* Size=0x38 */
  /* 0x0000 */ public:
    LawnApp *mApp;
  /* 0x0004 */ public:
    Board *mBoard;
  /* 0x0008 */ public:
    int mCutsceneTime;
  /* 0x000c */ public:
    int mSodTime;
  /* 0x0010 */ public:
    int mGraveStoneTime;
  /* 0x0014 */ public:
    int mReadySetPlantTime;
  /* 0x0018 */ public:
    int mFogTime;
  /* 0x001c */ public:
    int mBossTime;
  /* 0x0020 */ public:
    int mCrazyDaveTime;
  /* 0x0024 */ public:
    int mLawnMowerTime;
  /* 0x0028 */ public:
    int mCrazyDaveDialogStart;
  /* 0x002c */ public:
    bool mSeedChoosing;
  /* 0x0030 */ public:
    ReanimationID mZombiesWonReanimID;
  /* 0x0034 */ public:
    bool mPreloaded;
  /* 0x0035 */ public:
    bool mPlacedZombies;
  /* 0x0036 */ public:
    bool mPlacedLawnItems;

  public:
    CutScene();

  public:
    void StartLevelIntro();

  public:
    void CancelIntro();

  public:
    void Update();

  public:
    void AnimateBoard();

  public:
    void StartSeedChooser();

  public:
    void EndSeedChooser();

  public:
    int CalcPosition(int, int, int, int);

  public:
    void PlaceStreetZombies();

  public:
    void AddGraveStoneParticles();

  public:
    void PlaceAZombie(ZombieType, int, int);

  public:
    bool CanZombieGoInGridSpot(ZombieType, int, int, bool *[5]);

  public:
    bool IsSurvivalRepick();

  public:
    bool IsAfterSeedChooser();

  public:
    void AddFlowerPots();

  public:
    void UpdateZombiesWon();

  public:
    void StartZombiesWon();

  public:
    bool ShowZombieWalking();

  public:
    bool IsCutSceneOver();

  public:
    void ZombieWonClick();

  public:
    void MouseDown(int, int);

  public:
    void KeyDown(Sexy::KeyCode);

  public:
    void AdvanceCrazyDaveDialog(bool);

  public:
    void ShowShovel();

  public:
    bool CanGetPacketUpgrade();

  public:
    void FindPlaceForStreetZombies(ZombieType, bool *[5], int &, int &);

  public:
    void FindAndPlaceZombie(ZombieType, bool *[5]);

  public:
    bool Is2x2Zombie(ZombieType);

  public:
    void PreloadResources();

  public:
    bool IsBeforePreloading();

  public:
    bool IsShowingCrazyDave();

  public:
    bool IsNonScrollingCutscene();

  public:
    bool IsScrolledLeftAtStart();

  public:
    bool IsInShovelTutorial();

  public:
    void PlaceLawnItems();

  public:
    bool CanGetSecondPacketUpgrade();
};

#endif