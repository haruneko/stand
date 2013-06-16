/*
 *
 *    GeneratorEnvelope.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "GeneratorEnvelope.h"

GeneratorEnvelope::GeneratorEnvelope(Envelope *pitch) :
    Envelope()
{
    setEnvelope(pitch);
}

void GeneratorEnvelope::setEnvelope(Envelope *pitch)
{
    if(!pitch)
    {
        _pitch = this;
    }
    else
    {
        _pitch = pitch;
    }
}

double GeneratorEnvelope::generate(double ms)
{
    return _pitch->value(ms);
}

double GeneratorEnvelope::msTimeLength() const
{
    return _pitch->msLength();
}
