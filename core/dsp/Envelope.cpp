/*
 *
 *    Envelope.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/04
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "Envelope.h"

#include <stdio.h>
#include <string.h>

Envelope::Envelope(double *data, int size, double msFramePeriod, bool autodelete)
{
    _data = NULL;
    _autodelete = false;
    _defaultValue = 0.0;
    if(data)
    {
        set(data, size, msFramePeriod, autodelete);
    }
    else
    {
        _msFramePeriod = msFramePeriod;
        if(size)
        {
            set(new double[size], size, msFramePeriod, true);
        }
    }
}

Envelope::~Envelope()
{
    _destroy();
}

void Envelope::_destroy()
{
    if(_autodelete)
    {
        delete _data;
    }
    _data = NULL;
    _autodelete = false;
}

void Envelope::set(double *data, int size, double msFramePeriod, bool autodelete)
{
    if(!data)
    {
        qDebug("Envelope::set(NULL); // Invalid args.");
        return;
    }
    _destroy();
    _data = data;
    _size = size;
    _msFramePeriod = msFramePeriod;
    _autodelete = autodelete;
}

double Envelope::value(double ms) const
{
    int index = ms / _msFramePeriod;
    return value(index);
}

double Envelope::value(int index) const
{
    if(!_data)
    {
        return _defaultValue;
    }

    index = qMax(0, qMin(index, _size - 1));

    return _data[index];
}

const double *Envelope::data() const
{
    return _data;
}

double Envelope::msFramePeriod() const
{
    return _msFramePeriod;
}

int Envelope::size() const
{
    return _size;
}

double Envelope::msLength() const
{
    return _size * _msFramePeriod;
}
