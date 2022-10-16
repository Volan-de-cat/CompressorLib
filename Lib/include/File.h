#ifndef FILE_H
#define FILE_H

#include "Bitmap.h"
#include "Combit.h"

class File
{
    public:
    bool write(const char*, const Combit);

    bool read(const char*, Combit&);
    bool read(const char*, Bitmap&);
};

#endif // FILE_H