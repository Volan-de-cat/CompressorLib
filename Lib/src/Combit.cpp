#include "Combit.h"

#include <string.h>

Combit::Combit(uint64_t height, uint64_t width, bool* emptyLine, uint8_t* data, uint64_t length)
	: _height(height)
	, _width(width)
	, _emptyLine(new bool[_height])
	, _data(new uint8_t[_height * _width])
	, _length(length)
{
	memcpy(_emptyLine, emptyLine, _height);
	memcpy(_data, data, _height * _width);
}
Combit::Combit(const Combit& other)
	: _height(other._height)
	, _width(other._width)
	, _emptyLine(new bool[_height])
	, _data(new uint8_t[_height * _width])
	, _length(other._length)
{
	memcpy(_emptyLine, other._emptyLine, _height);
	memcpy(_data, other._data, _height * _width);
}
Combit::Combit(Combit&& other)
	: _height(other._height)
	, _width(other._width)
	, _emptyLine(other._emptyLine)
	, _data(other._data)
	, _length(other._length)
{
	other._height = 0;
	other._width = 0;
	other._emptyLine = nullptr;
	other._data = nullptr;
	other._length = 0;
}
Combit::~Combit()
{
	_height = 0;
	_width = 0;

	if (nullptr != _emptyLine)
	{
		delete[] _emptyLine;
	}

	if (nullptr != _data)
	{
		delete[] _data;
	}

	_length = 0;
}

Combit& Combit::operator=(const Combit& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (nullptr != _emptyLine)
	{
		delete[] _emptyLine;
	}

	if (nullptr != _data)
	{
		delete[] _data;
	}

	_height = other._height;
	_width = other._width;
	_emptyLine = new bool[_height];
	_data = new uint8_t[_height * _width];
	_length = other._length;

	memcpy(_emptyLine, other._emptyLine, _height);
	memcpy(_data, other._data, _height * _width);

	return *this;
}
Combit& Combit::operator=(Combit&& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (nullptr != _emptyLine)
	{
		delete[] _emptyLine;
	}

	if (nullptr != _data)
	{
		delete[] _data;
	}

	_height = other._height;
	_width = other._width;
	_emptyLine = other._emptyLine;
	_data = other._data;
	_length = other._length;

	other._height = 0;
	other._width = 0;
	other._emptyLine = nullptr;
	other._data = nullptr;
	other._length = 0;

	return *this;
}