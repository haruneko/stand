/*
 *
 *    Specgram.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/03/21
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <iostream>

#include "Specgram.h"

Specgram::Specgram(int frameLength, int frequencyLength)
{
    _data = NULL;
    alloc(frameLength, frequencyLength);
}

Specgram::~Specgram()
{
    _destroy();
}

void Specgram::alloc(int t, int f)
{
    _destroy();
    if(t <= 0 || f <= 0)
    {
        return;
    }
    _data = new double*[t];
    _data[0] = new double[t*f];
    for(int i = 1; i < t; i++)
    {
        _data[i] = _data[0] + f * i;
    }
    _frameLength = t;
    _frequencyLength = f;
}

void Specgram::_destroy()
{
    if(_data)
    {
        delete[] _data[0];
        delete[] _data;
        _data = NULL;
    }
    _frameLength = 0;
    _frequencyLength = 0;
}

void Specgram::setValue(double val, int t, int f)
{
    _data[t][f] = val;
}

double Specgram::value(int t, int f) const
{
    return _data[t][f];
}

const double *const *Specgram::data() const
{
    return _data;
}

double *Specgram::operator [](int t)
{
    return _data[t];
}

int Specgram::frameLength() const
{
    return _frameLength;
}

int Specgram::frequencyLength() const
{
    return _frequencyLength;
}

bool Specgram::isValid() const
{
    return (_data && _data[0] && _frameLength >0 && _frequencyLength > 0);
}
