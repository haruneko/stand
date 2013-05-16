/*
 *
 *    WorldSynthesis.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <iostream>

#include "../world/ResidualExtractor.h"
#include "../world/constant_numbers.h"
#include "../world/common.h"

#include "WorldSynthesis.h"

WorldSynthesis::WorldSynthesis(int fftLength)
{
    fftLength = 0;
    _minimumPhase = NULL;
    _spectrum = NULL;
    _impulse = NULL;
    _plan = NULL;
    _setFftLength(fftLength);
}

WorldSynthesis::~WorldSynthesis()
{
    _destroy();
}

void WorldSynthesis::_setFftLength(int fftLength)
{
    _destroy();
    _fftLength = fftLength;
    if(!fftLength)
    {
        return;
    }
    _minimumPhase = new MinimumPhaseAnalysis;
    InitializeMinimumPhaseAnalysis(fftLength, _minimumPhase);
    _spectrum = new fft_complex[fftLength / 2 + 1];
    _impulse = new double[fftLength];
    _plan = new fft_plan;
    *_plan = fft_plan_dft_c2r_1d(fftLength, _spectrum, _impulse, FFT_BACKWARD);
}

void WorldSynthesis::_destroy()
{
    if(_minimumPhase)
    {
        DestroyMinimumPhaseAnalysis(_minimumPhase);
    }
    delete _minimumPhase;
    delete[] _spectrum;
    delete[] _impulse;

    if(_plan)
    {
        fft_destroy_plan(*_plan);
        _plan = NULL;
    }
    _fftLength = 0;
    _spectrum = NULL;
    _impulse = NULL;
}

double WorldSynthesis::msForUnvoicedFrame() const
{
    return 1000.0 / world::kDefaultF0;
}

void WorldSynthesis::synthesize(double *dst, int length, int fftLength, const double *spectrum, const double *residual)
{
    // 長さが違うときはバッファ再生成
    if(fftLength!= _fftLength)
    {
        _setFftLength(fftLength);
    }

    // エルミート対称なので半分でよろしい.
    int lastIndex = fftLength / 2;
    // パワースペクトル→最小位相応答スペクトル
    for (int i = 0; i <= lastIndex; i++)
    {
        _minimumPhase->log_spectrum[i] = log(spectrum[i]) / 2.0;
    }
    GetMinimumPhaseSpectrum(_minimumPhase);

    // 最小位相応答と励起信号を畳み込みする.
    fft_complex *minimum = _minimumPhase->minimum_phase_spectrum;
    _spectrum[0][0] = minimum[0][0] * residual[0];
    _spectrum[0][1] = 0.0;
    for(int i = 1; i < lastIndex; i++)
    {
        _spectrum[i][0] = minimum[i][0] * residual[i*2-1] - minimum[i][1] * residual[i*2];
        _spectrum[i][1] = minimum[i][1] * residual[i*2-1] + minimum[i][0] * residual[i*2];
    }
    _spectrum[lastIndex][0] = minimum[lastIndex][0] * residual[fftLength - 1];
    _spectrum[lastIndex][1] = 0.0;

    // 逆 FFT したら
    fft_execute(*_plan);

    // バッファに足しこんで終了.
    for(int i = 0; i < _fftLength * 3 / 4 && i < length; i++) // ループ回数は本家に合わせた.
    {
        dst[i] += _impulse[i] / _fftLength; // FFT の補正項はここ.
    }
}

