#pragma once

#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

class Sexy::Color;
class Sexy::TPoint<int>;
class Sexy::TRect<int>;
class Sexy::ButtonListener;
class Sexy::DialogListener;
struct Sexy::Ratio;
class Sexy::TriVertex;
class Sexy::Graphics;
class Sexy::GraphicsState;
struct Sexy::Edge;
class Sexy::Font;
class Sexy::FlagsMod;
class Sexy::ModalFlags;
class Sexy::Widget;
class Sexy::WidgetContainer;
class Sexy::Insets;
class Sexy::SoundManager;
class Sexy::SoundInstance;
struct TodAllocator;
class TodList<enum ParticleID>;
class TodList<enum ParticleEmitterID>;
class Sexy::MTRand;
class TodList<ReanimCacheImageVariation>;
class Sexy::Dialog;
class Sexy::PreModalInfo;
class Sexy::WidgetManager;
class GameObject;
class ZombieDrawPosition;
class PlantsOnLawn;
class ReanimatorDefinition;
class ReanimatorTransform;
class AttachEffect;
class AttacherInfo;
class Sexy::InternetManager;
class Sexy::SexyApp;
class ReanimCacheImageVariation;
class ReanimatorCache;
class PlayerInfo;
class ReanimationWidget;
class LawnDialog;
class PopDRMComm;
class TodParticleDefinition;
class TodParticle;
class TodParticleEmitter;
class FloatParameterTrackNode;
class FloatParameterTrack;
class ParticleField;
class TodEmitterDefinition;
class ReanimatorTrack;
class MagnetItem;
class TodWeightedGridArray;
struct tagMSG;
class Sexy::SharedImage;
class Sexy::WidgetSafeDeleteInfo;
class Sexy::Buffer;
class Sexy::SharedImageRef;
class Sexy::SexyAppBase;
class HitResult;
struct Sexy::AnimInfo;
struct Sexy::Span;
class FoleyInstance;
struct Sexy::SexyRGBA;
class Music;
class DataArray<Zombie>::DataArrayItem;
class DataArray<Plant>::DataArrayItem;
class DataArray<LawnMower>::DataArrayItem;
class Sexy::SexyTransform2D;
class Sexy::DialogButton;
class Sexy::ButtonWidget;
class LawnStoneButton;
class SpecialGridPlacement;
class TodTriangleGroup;
class Attachment;
class AttachmentHolder;
class EffectSystem;
class StoreScreen;
class NewLawnButton;
class GameButton;
class DataArray<Coin>::DataArrayItem;
class DataArray<GridItem>::DataArrayItem;
struct TodListNode<enum ParticleEmitterID>;
class DataArray<TodParticleEmitter>::DataArrayItem;
class ProfileMgr;
struct Sexy::StringLessNoCase;
class PottedPlant;
class TypingCheck;
class TrailDefinition;
class Trail;
class DataArray<Trail>::DataArrayItem;
class Sexy::SexyVector2;
class ToolTipWidget;
struct PFILE;
class PakCollection;
class PakRecord;
class Sexy::TRect<double>;
struct IUnknown;
class TodParticleSystem;
class TodParticleHolder;
class ParticleRenderParams;
struct TodListNode<enum ParticleID>;
class DataArray<TodParticleSystem>::DataArrayItem;
class DataArray<TodParticle>::DataArrayItem;
class Sexy::SexyMatrix3;
class TodFoley;
struct _DDCOLORKEY;
struct _DDBLTFX;
struct _DDSCAPS;
struct _DDSCAPS2;
struct _DDCAPS_DX7;
struct _DDPIXELFORMAT;
struct _DDOVERLAYFX;
struct _DDBLTBATCH;
struct _DDSURFACEDESC;
struct _DDSURFACEDESC2;
struct IDirectDrawSurface7;
struct tagDDDEVICEIDENTIFIER2;
struct IDirectDraw7;
class Sexy::D3DTester;
class Sexy::DDInterface;
struct IDirectDrawSurface;
class Sexy::MemoryImage;
class Sexy::Image;
struct IDirectDrawClipper;
struct IDirectDrawPalette;
struct IDirectDraw;
class Sexy::NativeDisplay;
class Sexy::ResourceManager;
struct Sexy::ResourceManager::BaseRes;
struct Sexy::ResourceManager::ImageRes;
struct Sexy::ResourceManager::SoundRes;
struct Sexy::ResourceManager::FontRes;
class Sexy::DDImage;
struct _D3DVECTOR;
struct _D3DVIEWPORT7;
class TodWeightedArray;
class Sexy::EncodingParser;
struct IDirect3D7;
struct _D3DDeviceDesc7;
struct _D3DRECT;
struct _D3DMATRIX;
struct _D3DMATERIAL7;
struct _D3DLIGHT7;
struct _D3DCLIPSTATUS;
struct _D3DDRAWPRIMITIVESTRIDEDDATA;
struct _D3DVERTEXBUFFERDESC;
struct IDirect3DVertexBuffer7;
struct IDirect3DDevice7;
class Sexy::D3DInterface;
class TitleScreen;
class Sexy::HyperlinkWidget;
class ChallengeScreen;
class ChallengeDefinition;
class ReanimatorTrackInstance;
class DataArray<Reanimation>::DataArrayItem;
class ChosenSeed;
class SeedChooserScreen;
class Coin;
class SeedPacket;
class SeedBank;
class MessageWidget;
class CursorPreview;
class TrailHolder;
class DataArray<Projectile>::DataArrayItem;
class DataArray<Attachment>::DataArrayItem;
struct tagPOINT;
struct _LIST_ENTRY;
struct HWND__;
struct _RTL_CRITICAL_SECTION;
struct HKEY__;
struct HICON__;
struct _iobuf;
struct _RTL_CRITICAL_SECTION_DEBUG;
struct tagRECT;
class ReanimAtlas;
class ReanimationHolder;
class ReanimatorFrameTime;
class ReanimAtlasImage;
struct TodListNode<ReanimCacheImageVariation>;
class ProjectileDefinition;
class DataSync;
class DataWriter;
class DataReader;
struct tagPALETTEENTRY;
struct tagSIZE;
struct _RGNDATA;
struct HFONT__;
struct HBITMAP__;
class Sexy::Transform;
class Sexy::SexyVector3;
struct HDC__;
class PoolEffect;
class AwardScreen;
class LevelStats;
class Sexy::MusicInterface;
class Zombie;
class CutScene;
class Sexy::WinInetHTTPTransfer;
class Challenge;
class GameSelector;
class CreditScreen;
class Sexy::BetaSupport;
class Reanimation;
class Sexy::XMLParser;
class Sexy::XMLElement;
class GridItem;
class CursorObject;
class ZenGarden;
class CreditsTiming;
class Plant;
class BeghouledBoardState;
class Projectile;
class LawnMower;
class ZombiePicker;
class BungeeDropGrid;
class RenderItem;
class LawnApp;
class AlmanacDialog;
class Board;
struct _GUID;

class Sexy::FlagsMod
{ /* Size=0x8 */
  /* 0x0000 */ public:
    int32_t mAddFlags;
  /* 0x0004 */ public:
    int32_t mRemoveFlags;

  public:
    void FlagsMod();
};

class Sexy::Insets
{ /* Size=0x10 */
  /* 0x0000 */ public:
    int32_t mLeft;
  /* 0x0004 */ public:
    int32_t mTop;
  /* 0x0008 */ public:
    int32_t mRight;
  /* 0x000c */ public:
    int32_t mBottom;

  public:
    void Insets(const Sexy::Insets &);

  public:
    void Insets(int32_t, int32_t, int32_t, int32_t);

  public:
    void Insets();
};

class Sexy::WidgetContainer
{ /* Size=0x54 */
  /* 0x0004 */ public:
    std::list<Sexy::Widget *, std::allocator<Sexy::Widget *>> mWidgets;
  /* 0x0010 */ public:
    Sexy::WidgetManager *mWidgetManager;
  /* 0x0014 */ public:
    Sexy::WidgetContainer *mParent;
  /* 0x0018 */ public:
    bool mUpdateIteratorModified;
  /* 0x001c */ public:
    std::list<Sexy::Widget *, std::allocator<Sexy::Widget *>>::_Iterator<1> mUpdateIterator;
  /* 0x0024 */ public:
    uint32_t mLastWMUpdateCount;
  /* 0x0028 */ public:
    int32_t mUpdateCnt;
  /* 0x002c */ public:
    bool mDirty;
  /* 0x0030 */ public:
    int32_t mX;
  /* 0x0034 */ public:
    int32_t mY;
  /* 0x0038 */ public:
    int32_t mWidth;
  /* 0x003c */ public:
    int32_t mHeight;
  /* 0x0040 */ public:
    bool mHasAlpha;
  /* 0x0041 */ public:
    bool mClip;
  /* 0x0044 */ public:
    Sexy::FlagsMod mWidgetFlagsMod;
  /* 0x004c */ public:
    int32_t mPriority;
  /* 0x0050 */ public:
    int32_t mZOrder;

  public:
    Sexy::Widget *GetWidgetAtHelper(int32_t, int32_t, int32_t, bool *, int32_t *, int32_t *);

  public:
    bool IsBelowHelper(Sexy::Widget *, Sexy::Widget *, bool *);

  public:
    void InsertWidgetHelper(const std::list<Sexy::Widget *, std::allocator<Sexy::Widget *>>::_Iterator<1> &,
                            Sexy::Widget *);

  public:
    void WidgetContainer(const Sexy::WidgetContainer &);

  public:
    void WidgetContainer();

  public:
    virtual ~WidgetContainer();

  public:
    virtual Sexy::TRect<int> GetRect();

  public:
    virtual bool Intersects(Sexy::WidgetContainer *);

  public:
    virtual void AddWidget(Sexy::Widget *);

  public:
    virtual void RemoveWidget(Sexy::Widget *);

  public:
    virtual bool HasWidget(Sexy::Widget *);

  public:
    virtual void DisableWidget(Sexy::Widget *);

  public:
    virtual void RemoveAllWidgets(bool, bool);

  public:
    virtual void SetFocus(Sexy::Widget *);

  public:
    virtual bool IsBelow(Sexy::Widget *, Sexy::Widget *);

  public:
    virtual void MarkAllDirty();

  public:
    virtual void BringToFront(Sexy::Widget *);

  public:
    virtual void BringToBack(Sexy::Widget *);

  public:
    virtual void PutBehind(Sexy::Widget *, Sexy::Widget *);

  public:
    virtual void PutInfront(Sexy::Widget *, Sexy::Widget *);

  public:
    virtual Sexy::TPoint<int> GetAbsPos();

  public:
    virtual void MarkDirty(Sexy::WidgetContainer *);

  public:
    virtual void MarkDirty();

  public:
    virtual void MarkDirtyFull(Sexy::WidgetContainer *);

  public:
    virtual void MarkDirtyFull();

  public:
    virtual void AddedToManager(Sexy::WidgetManager *);

  public:
    virtual void RemovedFromManager(Sexy::WidgetManager *);

  public:
    virtual void Update();

  public:
    virtual void UpdateAll(Sexy::ModalFlags *);

  public:
    virtual void UpdateF(float);

  public:
    virtual void UpdateFAll(Sexy::ModalFlags *, float);

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void DrawAll(Sexy::ModalFlags *, Sexy::Graphics *);

  public:
    virtual void SysColorChangedAll();

  public:
    virtual void SysColorChanged();

  public:
    Sexy::WidgetContainer &operator=(const Sexy::WidgetContainer &);

  public:
    void __local_vftable_ctor_closure();

  public:
    virtual void *__vecDelDtor(uint32_t);
};

enum Sexy::KeyCode : int32_t
{
    KEYCODE_UNKNOWN = 0x0000,
    KEYCODE_LBUTTON = 0x0001,
    KEYCODE_RBUTTON = 0x0002,
    KEYCODE_CANCEL = 0x0003,
    KEYCODE_MBUTTON = 0x0004,
    KEYCODE_BACK = 0x0008,
    KEYCODE_TAB = 0x0009,
    KEYCODE_CLEAR = 0x000c,
    KEYCODE_RETURN = 0x000d,
    KEYCODE_SHIFT = 0x0010,
    KEYCODE_CONTROL = 0x0011,
    KEYCODE_MENU = 0x0012,
    KEYCODE_PAUSE = 0x0013,
    KEYCODE_CAPITAL = 0x0014,
    KEYCODE_KANA = 0x0015,
    KEYCODE_HANGEUL = 0x0015,
    KEYCODE_HANGUL = 0x0015,
    KEYCODE_JUNJA = 0x0017,
    KEYCODE_FINAL = 0x0018,
    KEYCODE_HANJA = 0x0019,
    KEYCODE_KANJI = 0x0019,
    KEYCODE_ESCAPE = 0x001b,
    KEYCODE_CONVERT = 0x001c,
    KEYCODE_NONCONVERT = 0x001d,
    KEYCODE_ACCEPT = 0x001e,
    KEYCODE_MODECHANGE = 0x001f,
    KEYCODE_SPACE = 0x0020,
    KEYCODE_PRIOR = 0x0021,
    KEYCODE_NEXT = 0x0022,
    KEYCODE_END = 0x0023,
    KEYCODE_HOME = 0x0024,
    KEYCODE_LEFT = 0x0025,
    KEYCODE_UP = 0x0026,
    KEYCODE_RIGHT = 0x0027,
    KEYCODE_DOWN = 0x0028,
    KEYCODE_SELECT = 0x0029,
    KEYCODE_PRINT = 0x002a,
    KEYCODE_EXECUTE = 0x002b,
    KEYCODE_SNAPSHOT = 0x002c,
    KEYCODE_INSERT = 0x002d,
    KEYCODE_DELETE = 0x002e,
    KEYCODE_HELP = 0x002f,
    KEYCODE_ASCIIBEGIN = 0x0030,
    KEYCODE_ASCIIEND = 0x005a,
    KEYCODE_LWIN = 0x005b,
    KEYCODE_RWIN = 0x005c,
    KEYCODE_APPS = 0x005d,
    KEYCODE_NUMPAD0 = 0x0060,
    KEYCODE_NUMPAD1 = 0x0061,
    KEYCODE_NUMPAD2 = 0x0062,
    KEYCODE_NUMPAD3 = 0x0063,
    KEYCODE_NUMPAD4 = 0x0064,
    KEYCODE_NUMPAD5 = 0x0065,
    KEYCODE_NUMPAD6 = 0x0066,
    KEYCODE_NUMPAD7 = 0x0067,
    KEYCODE_NUMPAD8 = 0x0068,
    KEYCODE_NUMPAD9 = 0x0069,
    KEYCODE_MULTIPLY = 0x006a,
    KEYCODE_ADD = 0x006b,
    KEYCODE_SEPARATOR = 0x006c,
    KEYCODE_SUBTRACT = 0x006d,
    KEYCODE_DECIMAL = 0x006e,
    KEYCODE_DIVIDE = 0x006f,
    KEYCODE_F1 = 0x0070,
    KEYCODE_F2 = 0x0071,
    KEYCODE_F3 = 0x0072,
    KEYCODE_F4 = 0x0073,
    KEYCODE_F5 = 0x0074,
    KEYCODE_F6 = 0x0075,
    KEYCODE_F7 = 0x0076,
    KEYCODE_F8 = 0x0077,
    KEYCODE_F9 = 0x0078,
    KEYCODE_F10 = 0x0079,
    KEYCODE_F11 = 0x007a,
    KEYCODE_F12 = 0x007b,
    KEYCODE_F13 = 0x007c,
    KEYCODE_F14 = 0x007d,
    KEYCODE_F15 = 0x007e,
    KEYCODE_F16 = 0x007f,
    KEYCODE_F17 = 0x0080,
    KEYCODE_F18 = 0x0081,
    KEYCODE_F19 = 0x0082,
    KEYCODE_F20 = 0x0083,
    KEYCODE_F21 = 0x0084,
    KEYCODE_F22 = 0x0085,
    KEYCODE_F23 = 0x0086,
    KEYCODE_F24 = 0x0087,
    KEYCODE_NUMLOCK = 0x0090,
    KEYCODE_SCROLL = 0x0091,
    KEYCODE_ASCIIBEGIN2 = 0x00b3,
    KEYCODE_ASCIIEND2 = 0x00e0,
};

enum ParticleSystemID : int32_t
{
    PARTICLESYSTEMID_NULL = 0x0000,
};

class Sexy::Widget : public Sexy::WidgetContainer
{   /* Size=0x88 */
    /* 0x0000: fields for Sexy::WidgetContainer */
  /* 0x0054 */ public:
    bool mVisible;
  /* 0x0055 */ public:
    bool mMouseVisible;
  /* 0x0056 */ public:
    bool mDisabled;
  /* 0x0057 */ public:
    bool mHasFocus;
  /* 0x0058 */ public:
    bool mIsDown;
  /* 0x0059 */ public:
    bool mIsOver;
  /* 0x005a */ public:
    bool mHasTransparencies;
  /* 0x005c */ public:
    std::vector<Sexy::Color, std::allocator<Sexy::Color>> mColors;
  /* 0x006c */ public:
    Sexy::Insets mMouseInsets;
  /* 0x007c */ public:
    bool mDoFinger;
  /* 0x007d */ public:
    bool mWantsFocus;
  /* 0x0080 */ public:
    Sexy::Widget *mTabPrev;
  /* 0x0084 */ public:
    Sexy::Widget *mTabNext;

  public:
    static bool mWriteColoredString;

  public:
    void WidgetRemovedHelper();

  public:
    void Widget(const Sexy::Widget &);

  public:
    void Widget();

  public:
    virtual ~Widget();

  public:
    virtual void OrderInManagerChanged();

  public:
    virtual void SetVisible(bool);

  public:
    virtual void SetColors(int32_t *[4], int32_t);

  public:
    virtual void SetColors(int32_t *[3], int32_t);

  public:
    virtual void SetColor(int32_t, const Sexy::Color &);

  public:
    virtual Sexy::Color GetColor(int32_t, const Sexy::Color &);

  public:
    virtual const Sexy::Color &GetColor(int32_t);

  public:
    virtual void SetDisabled(bool);

  public:
    virtual void ShowFinger(bool);

  public:
    virtual void Resize(const Sexy::TRect<int> &);

  public:
    virtual void Resize(int32_t, int32_t, int32_t, int32_t);

  public:
    virtual void Move(int32_t, int32_t);

  public:
    virtual bool WantsFocus();

  public:
    virtual void Draw(Sexy::Graphics *);

  public:
    virtual void DrawOverlay(Sexy::Graphics *, int32_t);

  public:
    virtual void DrawOverlay(Sexy::Graphics *);

  public:
    virtual void Update();

  public:
    virtual void UpdateF(float);

  public:
    virtual void GotFocus();

  public:
    virtual void LostFocus();

  public:
    virtual void KeyChar(char);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    virtual void KeyUp(Sexy::KeyCode);

  public:
    virtual void MouseEnter();

  public:
    virtual void MouseLeave();

  public:
    virtual void MouseMove(int32_t, int32_t);

  public:
    virtual void MouseDown(int32_t, int32_t, int32_t, int32_t);

  public:
    virtual void MouseDown(int32_t, int32_t, int32_t);

  public:
    virtual void MouseUp(int32_t, int32_t, int32_t, int32_t);

  public:
    virtual void MouseUp(int32_t, int32_t, int32_t);

  public:
    virtual void MouseUp(int32_t, int32_t);

  public:
    virtual void MouseDrag(int32_t, int32_t);

  public:
    virtual void MouseWheel(int32_t);

  public:
    virtual bool IsPointVisible(int32_t, int32_t);

  public:
    virtual Sexy::TRect<int> WriteCenteredLine(
        Sexy::Graphics *, int32_t, const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
        Sexy::Color, Sexy::Color, const Sexy::TPoint<int> &);

  public:
    virtual Sexy::TRect<int> WriteCenteredLine(
        Sexy::Graphics *, int32_t, const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    virtual int32_t WriteString(Sexy::Graphics *,
                                const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, int32_t,
                                int32_t, int32_t, int32_t, bool, int32_t, int32_t);

  public:
    virtual int32_t WriteWordWrapped(Sexy::Graphics *, const Sexy::TRect<int> &,
                                     const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                     int32_t, int32_t);

  public:
    virtual int32_t GetWordWrappedHeight(Sexy::Graphics *, int32_t,
                                         const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                         int32_t);

  public:
    virtual int32_t GetNumDigits(int32_t);

  public:
    virtual void WriteNumberFromStrip(Sexy::Graphics *, int32_t, int32_t, int32_t, Sexy::Image *, int32_t);

  public:
    virtual bool Contains(int32_t, int32_t);

  public:
    virtual Sexy::TRect<int> GetInsetRect();

  public:
    void DeferOverlay(int32_t);

  public:
    int32_t Left();

  public:
    int32_t Top();

  public:
    int32_t Right();

  public:
    int32_t Bottom();

  public:
    int32_t Width();

  public:
    int32_t Height();

  public:
    void Layout(int32_t, Sexy::Widget *, int32_t, int32_t, int32_t, int32_t);

  public:
    Sexy::Widget &operator=(const Sexy::Widget &);

  public:
    void __local_vftable_ctor_closure();

  public:
    virtual void *__vecDelDtor(uint32_t);
};

enum ReanimationID : int32_t
{
    REANIMATIONID_NULL = 0x0000,
};

enum SelectorAnimState : int32_t
{
    SELECTOR_OPEN = 0x0000,
    SELECTOR_NEW_USER = 0x0001,
    SELECTOR_SHOW_SIGN = 0x0002,
    SELECTOR_IDLE = 0x0003,
};

class Sexy::ButtonListener
{ /* Size=0x4 */

  public:
    virtual void ButtonPress(int32_t, int32_t);

  public:
    virtual void ButtonPress(int32_t);

  public:
    virtual void ButtonDepress(int32_t);

  public:
    virtual void ButtonDownTick(int32_t);

  public:
    virtual void ButtonMouseEnter(int32_t);

  public:
    virtual void ButtonMouseLeave(int32_t);

  public:
    virtual void ButtonMouseMove(int32_t, int32_t, int32_t);

  public:
    void ButtonListener(const Sexy::ButtonListener &);

  public:
    void ButtonListener();

  public:
    Sexy::ButtonListener &operator=(const Sexy::ButtonListener &);
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
    int32_t mStartingGameCounter;
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
    int32_t mCloudCounter[6];
  /* 0x0104 */ public:
    ReanimationID mFlowerReanimID[3];
  /* 0x0110 */ public:
    ReanimationID mLeafReanimID;
  /* 0x0114 */ public:
    ReanimationID mHandReanimID;
  /* 0x0118 */ public:
    int32_t mLeafCounter;
  /* 0x011c */ public:
    SelectorAnimState mSelectorState;
  /* 0x0120 */ public:
    int32_t mLevel;
  /* 0x0124 */ public:
    bool mLoading;
  /* 0x0128 */ public:
    ToolTipWidget *mToolTip;

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
    virtual void ButtonMouseEnter(int32_t);

  public:
    virtual void ButtonPress(int32_t, int32_t);

  public:
    virtual void ButtonDepress(int32_t);

  public:
    virtual void KeyDown(Sexy::KeyCode);

  public:
    virtual void KeyChar(char);

  public:
    virtual void MouseDown(int32_t, int32_t, int32_t);

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

  public:
    virtual void *__vecDelDtor(uint32_t);
};

#endif