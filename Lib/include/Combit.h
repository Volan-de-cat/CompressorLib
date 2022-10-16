#ifndef COMBIT_H
#define COMBIT_H

#include <stdint.h>

class Combit
{
public:

    Combit(uint64_t, uint64_t, bool*, uint8_t*, uint64_t);
    Combit(const Combit& other);
    Combit(Combit&& other);
    ~Combit();

    Combit& operator=(const Combit& other);
    Combit& operator=(Combit&& other);

    inline const uint64_t& getHeight() const;
    inline const uint64_t& getWidth() const;

    inline const bool* getEmptyLine() const;

    inline const uint8_t* getData() const;
    inline const uint64_t& getLength() const;

private:

    uint64_t _height;
    uint64_t _width;

    bool* _emptyLine;

    uint8_t* _data;
    uint64_t _length;
};

inline const uint64_t& Combit::getHeight() const
{
    return _height;
}
inline const uint64_t& Combit::getWidth() const
{
    return _width;
}

inline const bool* Combit::getEmptyLine() const
{
    return _emptyLine;
}

inline const uint8_t* Combit::getData() const
{
    return _data;
}

inline const uint64_t& Combit::getLength() const
{
    return _length;
}


#endif // COMBIT_H
