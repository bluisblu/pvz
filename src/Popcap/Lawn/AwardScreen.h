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
    AWARD_FOR_LEVEL           = 0x0000,
    AWARD_CREDITS_ZOMBIE_NOTE = 0x0001,
};
#endif

class AwardScreen : public Sexy::Widget
{ /* Size=0x9c */
  public:
    /* 0x0000: fields for Sexy::Widget */
    /* 0x0088 */ /*GameButton * */ void *mStartButton;
    /* 0x008c */ /*GameButton * */ void *mMenuButton;
    /* 0x0090 */ LawnApp *mApp;
    /* 0x0094 */ int mFadeInCounter;
    /* 0x0098 */ AwardType mAwardType;

  public:
    AwardScreen(const AwardScreen &);
    AwardScreen(LawnApp *, AwardType);
    virtual ~AwardScreen();
    virtual void Update();
    virtual void Draw(Sexy::Graphics *);
    virtual void Resize(int, int, int, int);
    virtual void AddedToManager(Sexy::WidgetManager *);
    virtual void RemovedFromManager(Sexy::WidgetManager *);
    virtual void KeyChar(char);
    virtual void MouseUp(int, int, int);
    virtual void MouseDown(int, int, int);
    void DrawAwardSeed(Sexy::Graphics *);
    void DrawBottom(Sexy::Graphics *, const std::string &, const std::string &,
                    const std::string &);
    void StartButtonPressed();
    AwardScreen &operator=(const AwardScreen &);
};

#endif
