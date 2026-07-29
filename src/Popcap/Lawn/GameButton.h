#ifndef __GAMEBUTTON_H__
#define __GAMEBUTTON_H__

#include "SexyAppFramework/DialogButton.h"

#include "LawnApp.h"

class LawnStoneButton : public Sexy::DialogButton
{ /* Size=0x138 */
  public:
    /* 0x0000: fields for Sexy::DialogButton */
    LawnStoneButton(const LawnStoneButton &);
    LawnStoneButton(Sexy::Image *, int, Sexy::ButtonListener *);
    virtual void Draw(Sexy::Graphics *);
    void SetLabel(const std::string &);
    virtual ~LawnStoneButton();
    LawnStoneButton &operator=(const LawnStoneButton &);
};

class GameButton
{ /* Size=0x130 */
  public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Sexy::Widget *mParentWidget;
    /* 0x0008 */ int mX;
    /* 0x000c */ int mY;
    /* 0x0010 */ int mWidth;
    /* 0x0014 */ int mHeight;
    /* 0x0018 */ bool mIsOver;
    /* 0x0019 */ bool mIsDown;
    /* 0x001a */ bool mDisabled;
    /* 0x001c */ Sexy::Color mColors[6];
    /* 0x007c */ int mId;
    /* 0x0080 */ std::string mLabel;
    /* 0x009c */ int mLabelJustify;
    /* 0x00a0 */ Sexy::Font *mFont;
    /* 0x00a4 */ Sexy::Image *mButtonImage;
    /* 0x00a8 */ Sexy::Image *mOverImage;
    /* 0x00ac */ Sexy::Image *mDownImage;
    /* 0x00b0 */ Sexy::Image *mDisabledImage;
    /* 0x00b4 */ Sexy::Image *mOverOverlayImage;
    /* 0x00b8 */ Sexy::TRect<int> mNormalRect;
    /* 0x00c8 */ Sexy::TRect<int> mOverRect;
    /* 0x00d8 */ Sexy::TRect<int> mDownRect;
    /* 0x00e8 */ Sexy::TRect<int> mDisabledRect;
    /* 0x00f8 */ bool mInverted;
    /* 0x00f9 */ bool mBtnNoDraw;
    /* 0x00fa */ bool mFrameNoDraw;
    /* 0x0100 */ double mOverAlpha;
    /* 0x0108 */ double mOverAlphaSpeed;
    /* 0x0110 */ double mOverAlphaFadeInSpeed;
    /* 0x0118 */ bool mDrawStoneButton;
    /* 0x011c */ int mTextOffsetX;
    /* 0x0120 */ int mTextOffsetY;
    /* 0x0124 */ int mButtonOffsetX;
    /* 0x0128 */ int mButtonOffsetY;

  public:
    GameButton(const GameButton &);
    GameButton(int);
    ~GameButton();
    bool HaveButtonImage(Sexy::Image *, const Sexy::TRect<int> &);
    void DrawButtonImage(Sexy::Graphics *, Sexy::Image *, const Sexy::TRect<int> *, int, int);
    void SetFont(Sexy::Font *);
    bool IsButtonDown();
    void Draw(Sexy::Graphics *);
    void SetDisabled(bool);
    bool IsMouseOver();
    void Update();
    void Resize(int, int, int, int);
    void SetLabel(const std::string &);
    GameButton &operator=(const GameButton &);
};

#endif
