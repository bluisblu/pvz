#include "TypingCheck.h"

TypingCheck::TypingCheck() : mPhrase(), mRecentTyping()
{
}

void TypingCheck::AddKeyCode(Sexy::KeyCode theCode)
{
    mPhrase.append(1, theCode);
}

void TypingCheck::AddChar(char theChar)
{
    std::string strKey(1, (char)tolower(theChar));

    char codeAsChar = Sexy::GetKeyCodeFromName(strKey);

    mPhrase.append(1, codeAsChar);
}

void TypingCheck::SetPhrase(const std::string &thePhrase)
{
    for (int i = 0; i < (int)thePhrase.length(); ++i)
    {
        AddChar(thePhrase[i]);
    }
}

bool TypingCheck::Check(Sexy::KeyCode theCode)
{
    mRecentTyping.append(1, (char)theCode);

    if (!mPhrase.empty())
    {
        if (mRecentTyping.length() > mPhrase.length())
        {
            mRecentTyping = mRecentTyping.substr(1, mPhrase.length());
        }

        if (mRecentTyping == mPhrase)
        {
            mRecentTyping.clear();
            return true;
        }
    }

    return false;
}

TypingCheck::TypingCheck(const std::string &thePhrase) : mPhrase(), mRecentTyping()
{
    SetPhrase(thePhrase);
}
