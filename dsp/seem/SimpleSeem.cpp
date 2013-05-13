/*
 *
 *    SimpleSeem.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/04/30
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <cmath>
#include <iostream>

#include "../Specgram.h"
#include "../fftsg/fftsg.h"

#include "SimpleSeem.h"

SimpleSeem::SimpleSeem(int fftLength, double (*window)(double))
{
    _window = window;
    _ip = NULL;
    _w = NULL;
    _fftLength = 0;
    _resetFftLength(fftLength);
}

SimpleSeem::~SimpleSeem()
{
    _destroy();
}

void SimpleSeem::_destroy()
{
    delete[] _ip;
    delete[] _w;
    _fftLength =0;
    _ip = NULL;
    _w = NULL;
}

void SimpleSeem::_resetFftLength(int fftLength)
{
    // リセットの必要が無い
    if(fftLength == _fftLength)
    {
       return;
    }

    _destroy();
    // 長さが無い
    if(fftLength <= 0)
    {
        return;
    }
    _fftLength = fftLength;
    _ip = new int[(int)(2 + sqrt((double)fftLength) + 0.5)];
    _w = new double[fftLength];

    _ip[0] = 0;
}

bool SimpleSeem::estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod)
{
    double frameShift = samplingFrequency * msFramePeriod / 1000.0;
    int frameLength = length / frameShift + 1;
    // エルミート対称なので情報は半分しか意味が無い
    dst->alloc(frameLength, fftLength / 2);
    // FFT 長を変更
    _resetFftLength(fftLength);

    // 波形切り出し用バッファ
    double *buf = new double[fftLength * 2];
    for(int i = 0; i < frameLength; i++)
    {
        // 切り出すのは半分でいい（実部のみだから）
        _setBuffer(buf, src, i, length, fftLength, frameShift, _window);

        // ToDo: do FFT buf=>out
        rdft(fftLength * 2, FFTSG_FORWARD, buf, _ip, _w);
        _setPowerSpectrum((*dst)[i], buf, fftLength);
    }
    delete[] buf;

    return true;
}

void SimpleSeem::_setBuffer(double *buf, const double *wave, int frameIndex, int length, int fftLength, double frameShift, double (*window)(double))
{
    int midIndex = frameIndex * frameShift;
    int waveIndex = midIndex - fftLength / 2;
    int index;
    // waveIndex が 0 未満にならないようにする．
    for(index = 0; waveIndex < 0; index++, waveIndex++)
    {
        buf[index * 2] = buf[index * 2 + 1] = 0;
    }

    for(; index < fftLength && waveIndex < length; index++, waveIndex++)
    {
        buf[index * 2] = (*window)((double)index / fftLength) * wave[waveIndex];
        buf[index * 2 + 1] = 0.0;
    }

    for(; index < fftLength; index++)
    {
        buf[index * 2] = buf[index * 2 + 1] = 0.0;
    }
}

void SimpleSeem::_setPowerSpectrum(double *dst, const double *src, int fftLength)
{
    // エルミート対称なので情報は半分しか意味が無い
    for(int i = 0; i < fftLength / 2; i++)
    {
        dst[i] = src[i*2 + 1] * src[i*2 + 1] + src[i*2] * src[i*2];
    }
}
