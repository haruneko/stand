/*
 *
 *    StarSeem.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/04
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <iostream>

#include "../ffem/DioFfem.h"
#include "../Specgram.h"
#include "../world/dio.h"
#include "../world/star.h"

#include "StarSeem.h"

StarSeem::StarSeem(Envelope *e)
{
    _pitch = NULL;
    _setPitch(e);
}

StarSeem::~StarSeem()
{
    _destroy();
}

void StarSeem::_destroy()
{
    if(_autodelete)
    {
        delete _pitch;
    }
    _pitch = NULL;
}

void StarSeem::_setPitch(Envelope *e)
{
    _destroy();
    _pitch = e;
    _autodelete = false;        // 他から与えられた場合は delete したらまずい．
}

bool StarSeem::estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod)
{
    int tLen = GetSamplesForDIO(samplingFrequency, length, msFramePeriod);
    /* 長さ違いの場合は現状は STAR に合わせておく */
    fftLength = GetFFTSizeForStar(samplingFrequency);
    dst->alloc(tLen, fftLength / 2 + 1);

    // 今保持している基本周波数がうまくないので再推定
    if(!_pitch || _pitch->size() < tLen)
    {
        _destroy();
        // Do DIO.
        FfemInterface *ffem = new DioFfem;
        _pitch = new Envelope();
        _autodelete = true;
        ffem->estimate(_pitch, src, length, samplingFrequency, msFramePeriod);
        delete ffem;
    }
    Star(src, length, samplingFrequency, msFramePeriod, _pitch->data(), _pitch->size(), dst->pointer());

    return true;
}
