#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BYTE_LEN                0x08

#define COMPRESS_BYTES_COUNT    0x04

#define WHITE_COLLOR            0xFF
#define BLACK_COLLOR            0x00

#define WHITE_BITS              0x00 // 00
#define BLACK_BITS              0x02 // 10
#define OTHER_BITS              0x03 // 11

#define WHITE_BITS_COUNT        0x01
#define BLACK_BITS_COUNT        0x02
#define OTHER_BITS_COUNT        0x02

#define LEGTH_BITES_COUNT       0x08                               

#define BMP_HEADER_SIZE                         0x14
#define BMP_HEADER_SIGANTURE_SIZE               0x02
#define BMP_HEADER_FILESIZE_SIZE                0x02
#define BMP_HEADER_RESERVED_SIZE                0x02
#define BMP_HEADER_DATAOFFSET_SIZE              0x02

#define BMP_INFO_HEADER_SIZE                    0x40
#define BMP_INFO_HEADER_SIZE_SIZE               0x04
#define BMP_INFO_HEADER_WIDTH_SIZE              0x04
#define BMP_INFO_HEADER_HEIGTH_SIZE             0x04
#define BMP_INFO_HEADER_PLANES_SIZE             0x02
#define BMP_INFO_HEADER_BITCOUNT_SIZE           0x02
#define BMP_INFO_HEADER_COMPRESSION_SIZE        0x04
#define BMP_INFO_HEADER_IMAGESIZE_SIZE          0x04
#define BMP_INFO_HEADER_XPIX_SIZE               0x04
#define BMP_INFO_HEADER_YPIX_SIZE               0x04
#define BMP_INFO_HEADER_COLORUSED_SIZE          0x04
#define BMP_INFO_HEADER_COLORSIMPORTANT_SIZE    0x04

#define BMP_COLOR_TABEL_COLORS_SIZE             0x04
#define BMP_COLOR_TABEL_COLOR_RED_SIZE          0x01
#define BMP_COLOR_TABEL_COLORS_GREEN_SIZE       0x01
#define BMP_COLOR_TABEL_COLORS_BLUE_SIZE        0x01
#define BMP_COLOR_TABEL_COLORS_RESERVED_SIZE    0x01


#endif // CONSTANTS_H