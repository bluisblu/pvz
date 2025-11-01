#pragma once

#ifndef __GAMEBUTTON_H__
#define __GAMEBUTTON_H__

#include "SexyAppFramework/DialogButton.h"

#include "LawnApp.h"

class LawnStoneButton : public Sexy::DialogButton { /* Size=0x138 */
  /* 0x0000: fields for Sexy::DialogButton */

  public: LawnStoneButton(const LawnStoneButton&);
  public: LawnStoneButton(Sexy::Image*, int, Sexy::ButtonListener*);
  public: virtual void Draw(Sexy::Graphics*);
  public: void SetLabel(const std::string&);
  public: virtual ~LawnStoneButton();
  public: LawnStoneButton& operator=(const LawnStoneButton&);
};

class GameButton { /* Size=0x130 */
  /* 0x0000 */ public: LawnApp* mApp;
  /* 0x0004 */ public: Sexy::Widget* mParentWidget;
  /* 0x0008 */ public: int mX;
  /* 0x000c */ public: int mY;
  /* 0x0010 */ public: int mWidth;
  /* 0x0014 */ public: int mHeight;
  /* 0x0018 */ public: bool mIsOver;
  /* 0x0019 */ public: bool mIsDown;
  /* 0x001a */ public: bool mDisabled;
  /* 0x001c */ public: Sexy::Color mColors[6];
  /* 0x007c */ public: int mId;
  /* 0x0080 */ public: std::string mLabel;
  /* 0x009c */ public: int mLabelJustify;
  /* 0x00a0 */ public: Sexy::Font* mFont;
  /* 0x00a4 */ public: Sexy::Image* mButtonImage;
  /* 0x00a8 */ public: Sexy::Image* mOverImage;
  /* 0x00ac */ public: Sexy::Image* mDownImage;
  /* 0x00b0 */ public: Sexy::Image* mDisabledImage;
  /* 0x00b4 */ public: Sexy::Image* mOverOverlayImage;
  /* 0x00b8 */ public: Sexy::TRect<int> mNormalRect;
  /* 0x00c8 */ public: Sexy::TRect<int> mOverRect;
  /* 0x00d8 */ public: Sexy::TRect<int> mDownRect;
  /* 0x00e8 */ public: Sexy::TRect<int> mDisabledRect;
  /* 0x00f8 */ public: bool mInverted;
  /* 0x00f9 */ public: bool mBtnNoDraw;
  /* 0x00fa */ public: bool mFrameNoDraw;
  /* 0x0100 */ public: double mOverAlpha;
  /* 0x0108 */ public: double mOverAlphaSpeed;
  /* 0x0110 */ public: double mOverAlphaFadeInSpeed;
  /* 0x0118 */ public: bool mDrawStoneButton;
  /* 0x011c */ public: int mTextOffsetX;
  /* 0x0120 */ public: int mTextOffsetY;
  /* 0x0124 */ public: int mButtonOffsetX;
  /* 0x0128 */ public: int mButtonOffsetY;

  public: GameButton(const GameButton&);
  public: GameButton(int);
  public: ~GameButton();
  public: bool HaveButtonImage(Sexy::Image*, const Sexy::TRect<int>&);
  public: void DrawButtonImage(Sexy::Graphics*, Sexy::Image*, const Sexy::TRect<int>*, int, int);
  public: void SetFont(Sexy::Font*);
  public: bool IsButtonDown();
  public: void Draw(Sexy::Graphics*);
  public: void SetDisabled(bool);
  public: bool IsMouseOver();
  public: void Update();
  public: void Resize(int, int, int, int);
  public: void SetLabel(const std::string&);
  public: GameButton& operator=(const GameButton&);
};

#endif
