#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

class Bitmap
{
public:

    Bitmap(uint64_t, uint64_t);
    Bitmap(uint64_t, uint64_t, uint8_t*);
    Bitmap(const Bitmap& other);
    Bitmap(Bitmap&& other);
    ~Bitmap();

    Bitmap& operator=(const Bitmap& other);
    Bitmap& operator=(Bitmap&& other);

    inline const uint64_t& getHeight() const;
    inline const uint64_t& getWidth() const;

    bool setData(const uint8_t*);
    inline const uint8_t* getData() const;

private:

    uint64_t _height;
    uint64_t _width;

    uint8_t* _data;
};

inline const uint64_t& Bitmap::getHeight() const
{
    return _height;
}
inline const uint64_t& Bitmap::getWidth() const
{
    return _width;
}

inline const uint8_t* Bitmap::getData() const
{
    return _data;
}

#endif // BITMAP_H