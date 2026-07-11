#include "DataWriter.h"

DataWriter::DataWriter()
{
    mFile     = NULL;
    mData     = NULL;
    mDataLen  = 0;
    mCapacity = 0;
}

DataWriter::~DataWriter()
{
    Close();
}

void DataWriter::Close()
{
    if (mFile)
    {
        fclose(mFile);
        mFile = NULL;
    }

    delete[] mData;
    mData     = NULL;
    mDataLen  = 0;
    mCapacity = 0;
}

void DataWriter::OpenMemory(unsigned long initialCapacity)
{
    Close();

    unsigned long capacity = initialCapacity;
    if (capacity < 0x20)
    {
        capacity = 0x20;
    }

    mData     = new char[capacity];
    mCapacity = capacity;
}

void DataWriter::EnsureCapacity(unsigned long theNumBytes)
{
    if (mCapacity < theNumBytes)
    {
        while (mCapacity < theNumBytes)
        {
            mCapacity <<= 1;
        }

        char *newData = new char[mCapacity];

        memcpy(newData, mData, mDataLen);

        delete mData;
        mData = newData;
    }
}

void DataWriter::WriteBytes(const void *buffer, unsigned long size)
{
    if (mData)
    {
        EnsureCapacity(mDataLen + size);
        memcpy(mData + mDataLen, buffer, size);
        mDataLen += size;
    }
    else if (mFile)
    {
        fwrite(buffer, 1, size, mFile);
    }
}

void DataWriter::WriteLong(unsigned long value)
{
    if (mData)
    {
        EnsureCapacity(mDataLen + 4);
        *(unsigned int *)(mData + mDataLen) = value;
        mDataLen += 4;
    }
    else if (mFile)
    {
        fwrite(&value, 1, 4, mFile);
    }
}

void DataWriter::WriteShort(unsigned short value)
{
    if (mData)
    {
        EnsureCapacity(mDataLen + 2);
        *(unsigned short *)(mData + mDataLen) = value;
        mDataLen += 2;
    }
    else if (mFile)
    {
        fwrite(&value, 1, 2, mFile);
    }
}

void DataWriter::WriteString(const std::string &value)
{
    WriteShort((unsigned short)value.size());
    WriteBytes(value.data(), (unsigned long)value.size());
}
