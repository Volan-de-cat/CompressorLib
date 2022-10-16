#include "Bitmap.h"

#include <string.h>

Bitmap::Bitmap(uint64_t height, uint64_t width)
	: _height(height)
	, _width(width)
	, _data(new uint8_t[_height * _width])
{
	memset(_data, 0, _height * _width);
}
Bitmap::Bitmap(uint64_t height, uint64_t width, uint8_t* data)
	: _height(height)
	, _width(width)
	, _data(new uint8_t[_height * _width])
{
	memcpy(_data, data, _height * _width);
}
Bitmap::Bitmap(const Bitmap& other)
	: _height(other._height)
	, _width(other._width)
	, _data(new uint8_t[_height * _width])
{
	memcpy(_data, other._data, _height * _width);
}
Bitmap::Bitmap(Bitmap&& other)
	: _height(other._height)
	, _width(other._width)
	, _data(other._data)
{
	other._height = 0;
	other._width = 0;

	other._data = nullptr;
}
Bitmap::~Bitmap()
{
	_height = 0;
	_width = 0;

	if (nullptr != _data)
	{
		delete[] _data;
	}
}

Bitmap& Bitmap::operator=(const Bitmap& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (nullptr != _data)
	{
		delete[] _data;
	}

	_height = other._height;
	_width = other._width;

	_data = new uint8_t[_height * _width];
	memcpy(_data, other._data, _height * _width);

	return *this;
}
Bitmap& Bitmap::operator=(Bitmap&& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (nullptr != _data)
	{
		delete[] _data;
	}

	_height = other._height;
	_width = other._width;
	_data = other._data;

	other._height = 0;
	other._width = 0;

	other._data = nullptr;

	return *this;
}

bool Bitmap::setData(const uint8_t* data)
{
	if (nullptr == data)
	{
		return false;
	}

	memcpy(_data, data, _height * _width);

	return true;
}