#include "File.h"
#include "Constants.h"

#include <stdio.h>
#include <memory>

bool File::write(const char *fname, const Combit combit)
{
    FILE* output;

    output = fopen(fname, "wb");
    if (output == NULL) {
        printf("Error opening file");
        return false;
    }

    uint8_t height[LEGTH_BITES_COUNT];

    const uint8_t* inverseHeight = reinterpret_cast<const uint8_t*>(&combit.getHeight());

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        height[LEGTH_BITES_COUNT - i - 1] = inverseHeight[i];
    }

    fwrite(height, 1, sizeof(height), output);

    uint8_t width[LEGTH_BITES_COUNT];

    const uint8_t* inverseWidth = reinterpret_cast<const uint8_t*>(&combit.getWidth());

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        width[LEGTH_BITES_COUNT - i - 1] = inverseWidth[i];
    }

    fwrite(width, 1, sizeof(width), output);
    fwrite(combit.getEmptyLine(), 1, combit.getHeight(), output);

    uint8_t length[LEGTH_BITES_COUNT];

    const uint8_t* inverseLength = reinterpret_cast<const uint8_t*>(&combit.getLength());

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        length[LEGTH_BITES_COUNT - i - 1] = inverseLength[i];
    }
    fwrite(length, 1, sizeof(length), output);
    fwrite(combit.getData(),1, combit.getLength(), output);  

    fclose(output);

    return true;
}

bool File::read(const char*fname, Combit &combit)
{
    FILE* input = fopen(fname, "rb");
    if (input == NULL) {
        printf("Error opening file");
        return false;
    }

    uint8_t inverseHeight[LEGTH_BITES_COUNT];

    fread(inverseHeight, 1, sizeof(inverseHeight), input);
    
    uint64_t height;

    uint8_t* pointHeight = reinterpret_cast<uint8_t*>(&height);

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        pointHeight[LEGTH_BITES_COUNT - i - 1] = inverseHeight[i];
    }
    

    uint8_t inverseWidth[LEGTH_BITES_COUNT];

    fread(inverseWidth, 1, sizeof(inverseWidth), input);
    
    uint64_t width;

    uint8_t* pointWidth = reinterpret_cast<uint8_t*>(&width);

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        pointWidth[LEGTH_BITES_COUNT - i - 1] = inverseWidth[i];
    }
    
    std::unique_ptr<bool[]> emptyLine(new bool[height]);
    fread(emptyLine.get(), 1, height, input);

    uint8_t inverseLength[LEGTH_BITES_COUNT];

    fread(inverseLength, 1, sizeof(inverseLength), input);
    
    uint64_t length;

    uint8_t* pointLength = reinterpret_cast<uint8_t*>(&length);

    for (int8_t i = LEGTH_BITES_COUNT - 1; i >= 0; i--)
    {
        pointLength[LEGTH_BITES_COUNT - i - 1] = inverseLength[i];
    }
    
    std::unique_ptr<uint8_t[]> data(new uint8_t[length]);
    fread(data.get(), 1, length, input);

    combit = {height, width, emptyLine.get(), data.get(),length};
    return true;
}

bool File::read(const char*fname, Bitmap &bitmap)
{
	FILE* fd = fopen(fname, "rb");

	if (NULL == fd)
	{
		printf("Error open file\n");

		return false;
	}

	uint8_t BMPHeader[BMP_HEADER_SIZE];

	fread(BMPHeader, 1, sizeof(BMPHeader), fd);

	uint8_t BMPHeaderInfo[BMP_INFO_HEADER_SIZE];

	fread(BMPHeaderInfo, 1, sizeof(BMPHeaderInfo), fd);

	uint32_t width = 0;
	for (uint8_t i = 0; i < BMP_INFO_HEADER_WIDTH_SIZE; i++)
	{
		width += *(BMPHeaderInfo + BMP_INFO_HEADER_SIZE_SIZE + i);
		width <<= 8;
	}

	uint32_t height = 0;
	for (uint8_t i = 0; i < BMP_INFO_HEADER_HEIGTH_SIZE; i++)
	{
		height += *(BMPHeaderInfo + BMP_INFO_HEADER_SIZE_SIZE + BMP_INFO_HEADER_WIDTH_SIZE + i);
		height <<= 8;
	}

	std::unique_ptr<uint8_t[]> colorData(new uint8_t[BMP_COLOR_TABEL_COLORS_SIZE * height * width]);

	fread(colorData.get(), 1, BMP_COLOR_TABEL_COLORS_SIZE * height * width, fd);

	fclose(fd);

    std::unique_ptr<uint8_t[]> data(new uint8_t[height * width]);
    uint64_t index = 0;

    for (uint64_t i = 0; i < height; i++)
    {
        for (uint64_t j = 0; j < width; j++)
        {
            data[i * width + j] = colorData[BMP_COLOR_TABEL_COLORS_SIZE * index++];
        }
    }

    bitmap = {height, width, data.get()};
    return true;
}