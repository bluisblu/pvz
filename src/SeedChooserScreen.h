#pragma once

#ifndef __SEEDCHOOSERSCREEN_H__
#define __SEEDCHOOSERSCREEN_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/Flags.h"
#include "SexyAppFramework/Insets.h"
#include "SexyAppFramework/KeyCodes.h"
#include "SexyAppFramework/MTRand.h"
#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/WidgetContainer.h"

#include "LawnApp.h"

class LawnApp;

enum ChosenSeedState : int
{
    SEED_FLYING_TO_BANK = 0x0000,
    SEED_IN_BANK = 0x0001,
    SEED_FLYING_TO_CHOOSER = 0x0002,
    SEED_IN_CHOOSER = 0x0003,
    SEED_PACKET_HIDDEN = 0x0004,
};

class ChosenSeed
{ /* Size=0x3c */
  /* 0x0000 */ public:
    int mX;
  /* 0x0004 */ public:
    int mY;
  /* 0x0008 */ public:
    int mTimeStartMotion;
  /* 0x000c */ public:
    int mTimeEndMotion;
  /* 0x0010 */ public:
    int mStartX;
  /* 0x0014 */ public:
    int mStartY;
  /* 0x0018 */ public:
    int mEndX;
  /* 0x001c */ public:
    int mEndY;
  /* 0x0020 */ public:
    SeedType mSeedType;
  /* 0x0024 */ public:
    ChosenSeedState mSeedState;
  /* 0x0028 */ public:
    int mSeedIndexInBank;
  /* 0x002c */ public:
    bool mRefreshing;
  /* 0x0030 */ public:
    int mRefreshCounter;
  /* 0x0034 */ public:
    SeedType mImitaterType;
  /* 0x0038 */ public:
    bool mCrazyDavePicked;
};

enum SeedChooserState : int
{
    CHOOSE_NORMAL = 0x0000,
    CHOOSE_VIEW_LAWN = 0x0001,
};

class SeedChooserScreen : public Sexy::Widget
{   /* Size=0xd40 */
    /* 0x0000: fields for Sexy::Widget */
  /* 0x0088 */ public:
    /* GameButton * */ int mStartButton;
  /* 0x008c */ public:
    /* GameButton * */ int mRandomButton;
  /* 0x0090 */ public:
    /* GameButton * */ int mViewLawnButton;
  /* 0x0094 */ public:
    /* GameButton * */ int mStoreButton;
  /* 0x0098 */ public:
    /* GameButton * */ int mAlmanacButton;
  /* 0x009c */ public:
    /* GameButton * */ int mMenuButton;
  /* 0x00a0 */ public:
    /* GameButton * */ int mImitaterButton;
  /* 0x00a4 */ public:
    ChosenSeed mChosenSeeds[53];
  /* 0x0d10 */ public:
    LawnApp *mApp;
  /* 0x0d14 */ public:
    Board *mBoard;
  /* 0x0d18 */ public:
    int mNumSeedsToChoose;
  /* 0x0d1c */ public:
    int mSeedChooserAge;
  /* 0x0d20 */ public:
    int mSeedsInFlight;
  /* 0x0d24 */ public:
    int mSeedsInBank;
  /* 0x0d28 */ public:
    /* ToolTipWidget * */ int mToolTip;
  /* 0x0d2c */ public:
    int mToolTipSeed;
  /* 0x0d30 */ public:
    int mLastMouseX;
  /* 0x0d34 */ public:
    int mLastMouseY;
  /* 0x0d38 */ public:
    SeedChooserState mChooseState;
  /* 0x0d3c */ public:
    int mViewLawnTime;

  public:
    SeedChooserScreen(const SeedChooserScreen &);

  public:
    SeedChooserScreen();

  public:
    virtual ~SeedChooserScreen();

  public:
    virtual void Update();

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void ButtonPress(int);

  public:
    virtual void ButtonDepress(int);

  public:
    virtual void MouseDown(int, int, int);

  public:
    virtual void MouseUp(int, int, int);

  public:
    virtual void KeyChar(char);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    void GetSeedPositionInChooser(int, int &, int &);

  public:
    void GetSeedPositionInBank(int, int &, int &);

  public:
    SeedType SeedHitTest(int, int);

  public:
    void ClickedSeedInChooser(ChosenSeed &);

  public:
    void ClickedSeedInBank(ChosenSeed &);

  public:
    SeedType FindSeedInBank(int);

  public:
    void EnableStartButton(bool);

  public:
    void RemoveToolTip();

  public:
    void ShowToolTip();

  public:
    unsigned int SeedNotRecommendedToPick(SeedType);

  public:
    bool SeedNotAllowedToPick(SeedType);

  public:
    void CloseSeedChooser();

  public:
    bool PickedPlantType(SeedType);

  public:
    void OnStartButton();

  public:
    bool DisplayRepickWarningDialog(const char *);

  public:
    void UpdateViewLawn();

  public:
    void CancelLawnView();

  public:
    void LandFlyingSeed(ChosenSeed &);

  public:
    void UpdateCursor();

  public:
    bool FlyProtectionCurrentlyPlanted();

  public:
    bool FlyersAreComing();

  public:
    void UpdateAfterPurchase();

  public:
    void UpdateImitaterButton();

  public:
    void CrazyDavePickSeeds();

  public:
    int PickFromWeightedArrayUsingSpecialRandSeed(const /* TodWeightedArray * */ int, int, Sexy::MTRand &);

  public:
    bool CheckSeedUpgrade(SeedType, SeedType);

  public:
    void PickRandomSeeds();

  public:
    bool Has7Rows();

  public:
    SeedChooserScreen &operator=(const SeedChooserScreen &);

  public:
    // void __local_vftable_ctor_closure();

  public:
    // virtual void *__vecDelDtor(unsigned int);
};

#endif // __SEEDCHOOSERSCREEN_H__