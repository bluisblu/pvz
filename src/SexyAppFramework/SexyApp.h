#ifndef __SEXYAPP_H__
#define __SEXYAPP_H__

#include "SexyAppBase.h"

// Need to also put Windows headers here too.

namespace Sexy
{

class SexyApp : public SexyAppBase
{
  public:
    /* InternetManager* */ void *mInternetManager;
    /* BetaSupport* */ void *mBetaSupport;

    // Special members for PvZ?
    std::string mBetaSupportSiteOverride;
    std::string mBetaSupportProdNameOverride;

    std::string mReferId;
    std::string mVariation;
    ulong mDownloadId;
    std::string mRegSource;
    ulong mLastVerCheckQueryTime;
    bool mSkipAd;
    bool mDontUpdate;

    int mBuildNum;
    std::string mBuildDate;
    std::string mUserName;
    std::string mRegUserName;
    std::string mRegCode;
    bool mIsRegistered;
    int mBuildUnlocked;

    int mTimesPlayed;
    int mTimesExecuted;
    bool mTimedOut;

  public:
    virtual void UpdateFrames();

    // Param names pulled from other sources. Should be correct.
    void WriteRegistrationInfo(std::string theRegUser, std::string theRegCode, int theTimesPlayed,
                               int theTimesExecuted);
    void ReadRegistrationInfo(std::string *theRegUser, std::string *theRegCode, int *theTimesPlayed,
                              int *theTimesExecuted);
    virtual void WriteToRegistry();
    virtual void ReadFromRegistry();

    virtual bool CheckSignature(const Buffer &theBuffer, const std::string &theFileName);

    virtual bool ShouldCheckForUpdate();
    virtual void UpdateCheckQueried();

    virtual void URLOpenSucceeded(const std::string &theURL);

  public:
    SexyApp();
    virtual ~SexyApp();

    bool Validate(const std::string &theUserName, const std::string &theRegCode);

    virtual bool OpenRegisterPage();

    virtual void PreDisplayHook();
    virtual void InitPropertiesHook();
    virtual void Init();
    virtual void PreTerminate();

    // std::map<std::string, std::string> is a typedef called DefinesMap, apparently.
    virtual bool OpenHTMLTemplate(const std::string &theTemplateFile,
                                  const std::map<std::string, std::string> &theDefinesMap);
    virtual void OpenUpdateURL();

    virtual void HandleCmdLineParam(const std::string &theParamName, const std::string &theParamValue);
    virtual void HandleNotifyGameMessageCommandLine(const std::wstring &idk); // not in other vers of SexyApp
    virtual std::string GetGameSEHInfo();
    virtual void GetSEHWebParams(std::map<std::string, std::string> *theDefinesMap);

    // Parameter typedefs are a guess. Original params: HWND, unsigned int, unsigned int, long, long *
    // We know UINT is unsigned int, WPARAM is unsigned (int), and LPARAM is long, so naturally the 5th param would have
    // to be LRESULT. But its actually LRESULT* it seems?
    virtual bool OverrideWindowProc(HWND theWindow, UINT theMsg, WPARAM theWParam, LPARAM theLParam,
                                    LRESULT *theLResult);
};

extern SexyApp *gSexyApp;

}; // namespace Sexy

#endif //__SEXYAPP_H__