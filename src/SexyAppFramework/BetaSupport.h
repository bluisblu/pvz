#ifndef __BETASUPPORT_H__
#define __BETASUPPORT_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Buffer.h"

namespace Sexy
{
class WinInetHTTPTransfer
{ /* Size=0x1a4 */
    enum EResult : int
    {
        RESULT_DONE = 0x0000,
        RESULT_NOT_STARTED = 0x0001,
        RESULT_NOT_COMPLETED = 0x0002,
        RESULT_NOT_FOUND = 0x0003,
        RESULT_HTTP_ERROR = 0x0004,
        RESULT_HTTP_REDIRECT = 0x0005,
        RESULT_ABORTED = 0x0006,
        RESULT_SOCKET_ERROR = 0x0007,
        RESULT_INVALID_ADDR = 0x0008,
        RESULT_CONNECT_FAIL = 0x0009,
        RESULT_DISCONNECTED = 0x000a,
        RESULT_INTERNAL_ERROR = 0x000b,
    };
  /* 0x0004 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mSpecifiedBaseURL;
  /* 0x0020 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mSpecifiedRelURL;
  /* 0x003c */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mURL;
  /* 0x0058 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mProto;
  /* 0x0074 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mUserName;
  /* 0x0090 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mUserPass;
  /* 0x00ac */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mHost;
  /* 0x00c8 */ private:
    int mPort;
  /* 0x00cc */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mPath;
  /* 0x00e8 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mAction;
  /* 0x0104 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mUserAgent;
  /* 0x0120 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mPostContentType;
  /* 0x013c */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mPostData;
  /* 0x0158 */ private:
    _iobuf *mFP;
  /* 0x015c */ private:
    bool mUsingFile;
  /* 0x0160 */ private:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mContent;
  /* 0x017c */ private:
    int mContentLength;
  /* 0x0180 */ private:
    int mCurContentLength;
  /* 0x0184 */ private:
    bool mTransferPending;
  /* 0x0185 */ private:
    bool mThreadRunning;
  /* 0x0186 */ private:
    bool mExiting;
  /* 0x0187 */ private:
    bool mAborted;
  /* 0x0188 */ private:
    Sexy::WinInetHTTPTransfer::EResult mResult;
  /* 0x018c */ private:
    _RTL_CRITICAL_SECTION mFileCritSection;

  public:
    WinInetHTTPTransfer(const Sexy::WinInetHTTPTransfer &);

  public:
    WinInetHTTPTransfer();

  public:
    Sexy::WinInetHTTPTransfer &operator=(const Sexy::WinInetHTTPTransfer &);

  public:
    virtual ~WinInetHTTPTransfer();

  public:
    bool SetOutputFile(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> &);

  public:
    bool SetOutputFile(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void Get(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
             const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void Get(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void Post(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
              const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
              const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void Post(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
              const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void PostMultiPart(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void PostMultiPart(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void Reset();

  public:
    void Abort();

  public:
    void WaitFor();

  public:
    Sexy::WinInetHTTPTransfer::EResult GetResultCode() const;

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetContent();

  protected:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetAbsURL(
        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  protected:
    void GetHelper(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  protected:
    void PostHelper(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                    const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, const char *);

  protected:
    void PrepareTransfer(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  protected:
    void StartTransfer();

  protected:
    void TransferThreadProc();

  protected:
    void Fail(WinInetHTTPTransfer::EResult);

  public:
    // void __local_vftable_ctor_closure();

  public:
    // virtual void *__vecDelDtor(unsigned int);

  public:
    static void TransferThreadProcStub(void *);
};

class BetaSupport
{ /* Size=0x250 */
  /* 0x0004 */ public:
    /* SexyApp * */ int mApp;
  /* 0x0008 */ public:
    /* HFONT__ * */ int mDialogFont;
  /* 0x000c */ public:
    /* HFONT__ * */ int mItalicsFont;
  /* 0x0010 */ public:
    /* HFONT__ * */ int mBoldFont;
  /* 0x0014 */ public:
    int mPeriodCount;
  /* 0x0018 */ public:
    /* HWND__ * */ int mHWnd;
  /* 0x001c */ public:
    /* HWND__ * */ int mTextHWnd;
  /* 0x0020 */ public:
    /* HWND__ * */ int mNameHWnd;
  /* 0x0024 */ public:
    /* HWND__ * */ int mPasswordHWnd;
  /* 0x0028 */ public:
    Sexy::WinInetHTTPTransfer mWinInetHTTPTransfer;
  /* 0x01cc */ public:
    bool mAborted;
  /* 0x01cd */ public:
    bool mDialogClosed;
  /* 0x01d0 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mBetaCommentURL;
  /* 0x01ec */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mDemoUploadFile;
  /* 0x0208 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mName;
  /* 0x0224 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mPassword;
  /* 0x0240 */ public:
    bool mValidated;
  /* 0x0244 */ public:
    std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Sexy::Buffer,
             std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>,
             std::allocator<
                 std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char>> const, Sexy::Buffer>>>
        mDataLogs;

  protected:
    void PositionDialog(/* HWND__ * */ int);

  protected:
    void WaitForDialogClose();

  protected:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetBetaSiteDomainName();

  protected:
    bool GetLoginInfo();

  protected:
    bool ValidateWithServer();

  protected:
    void ReadFromRegistry();

  protected:
    void WriteToRegistry();

  protected:
    void SubmitDemoBufferThread();

  protected:
    bool SubmitDemoBuffer();

  public:
    BetaSupport(const Sexy::BetaSupport &);

  public:
    BetaSupport(/*Sexy::SexyApp * */ int);

  public:
    virtual ~BetaSupport();

  public:
    bool Validate();

  public:
    bool RequestDemoUpload(const char *);

  public:
    bool RequestComments();

  public:
    void StoreDataLog(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                      const Sexy::Buffer &);

  public:
    Sexy::BetaSupport &operator=(const Sexy::BetaSupport &);

  public:
    // virtual void *__vecDelDtor(unsigned int);

  protected:
    static int ValidateWindowProc(HWND__ *, unsigned int, unsigned int, int);

  protected:
    static int LoginWindowProc(HWND__ *, unsigned int, unsigned int, int);

  protected:
    static int SubmitWindowProc(HWND__ *, unsigned int, unsigned int, int);

  protected:
    static void SubmitDemoBufferThreadStub(void *);
};
} // namespace Sexy

#endif