#pragma once

#ifndef __AWARDSCREEN_H__
#define __AWARDSCREEN_H__

#include "SexyAppFramework/Widget.h"

#include "LawnApp.h"

class LawnApp;

#ifndef E_AWARD_TYPE
#define E_AWARD_TYPE
enum AwardType : int
{
    AWARD_FOR_LEVEL = 0x0000,
    AWARD_CREDITS_ZOMBIE_NOTE = 0x0001,
};
#endif

class AwardScreen : public Sexy::Widget
{   /* Size=0x9c */
    /* 0x0000: fields for Sexy::Widget */
  /* 0x0088 */ public:
    /*GameButton * */ int mStartButton;
  /* 0x008c */ public:
    /*GameButton * */ int mMenuButton;
  /* 0x0090 */ public:
    LawnApp *mApp;
  /* 0x0094 */ public:
    int mFadeInCounter;
  /* 0x0098 */ public:
    AwardType mAwardType;

  public:
    AwardScreen(const AwardScreen &);

  public:
    AwardScreen(LawnApp *, AwardType);

  public:
    virtual ~AwardScreen();

  public:
    virtual void Update();

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void Resize(int, int, int, int);

  public:
    virtual void AddedToManager(Sexy::WidgetManager *);

  public:
    virtual void RemovedFromManager(Sexy::WidgetManager *);

  public:
    virtual void KeyChar(char);

  public:
    virtual void MouseUp(int, int, int);

  public:
    virtual void MouseDown(int, int, int);

  public:
    void DrawAwardSeed(Sexy::Graphics *);

  public:
    void DrawBottom(Sexy::Graphics *, const std::string &, const std::string &, const std::string &);

  public:
    void StartButtonPressed();

  public:
    AwardScreen &operator=(const AwardScreen &);
};

#endif