#pragma once

#ifndef __LAWNDIALOG_H__
#define __LAWNDIALOG_H__

#include "SexyAppFramework/Dialog.h"

#include "GameButton.h"
#include "LawnApp.h"

class LawnDialog;

class ReanimationWidget : public Sexy::Widget
{   /* Size=0x9c */
    /* 0x0000: fields for Sexy::Widget */
  /* 0x0088 */ public:
    LawnApp *mApp;
  /* 0x008c */ public:
    Reanimation *mReanim;
  /* 0x0090 */ public:
    LawnDialog *mLawnDialog;
  /* 0x0094 */ public:
    float mPosX;
  /* 0x0098 */ public:
    float mPosY;

  public:
    ReanimationWidget(const ReanimationWidget &);

  public:
    ReanimationWidget();

  public:
    virtual ~ReanimationWidget();

  public:
    void Dispose();

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void Update();

  public:
    void AddReanimation(float, float, ReanimationType);

  public:
    ReanimationWidget &operator=(const ReanimationWidget &);
};

class LawnDialog : public Sexy::Dialog
{   /* Size=0x16c */
    /* 0x0000: fields for Sexy::Dialog */
  /* 0x0150 */ public:
    LawnApp *mApp;
  /* 0x0154 */ public:
    int mButtonDelay;
  /* 0x0158 */ public:
    ReanimationWidget *mReanimation;
  /* 0x015c */ public:
    bool mDrawStandardBack;
  /* 0x0160 */ public:
    LawnStoneButton *mLawnYesButton;
  /* 0x0164 */ public:
    LawnStoneButton *mLawnNoButton;
  /* 0x0168 */ public:
    bool mTallBottom;
  /* 0x0169 */ public:
    bool mVerticalCenterText;

  public:
    int GetLeft();

  public:
    int GetWidth();

  public:
    int GetTop();

  public:
    LawnDialog(const LawnDialog &);

  public:
    LawnDialog(LawnApp *, Sexy::Image *, int, bool, const std::string &, const std::string &, const std::string &, int);

  public:
    virtual ~LawnDialog();

  public:
    virtual void SetButtonDelay(int);

  public:
    virtual void Update();

  public:
    virtual void ButtonPress(int);

  public:
    virtual void ButtonDepress(int);

  public:
    virtual void CheckboxChecked(int, bool);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    virtual void AddedToManager(Sexy::WidgetManager *theWidgetManager)
    {
        Sexy::Dialog::AddedToManager(theWidgetManager);
        this->AddWidget(this->mReanimation);
        if (this->mLawnYesButton)
            this->AddWidget(this->mLawnYesButton);
        if (this->mLawnNoButton)
            this->AddWidget(this->mLawnNoButton);
    }

  public:
    virtual void RemovedFromManager(Sexy::WidgetManager *);

  public:
    virtual void Resize(int, int, int, int);

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    void CalcSize(int, int);

  public:
    LawnDialog &operator=(const LawnDialog &);
};

#endif
