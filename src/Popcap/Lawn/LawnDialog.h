#pragma once

#ifndef __LAWNDIALOG_H__
#define __LAWNDIALOG_H__

#include "SexyAppFramework/Dialog.h"

#include "GameButton.h"
#include "LawnApp.h"

class LawnDialog;

class ReanimationWidget : public Sexy::Widget
{   /* Size=0x9c */
public:
    /* 0x0000: fields for Sexy::Widget */
  /* 0x0088 */ LawnApp *mApp;
  /* 0x008c */ Reanimation *mReanim;
  /* 0x0090 */ LawnDialog *mLawnDialog;
  /* 0x0094 */ float mPosX;
  /* 0x0098 */ float mPosY;
public:
    ReanimationWidget(const ReanimationWidget &);
    ReanimationWidget();
    virtual ~ReanimationWidget();
    void Dispose();
    virtual void Draw(Sexy::Graphics *);
    virtual void Update();
    void AddReanimation(float, float, ReanimationType);
    ReanimationWidget &operator=(const ReanimationWidget &);
};

class LawnDialog : public Sexy::Dialog
{   /* Size=0x16c */
public:
    /* 0x0000: fields for Sexy::Dialog */
  /* 0x0150 */ LawnApp *mApp;
  /* 0x0154 */ int mButtonDelay;
  /* 0x0158 */ ReanimationWidget *mReanimation;
  /* 0x015c */ bool mDrawStandardBack;
  /* 0x0160 */ LawnStoneButton *mLawnYesButton;
  /* 0x0164 */ LawnStoneButton *mLawnNoButton;
  /* 0x0168 */ bool mTallBottom;
  /* 0x0169 */ bool mVerticalCenterText;
public:
    int GetLeft();
    int GetWidth();
    int GetTop();
    LawnDialog(const LawnDialog &);
    LawnDialog(LawnApp *, Sexy::Image *, int, bool, const std::string &, const std::string &, const std::string &, int);
    virtual ~LawnDialog();
    virtual void SetButtonDelay(int);
    virtual void Update();
    virtual void ButtonPress(int);
    virtual void ButtonDepress(int);
    virtual void CheckboxChecked(int, bool);
    virtual void KeyDown(Sexy::KeyCode);
    virtual void AddedToManager(Sexy::WidgetManager *theWidgetManager)
    {
        Sexy::Dialog::AddedToManager(theWidgetManager);
        AddWidget(mReanimation);
        if (mLawnYesButton)
            AddWidget(mLawnYesButton);
        if (mLawnNoButton)
            AddWidget(mLawnNoButton);
    }
    virtual void RemovedFromManager(Sexy::WidgetManager *);
    virtual void Resize(int, int, int, int);
    virtual void Draw(Sexy::Graphics *);
    void CalcSize(int, int);
    LawnDialog &operator=(const LawnDialog &);
};

#endif
