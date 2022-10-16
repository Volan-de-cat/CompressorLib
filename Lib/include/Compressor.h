#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Bitmap.h"
#include "Combit.h"

class Compressor
{
public:

    Compressor() = delete;
    Compressor(const Compressor&) = delete;
    Compressor(Compressor&&) = delete;

    static Combit compress(const Bitmap);
    static Bitmap decompress(const Combit);
};

#endif // COMPRESSOR_H
