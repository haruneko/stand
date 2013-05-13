/*
 *
 *    ResidualExtractor.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/09
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QtGlobal>

#include "fft.h"
#include "../Specgram.h"

#include "ResidualExtractor.h"

void ResidualExtractor::extract(Specgram *dst, const Specgram *src)
{
    dst->alloc(src->frameLength(), src->frequencyLength());

    for(int t = 0; t < src->frameLength(); t++)
    {
        extractOneFrame((*dst)[t], src->data()[t], src->frequencyLength());
    }
}

void ResidualExtractor::extractOneFrame(double *dst, const double *residual, int fftLength)
{
    // src: FFT source
    fft_complex *src = new fft_complex[fftLength];
    fft_complex *test = new fft_complex[fftLength];

    convertToComplex(src, residual, fftLength);

    fft_plan p = fft_plan_dft_c2r_1d(fftLength, src, dst, FFT_BACKWARD);
    fft_execute(p);

    fft_plan p2 = fft_plan_dft_r2c_1d(fftLength, dst, test, FFT_FORWARD);
    fft_execute(p2);
/*    for(int i = 0; i < fftLength / 8; i++)
    {
        qDebug("(%4e, %4e) - (%4e, %4e)", src[i][0], src[i][1], test[i][0] / fftLength, test[i][1] / fftLength);
    }
*/
    fft_destroy_plan(p);
    delete[] src;
}

void ResidualExtractor::convertToComplex(fft_complex *dst, const double *src, int fftLength)
{
    dst[0][0] = src[0];
    dst[0][1] = 0.0;
    for(int i = 1; i < fftLength / 2; i++) {
        dst[i][0] = src[2*i];
        dst[i][1] = src[2*i-1];
    }
    dst[fftLength/2][0] = src[fftLength-1];
    dst[fftLength/2][1] = 0.0;
}
