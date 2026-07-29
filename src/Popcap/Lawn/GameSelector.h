#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/Widget.h"

#include "Enums.h"
#include "LawnApp.h"

class GameSelector : public Sexy::Widget, public Sexy::ButtonListener
{ /* Size=0x12c */
  public:
    /* 0x0000: fields for Sexy::Widget */
    /* 0x0088: fields for Sexy::ButtonListener */
    /* 0x008c */ LawnApp *mApp;
    /* 0x0090 */ Sexy::DialogButton *mAdventureButton;
    /* 0x0094 */ Sexy::DialogButton *mMinigameButton;
    /* 0x0098 */ Sexy::DialogButton *mPuzzleButton;
    /* 0x009c */ Sexy::DialogButton *mOptionsButton;
    /* 0x00a0 */ Sexy::DialogButton *mQuitButton;
    /* 0x00a4 */ Sexy::DialogButton *mHelpButton;
    /* 0x00a8 */ Sexy::DialogButton *mStoreButton;
    /* 0x00ac */ Sexy::DialogButton *mAlmanacButton;
    /* 0x00b0 */ Sexy::DialogButton *mZenGardenButton;
    /* 0x00b4 */ Sexy::DialogButton *mSurvivalButton;
    /* 0x00b8 */ Sexy::DialogButton *mChangeUserButton;
    /* 0x00bc */ Sexy::Widget *mOverlayWidget;
    /* 0x00c0 */ bool mStartingGame;
    /* 0x00c4 */ int mStartingGameCounter;
    /* 0x00c8 */ bool mMinigamesLocked;
    /* 0x00c9 */ bool mPuzzleLocked;
    /* 0x00ca */ bool mSurvivalLocked;
    /* 0x00cb */ bool mShowStartButton;
    /* 0x00cc */ ParticleSystemID mTrophyParticleID;
    /* 0x00d0 */ ReanimationID mSelectorReanimID;
    /* 0x00d4 */ ReanimationID mCloudReanimID[6];
    /* 0x00ec */ int mCloudCounter[6];
    /* 0x0104 */ ReanimationID mFlowerReanimID[3];
    /* 0x0110 */ ReanimationID mLeafReanimID;
    /* 0x0114 */ ReanimationID mHandReanimID;
    /* 0x0118 */ int mLeafCounter;
    /* 0x011c */ SelectorAnimState mSelectorState;
    /* 0x0120 */ int mLevel;
    /* 0x0124 */ bool mLoading;
    /* 0x0128 */ /* ToolTipWidget * */ int mToolTip;

  public:
    GameSelector(const GameSelector &);
    GameSelector(LawnApp *);
    virtual ~GameSelector();
    void SyncProfile(bool);
    virtual void Draw(Sexy::Graphics *);
    virtual void DrawOverlay(Sexy::Graphics *);
    virtual void Update();
    virtual void AddedToManager(Sexy::WidgetManager *);
    virtual void RemovedFromManager(Sexy::WidgetManager *);
    virtual void OrderInManagerChanged();
    virtual void ButtonMouseEnter(int);
    virtual void ButtonPress(int, int);
    virtual void ButtonDepress(int);
    virtual void KeyDown(Sexy::KeyCode);
    virtual void KeyChar(char);
    virtual void MouseDown(int, int, int);
    void TrackButton(Sexy::DialogButton *, const char *, float, float);
    void SyncButtons();
    void AddTrophySparkle();
    void ClickedAdventure();
    void UpdateTooltip();
    GameSelector &operator=(const GameSelector &);
};

#endif
