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
public:
  /* 0x0000 */ int mX;
  /* 0x0004 */ int mY;
  /* 0x0008 */ int mTimeStartMotion;
  /* 0x000c */ int mTimeEndMotion;
  /* 0x0010 */ int mStartX;
  /* 0x0014 */ int mStartY;
  /* 0x0018 */ int mEndX;
  /* 0x001c */ int mEndY;
  /* 0x0020 */ SeedType mSeedType;
  /* 0x0024 */ ChosenSeedState mSeedState;
  /* 0x0028 */ int mSeedIndexInBank;
  /* 0x002c */ bool mRefreshing;
  /* 0x0030 */ int mRefreshCounter;
  /* 0x0034 */ SeedType mImitaterType;
  /* 0x0038 */ bool mCrazyDavePicked;
};

enum SeedChooserState : int
{
    CHOOSE_NORMAL = 0x0000,
    CHOOSE_VIEW_LAWN = 0x0001,
};

class SeedChooserScreen : public Sexy::Widget
{   /* Size=0xd40 */
public:
    /* 0x0000: fields for Sexy::Widget */
  /* 0x0088 */ /* GameButton * */ int mStartButton;
  /* 0x008c */ /* GameButton * */ int mRandomButton;
  /* 0x0090 */ /* GameButton * */ int mViewLawnButton;
  /* 0x0094 */ /* GameButton * */ int mStoreButton;
  /* 0x0098 */ /* GameButton * */ int mAlmanacButton;
  /* 0x009c */ /* GameButton * */ int mMenuButton;
  /* 0x00a0 */ /* GameButton * */ int mImitaterButton;
  /* 0x00a4 */ ChosenSeed mChosenSeeds[53];
  /* 0x0d10 */ LawnApp *mApp;
  /* 0x0d14 */ Board *mBoard;
  /* 0x0d18 */ int mNumSeedsToChoose;
  /* 0x0d1c */ int mSeedChooserAge;
  /* 0x0d20 */ int mSeedsInFlight;
  /* 0x0d24 */ int mSeedsInBank;
  /* 0x0d28 */ /* ToolTipWidget * */ void *mToolTip;
  /* 0x0d2c */ int mToolTipSeed;
  /* 0x0d30 */ int mLastMouseX;
  /* 0x0d34 */ int mLastMouseY;
  /* 0x0d38 */ SeedChooserState mChooseState;
  /* 0x0d3c */ int mViewLawnTime;
public:
    SeedChooserScreen(const SeedChooserScreen &);
    SeedChooserScreen();
    virtual ~SeedChooserScreen();
    virtual void Update();
    virtual void Draw(Sexy::Graphics *);
    virtual void ButtonPress(int);
    virtual void ButtonDepress(int);
    virtual void MouseDown(int, int, int);
    virtual void MouseUp(int, int, int);
    virtual void KeyChar(char);
    virtual void KeyDown(Sexy::KeyCode);
    void GetSeedPositionInChooser(int, int &, int &);
    void GetSeedPositionInBank(int, int &, int &);
    SeedType SeedHitTest(int, int);
    void ClickedSeedInChooser(ChosenSeed &);
    void ClickedSeedInBank(ChosenSeed &);
    SeedType FindSeedInBank(int);
    void EnableStartButton(bool);
    void RemoveToolTip();
    void ShowToolTip();
    unsigned int SeedNotRecommendedToPick(SeedType);
    bool SeedNotAllowedToPick(SeedType);
    void CloseSeedChooser();
    bool PickedPlantType(SeedType);
    void OnStartButton();
    bool DisplayRepickWarningDialog(const char *);
    void UpdateViewLawn();
    void CancelLawnView();
    void LandFlyingSeed(ChosenSeed &);
    void UpdateCursor();
    bool FlyProtectionCurrentlyPlanted();
    bool FlyersAreComing();
    void UpdateAfterPurchase();
    void UpdateImitaterButton();
    void CrazyDavePickSeeds();
    int PickFromWeightedArrayUsingSpecialRandSeed(const /* TodWeightedArray * */ void *, int, Sexy::MTRand &);
    bool CheckSeedUpgrade(SeedType, SeedType);
    void PickRandomSeeds();
    bool Has7Rows();
    SeedChooserScreen &operator=(const SeedChooserScreen &);
};

#endif // __SEEDCHOOSERSCREEN_H__
