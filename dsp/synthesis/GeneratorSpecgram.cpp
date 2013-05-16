/*
 *
 *    GeneratorSpecgram.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "GeneratorSpecgram.h"

GeneratorSpecgram::GeneratorSpecgram(Specgram *specgram, double msFramePeriod) :
    Specgram()
{
    setSpecgram(specgram, msFramePeriod);
}

void GeneratorSpecgram::setSpecgram(Specgram *specgram, double msFramePeriod)
{
    if(!specgram)
    {
        _specgram = this;
    }
    else
    {
        _specgram = specgram;
    }
    _msFramePeriod = msFramePeriod;
}

Specgram *GeneratorSpecgram::specgram()
{
    return _specgram;
}

const double *GeneratorSpecgram::generate(double ms) const
{
    // 最近傍近似
    int index = (0.5 + ms / _msFramePeriod);
    return _specgram->data()[index];
}

double GeneratorSpecgram::msTimeLength() const
{
    return _msFramePeriod * _specgram->frameLength();
}

double GeneratorSpecgram::msFramePeriod() const
{
    return _msFramePeriod;
}
