#include <vector>

template <typename T>
class Pool
{
private:
    std::vector<T> pool;
    std::vector<unsigned short> availableItems;

public:
    Pool(unsigned int size);
    ~Pool();

    T *getNextObject();
    int getInactiveObjectAtChunk(unsigned int index);
    int size();

    void setUnused(unsigned int index);
};

/* DEFINITION FOR TEMPLATING */

#include <cmath>
#include <iostream>

template <typename T>
Pool<T>::Pool(unsigned int size)
{
    size = 16 * ceilf((float)size / 16.);
    pool.resize(size);
    availableItems.resize(size / 16);
}

template <typename T>
Pool<T>::~Pool() {}

template <typename T>
T *Pool<T>::getNextObject()
{
    for (int i = 0; i < availableItems.size(); i++)
    {
        int foundInactiveObjectIndex = getInactiveObjectAtChunk(i);
        if (foundInactiveObjectIndex != -1)
        {
            return &(pool[foundInactiveObjectIndex]);
        }
    }
    return nullptr;
}

template <typename T>
int Pool<T>::getInactiveObjectAtChunk(unsigned int index)
{
    // Get char (bool group) at index (0 -> 15 1st group, 16 -> 32 2nd group etc)
    int boolGroupIndex = index % 16;
    // Check
    for (int i = 0; i < 16; i++) // 16 because we have 16 per chunk ALWAYS
    {
        unsigned short boolMask = 0b1 << i;
        if (!(bool)(availableItems[boolGroupIndex] & boolMask))
        {
            availableItems[boolGroupIndex] += boolMask;
            return index + i;
        }
    }

    return -1;
}

template <typename T>
int Pool<T>::size()
{
    return pool.size();
}

template <typename T>
void Pool<T>::setUnused(unsigned int index)
{
    int boolGroup = index / 16;
    unsigned short boolMask = 0b1 << (index % 16);
    availableItems[boolGroup] = availableItems[boolGroup] - boolMask;
}
