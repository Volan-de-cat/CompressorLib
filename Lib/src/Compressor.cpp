#include "Compressor.h"
#include "Constants.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <string.h>

Combit Compressor::compress(const Bitmap bitmap)
{
	std::unique_ptr<bool[]> emptyLine(new bool[bitmap.getHeight()]);
	std::vector<uint8_t> data;

	uint8_t bytes[COMPRESS_BYTES_COUNT];
	memset(bytes, 0, COMPRESS_BYTES_COUNT);

	uint8_t bitPos = 1;

	for (uint64_t i = 0; i < bitmap.getHeight(); i++)
	{
		uint64_t index = 0;

		while (index < bitmap.getWidth() && WHITE_COLLOR == bitmap.getData()[i * bitmap.getWidth() + index++]);

		emptyLine[i] = (bitmap.getWidth() == index);

		if (!emptyLine[i])
		{
			if (0 == data.size())
			{
				data.push_back(0);
			}

			for (uint64_t j = 0; j < bitmap.getWidth(); j++)
			{
				bytes[j % COMPRESS_BYTES_COUNT] = bitmap.getData()[i * bitmap.getWidth() + j];

				if (0 == (j + 1) % COMPRESS_BYTES_COUNT)
				{
					bool isSolid = true;
					const uint8_t color = *bytes;
					for (uint8_t t = 0; isSolid && t < COMPRESS_BYTES_COUNT; t++)
					{
						if (color != bytes[t])
						{
							isSolid = false;
						}
					}

					uint8_t commandBits = 0;
					uint8_t bitsCount = 0;

					bool writeBytes = false;

					if (isSolid && WHITE_COLLOR == color)
					{
						commandBits = WHITE_BITS;
						bitsCount = WHITE_BITS_COUNT;
					}
					else
					if (isSolid && BLACK_COLLOR == color)
					{	
						commandBits = BLACK_BITS;
						bitsCount = BLACK_BITS_COUNT;
					}
					else
					{
						commandBits = OTHER_BITS;
						bitsCount = OTHER_BITS_COUNT;

						writeBytes = true;
					}

					// printf("Command: ");

					// switch (commandBits)
					// {
					// case WHITE_BITS:
					// {
					// 	printf("0");
					// 	break;
					// }
					// case BLACK_BITS:
					// {
					// 	printf("10");
					// 	break;
					// }
					// default:
					// {
					// 	printf("11");
					// 	break;
					// }
					// }
					
					// printf(" - ");

					for (int8_t k = bitsCount - 1; k >= 0; k--)
					{
						data[data.size() - 1] += (commandBits >> k) & 1;

						if (BYTE_LEN == bitPos)
						{
							data.push_back(0);
							bitPos = 1;
						}
						else
						{
							data[data.size() - 1] <<= 1;
							bitPos++;
						}

						// printf("%d", (commandBits >> k) & 1);
					}

					// printf("\n");

					// printf("Data: ");
					// for (uint64_t i = 0; i < data.size(); i++)
					// {
					// 	for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
					// 	{
					// 		printf("%d", (data[i] >> t) & 1);
					// 	}
					// 	printf(", ");
					// }
					// printf("\n");

					if (writeBytes)
					{
						// printf("Bytes: ");
						for (uint8_t k = 0; k < COMPRESS_BYTES_COUNT; k++)
						{
							for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
							{
								data[data.size() - 1] += (bytes[k] >> t) & 1;

								if (BYTE_LEN == bitPos)
								{
									data.push_back(0);
									bitPos = 1;
								}
								else
								{
									data[data.size() - 1] <<= 1;
									bitPos++;
								}

								// printf("Step: %d\n", BYTE_LEN - t);

								// printf("Data: ");
								// for (uint64_t i = 0; i < data.size(); i++)
								// {
								// 	for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
								// 	{
								// 		printf("%d", (data[i] >> t) & 1);
								// 	}
								// 	printf(", ");
								// }
								// printf("\n");

								// printf("%d", (bytes[k] >> t) & 1);
							}
							// printf(" ");
						}
						// printf("\n");
					}
				}
			}
		}
	}

	if (0 != data.size())
	{
		data[data.size() - 1] <<= (BYTE_LEN - bitPos);
	}

	Combit rezult(bitmap.getHeight(), bitmap.getWidth(), emptyLine.get(), data.data(), data.size());

	return rezult;
}

Bitmap Compressor::decompress(const Combit combit)
{
	std::vector<uint8_t> data;

	uint8_t bytes[COMPRESS_BYTES_COUNT];
	memset(bytes, 0, COMPRESS_BYTES_COUNT);

	uint64_t commandPosition = 0;
	uint8_t  bitPosition = 1;

	for (uint64_t i = 0; i < combit.getHeight(); i++)
	{
		for (uint64_t j = 0; j < combit.getWidth(); j++)
		{
			if (0 == j % COMPRESS_BYTES_COUNT)
			{
				uint8_t commandBits = WHITE_BITS;

				if (!combit.getEmptyLine()[i])
				{
					//printf("%d", (combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1);

					if ((combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1)
					{
						commandBits += 1;
						commandBits <<= 1;

						if (BYTE_LEN == bitPosition)
						{
							commandPosition++;
							bitPosition = 1;
						}
						else
						{
							bitPosition++;
						}

						//printf("%d", (combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1);

						if ((combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1)
						{
							commandBits += 1;
						}
					}
					
					if (BYTE_LEN == bitPosition)
					{
						commandPosition++;
						bitPosition = 1;
					}
					else
					{
						bitPosition++;
					}

					//printf("\n");
				}

				switch (commandBits)
				{
				case WHITE_BITS:
				{
					memset(bytes, WHITE_COLLOR, COMPRESS_BYTES_COUNT);
					break;
				}
				case BLACK_BITS:
				{
					memset(bytes, BLACK_COLLOR, COMPRESS_BYTES_COUNT);
					break;
				}
				case OTHER_BITS:
				{
					for (uint8_t k = 0; k < COMPRESS_BYTES_COUNT; k++)
					{
						bytes[k] = 0;
						
						for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
						{
							bytes[k] <<= 1;
							bytes[k] += (combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1;

							// printf("%d", (combit.getData()[commandPosition] >> (BYTE_LEN - bitPosition)) & 1);

							if (BYTE_LEN == bitPosition)
							{
								commandPosition++;
								bitPosition = 1;
							}
							else
							{
								bitPosition++;
							}
						}
						// printf(" = ");
						
						// for (int8_t t = BYTE_LEN - 1; t >= 0; t--)
						// {
						// 	printf("%d", (bytes[k] >> t) & 1);
						// }

						// printf(" ");
						
					}
					// printf("\n");
					break;
				}
				default:
					throw std::runtime_error("Invalid command bits");
				}
			}

			data.push_back(bytes[j % COMPRESS_BYTES_COUNT]);
		}
	}

	Bitmap rezult(combit.getHeight(), combit.getWidth(), data.data());

	return rezult;
}