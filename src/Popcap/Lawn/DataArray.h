#ifndef __DATAARRAY_H__
#define __DATAARRAY_H__

#include <cstddef>

template <class T> struct DataArrayItem
{
    T mItem;
    unsigned int mID;
    int mNext;
};

template <class T> class DataArray
{
  public:
    DataArrayItem<T> *mBlock;   // 0x00
    unsigned int mMaxUsedCount; // 0x04
    unsigned int mMaxSize;      // 0x08
    unsigned int mFreeListHead; // 0x0C
    unsigned int mSize;         // 0x10
    unsigned int mNextKey;      // 0x14
    const char *mName;          // 0x18

  public:
    DataArray();
    ~DataArray();

    void DataArrayInitialize(unsigned int, const char *);
    void DataArrayDispose();
    void DataArrayFreeAll();
    bool IterateNext(T *&);
    T *DataArrayAlloc();
    void DataArrayFree(T *);
    T *DataArrayGet(unsigned int id);
    T *DataArrayTryToGet(unsigned int);
    unsigned int DataArrayGetID(T *);
};

template <class T> DataArray<T>::DataArray()
{
    mBlock        = NULL;
    mMaxUsedCount = 0;
    mMaxSize      = 0;
    mFreeListHead = 0;
    mSize         = 0;
    mNextKey      = 0;
    mName         = NULL;
}

template <class T> DataArray<T>::~DataArray()
{
}

template <class T> void DataArray<T>::DataArrayInitialize(unsigned int aMaxSize, const char *aName)
{
}

template <class T> void DataArray<T>::DataArrayDispose()
{
}

template <class T> void DataArray<T>::DataArrayFreeAll()
{
}

template <class T> bool DataArray<T>::IterateNext(T *&item)
{
    return false;
}

template <class T> T *DataArray<T>::DataArrayAlloc()
{
    return NULL;
}

template <class T> void DataArray<T>::DataArrayFree(T *item)
{
}

template <class T> T *DataArray<T>::DataArrayGet(unsigned int id)
{
    if (id == 0)
    {
        return NULL;
    }

    unsigned int index = id & 0xFFFF;
    if (index < mMaxUsedCount)
    {
        DataArrayItem<T> *item = &mBlock[index];
        if (item->mID == id)
        {
            return &item->mItem;
        }
    }

    return NULL;
}

template <class T> T *DataArray<T>::DataArrayTryToGet(unsigned int id)
{
    return DataArrayGet(id);
}

template <class T> unsigned int DataArray<T>::DataArrayGetID(T *item)
{
    return 0;
}

#endif
