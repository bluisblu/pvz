#ifndef __DATAWRITER_H__
#define __DATAWRITER_H__

#include <string>

// MSVC CRT type
struct _iobuf;

class DataWriter
{
  public:
    DataWriter();
    DataWriter(const DataWriter &other);
    virtual ~DataWriter();

    DataWriter &operator=(const DataWriter &other);

    bool OpenFile(const std::string &filename);
    void OpenMemory(unsigned long initialCapacity);
    void Close();
    bool WriteToFile(const std::string &filename);
    void WriteBytes(const void *buffer, unsigned long size);
    void WriteLong(unsigned long value);
    void WriteShort(unsigned short value);
    void WriteByte(unsigned char value);
    void WriteBool(bool value);
    void WriteFloat(float value);
    void WriteDouble(double value);
    void WriteString(const std::string &value);
    unsigned int GetPos();
    void SetLong(unsigned int value, unsigned int offset);
    void SetShort(unsigned short value, unsigned int offset);
    void SetByte(unsigned char value, unsigned int offset);
    char *GetDataPtr();
    unsigned int GetDataLen();

  protected:
    void EnsureCapacity(unsigned long theNumBytes);

  protected:
    /* 0x0000 */ // vfptr
    /* 0x0004 */ _iobuf *mFile;
    /* 0x0008 */ char *mData;
    /* 0x000c */ unsigned int mDataLen;
    /* 0x0010 */ unsigned int mCapacity;
};

#endif // __DATAWRITER_H__
