#include <vector>

template <typename T>
class Pool
{
private:
    std::vector<T> pool;
    std::vector<unsigned short> availableItems;
    int lastFoundIndex;

    int getInactiveObjectAtChunk(unsigned int chunkIndex);
    int getChunkFromItemIndex(unsigned int itemIndex);

public:
    Pool(unsigned int size);
    ~Pool();

    T *getNextObject();
    int size();

    void setUnused(unsigned int index);
};

/* DEFINITION FOR TEMPLATING */

// CONSTRUCTORS

#include <cmath>

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
    for (int i = getChunkFromItemIndex(lastFoundIndex); i < availableItems.size(); i++) // We start from the chunk that the last found item was found for faster search.
    {
        int foundInactiveObjectIndex = getInactiveObjectAtChunk(i);
        if (foundInactiveObjectIndex != -1)
        {
            lastFoundIndex = foundInactiveObjectIndex;
            return &(pool[foundInactiveObjectIndex]);
        }
    }
    return nullptr;
}

// PRIVATE METHODS

template <typename T>
int Pool<T>::getInactiveObjectAtChunk(unsigned int chunkIndex)
{
    // Check
    for (int i = 0; i < 16; i++) // 16 because we have 16 per chunk ALWAYS
    {
        unsigned short boolMask = 0b1 << i;
        if (!(bool)(availableItems[chunkIndex] & boolMask))
        {
            availableItems[chunkIndex] += boolMask;
            return chunkIndex + i;
        }
    }

    return -1;
}

template <typename T>
inline int Pool<T>::getChunkFromItemIndex(unsigned int itemIndex)
{
    return itemIndex / 16;
}

// PUBLIC METHODS

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
