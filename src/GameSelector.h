#pragma once

#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/Widget.h"

#include "LawnApp.h"

#ifndef E_PARTICLE_SYSTEM_ID
#define E_PARTICLE_SYSTEM_ID
enum ParticleSystemID : int
{
    PARTICLESYSTEMID_NULL = 0x0000,
};
#endif

#ifndef E_REANIMATION_ID
#define E_REANIMATION_ID
enum ReanimationID : int
{
    REANIMATIONID_NULL = 0x0000,
};
#endif

enum SelectorAnimState : int
{
    SELECTOR_OPEN = 0x0000,
    SELECTOR_NEW_USER = 0x0001,
    SELECTOR_SHOW_SIGN = 0x0002,
    SELECTOR_IDLE = 0x0003,
};

class GameSelector : public Sexy::Widget, public Sexy::ButtonListener
{   /* Size=0x12c */
    /* 0x0000: fields for Sexy::Widget */
    /* 0x0088: fields for Sexy::ButtonListener */
  /* 0x008c */ public:
    LawnApp *mApp;
  /* 0x0090 */ public:
    Sexy::DialogButton *mAdventureButton;
  /* 0x0094 */ public:
    Sexy::DialogButton *mMinigameButton;
  /* 0x0098 */ public:
    Sexy::DialogButton *mPuzzleButton;
  /* 0x009c */ public:
    Sexy::DialogButton *mOptionsButton;
  /* 0x00a0 */ public:
    Sexy::DialogButton *mQuitButton;
  /* 0x00a4 */ public:
    Sexy::DialogButton *mHelpButton;
  /* 0x00a8 */ public:
    Sexy::DialogButton *mStoreButton;
  /* 0x00ac */ public:
    Sexy::DialogButton *mAlmanacButton;
  /* 0x00b0 */ public:
    Sexy::DialogButton *mZenGardenButton;
  /* 0x00b4 */ public:
    Sexy::DialogButton *mSurvivalButton;
  /* 0x00b8 */ public:
    Sexy::DialogButton *mChangeUserButton;
  /* 0x00bc */ public:
    Sexy::Widget *mOverlayWidget;
  /* 0x00c0 */ public:
    bool mStartingGame;
  /* 0x00c4 */ public:
    int mStartingGameCounter;
  /* 0x00c8 */ public:
    bool mMinigamesLocked;
  /* 0x00c9 */ public:
    bool mPuzzleLocked;
  /* 0x00ca */ public:
    bool mSurvivalLocked;
  /* 0x00cb */ public:
    bool mShowStartButton;
  /* 0x00cc */ public:
    ParticleSystemID mTrophyParticleID;
  /* 0x00d0 */ public:
    ReanimationID mSelectorReanimID;
  /* 0x00d4 */ public:
    ReanimationID mCloudReanimID[6];
  /* 0x00ec */ public:
    int mCloudCounter[6];
  /* 0x0104 */ public:
    ReanimationID mFlowerReanimID[3];
  /* 0x0110 */ public:
    ReanimationID mLeafReanimID;
  /* 0x0114 */ public:
    ReanimationID mHandReanimID;
  /* 0x0118 */ public:
    int mLeafCounter;
  /* 0x011c */ public:
    SelectorAnimState mSelectorState;
  /* 0x0120 */ public:
    int mLevel;
  /* 0x0124 */ public:
    bool mLoading;
  /* 0x0128 */ public:
    /* ToolTipWidget * */ int mToolTip;

  public:
    GameSelector(const GameSelector &);

  public:
    GameSelector(LawnApp *);

  public:
    virtual ~GameSelector();

  public:
    void SyncProfile(bool);

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void DrawOverlay(Sexy::Graphics *);

  public:
    virtual void Update();

  public:
    virtual void AddedToManager(Sexy::WidgetManager *);

  public:
    virtual void RemovedFromManager(Sexy::WidgetManager *);

  public:
    virtual void OrderInManagerChanged();

  public:
    virtual void ButtonMouseEnter(int);

  public:
    virtual void ButtonPress(int, int);

  public:
    virtual void ButtonDepress(int);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    virtual void KeyChar(char);

  public:
    virtual void MouseDown(int, int, int);

  public:
    void TrackButton(Sexy::DialogButton *, const char *, float, float);

  public:
    void SyncButtons();

  public:
    void AddTrophySparkle();

  public:
    void ClickedAdventure();

  public:
    void UpdateTooltip();

  public:
    GameSelector &operator=(const GameSelector &);
};

#endif