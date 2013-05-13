/*
 *
 *    PlatinumSeem.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/08
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "../Envelope.h"
#include "../Specgram.h"

#include "../ffem/DioFfem.h"
#include "../world/platinum.h"
#include "../world/star.h"
#include "../world/dio.h"
#include "StarSeem.h"

#include "PlatinumSeem.h"

PlatinumSeem::PlatinumSeem(Envelope *f0, Specgram *power)
{
    _deletableF0 = false;
    _deletablePower = false;
    setF0(f0);
    setPower(power);
}

PlatinumSeem::~PlatinumSeem()
{
    if(_deletableF0)
    {
        delete _f0;
    }
    if(_deletablePower)
    {
        delete _power;
    }
}

void PlatinumSeem::setF0(Envelope *f0)
{
    if(_deletableF0)
    {
        delete _f0;
    }
    _f0 = f0;
    _deletableF0 = false;
}

void PlatinumSeem::setPower(Specgram *power)
{
    if(_deletablePower)
    {
        delete _power;
    }
    _power = power;
    _deletablePower = false;
}

bool PlatinumSeem::_prepare(const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod)
{
    bool result = true;

    DioFfem dio;
    Envelope *f0 = new Envelope();
    result &= dio.estimate(f0, src, length, samplingFrequency, msFramePeriod);
    setF0(f0);
    _deletableF0 = true;

    StarSeem star(f0);
    Specgram *power = new Specgram();
    result &= star.estimate(power, src, length, fftLength, samplingFrequency, msFramePeriod);
    setPower(power);
    _deletablePower = true;

    return result;
}

bool PlatinumSeem::estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod)
{
    if(!_f0 || !_power || _f0->msFramePeriod() != msFramePeriod || _power->frameLength() != _f0->size())
    {
        if(!_prepare(src, length, fftLength, samplingFrequency, msFramePeriod))
        {
            return false;
        }
    }
    /* FFT 長が違うときは WORLD に合わせる */
    fftLength = GetFFTSizeForStar(samplingFrequency);
    dst->alloc(_power->frameLength(), fftLength);
    double *t = new double[_power->frameLength()];
    for(int i = 0; i < _power->frameLength(); i++)
    {
        t[i] = msFramePeriod * i / 1000.0;
    }
    Platinum(src, length, samplingFrequency, t, _f0->data(), _f0->size(), _power->data(), fftLength, dst->pointer());
    delete[] t;

    return true;
}


