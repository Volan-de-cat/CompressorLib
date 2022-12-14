#include <stdio.h>
#include <string.h>

#include "Constants.h"

#define WIDTH	8
#define IMAGE  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

#include "Compressor.h"

int main()
{
	const uint8_t width = WIDTH;
	uint8_t img[] = IMAGE;

	Bitmap input(sizeof(img) / width, width,  img);

	Combit output = Compressor::compress(input);

	// printf("White lines: ");
	// for(uint64_t i = 0; i < output.getHeight(); i++)
	// {
	// 	if (output.getEmptyLine()[i])
	// 	{
	// 		printf("%ld, ", i);
	// 	}
	// }
	// printf("\n");

	// printf("Compressed data: ");
	// for (uint64_t i = 0; i < output.getLength(); i++)
	// {
	// 	printf("%02X ", output.getData()[i]);
	// }
	// printf("\n");

	// printf("Bytes: ");
	// for (uint64_t i = 0; i < output.getLength(); i++)
	// {
	// 	for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
	// 	{
	// 		printf("%d", (output.getData()[i] >> t) & 1);
	// 	}
	// 	printf(", ");
	// }
	// printf("\n");

	Bitmap rezult = Compressor::decompress(output);

	// for (uint64_t i = 0; i < rezult.getHeight(); i++)
	// {
	// 	for (uint64_t j = 0; j < rezult.getWidth(); j++)
	// 	{
	// 		printf("0x%02X, ", rezult.getData()[i * rezult.getWidth() + j]);
	// 	}
	// 	printf("\n");
	// }

	if (0 == memcmp(input.getData(), rezult.getData(), sizeof(img)))
	{
		printf("OK\n");
	}

	getchar();
	return 0;
}
