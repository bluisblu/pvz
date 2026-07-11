#ifndef __TYPINGCHECK_H__
#define __TYPINGCHECK_H__

#include "SexyAppFramework/KeyCodes.h"
#include <string>

class TypingCheck
{ /* Size=0x38 */
  protected:
    /* 0x0000 */ std::string mPhrase;
    /* 0x001c */ std::string mRecentTyping;

  public:
    TypingCheck(const TypingCheck &);
    TypingCheck(const std::string &);
    TypingCheck();

    void SetPhrase(const std::string &);
    void AddKeyCode(Sexy::KeyCode);
    void AddChar(char);
    bool Check(char);
    bool Check(Sexy::KeyCode);
    ~TypingCheck();
    TypingCheck &operator=(const TypingCheck &);
};

#endif
